/*
 * Struck: Structured Output Tracking with Kernels
 *
 * Code to accompany the paper:
 *   Struck: Structured Output Tracking with Kernels
 *   Sam Hare, Amir Saffari, Philip H. S. Torr
 *   International Conference on Computer Vision (ICCV), 2011
 *
 * Copyright (C) 2011 Sam Hare, Oxford Brookes University, Oxford, UK
 *
 * This file is part of Struck.
 *
 * Struck is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Struck is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Struck.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Tracker.h"
#include "Config.h"

#include <trax/opencv.hpp>
#include <ctime>

#include <iostream>
#include <fstream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace std;
using namespace cv;

static const int kLiveBoxWidth = 80;
static const int kLiveBoxHeight = 80;

void parseFeatures(string str, std::vector<Config::FeatureKernelPair>& config) {

	Config::FeatureKernelPair fkp;

    istringstream f(str);
    string s;
    while (getline(f, s, ';')) {

		istringstream f2(s);
		string t;
		vector<string> tokens;
		while (getline(f2, t, '@')) {
			tokens.push_back(t);
		}

		if (tokens.size() < 2) {
			cout << "Invalid feature specification, ignoring." << endl;
			continue;
		}

		if (tokens[0] == "haar") {
			fkp.feature = Config::kFeatureTypeHaar;
		} else if (tokens[0] == "raw") {
			fkp.feature = Config::kFeatureTypeRaw;
		} else if (tokens[0] == "histogram") {
			fkp.feature = Config::kFeatureTypeHistogram;
		} else {
			cout << "Invalid feature specification, ignoring." << endl;
			continue;
		}

		if (tokens[1] == "linear") {
			fkp.kernel = Config::kKernelTypeLinear;
		} else if (tokens[1] == "intersection") {
			fkp.kernel = Config::kKernelTypeIntersection;
		} else if (tokens[1] == "chi2") {
			fkp.kernel = Config::kKernelTypeChi2;
		} else if (tokens[1] == "gaussian") {
			fkp.kernel = Config::kKernelTypeGaussian;
			if (tokens.size() < 3) {
				cout << "Invalid feature specification, ignoring." << endl;
				continue;
			}
			fkp.params.push_back(atof(tokens[2].c_str()));
		} else {
			cout << "Invalid feature specification, ignoring." << endl;
			continue;
		}

		config.push_back(fkp);
    }

}


int main(int argc, char* argv[])
{
    trax::ImageList img;
    trax::Region reg;
    cv::Mat image, gray, resized;
	cv::Rect rectangle;

    trax::Server handle(trax::Configuration(TRAX_REGION_RECTANGLE, TRAX_IMAGE_PATH | TRAX_IMAGE_MEMORY | TRAX_IMAGE_BUFFER, TRAX_CHANNEL_COLOR), trax_no_log);

	Config config;

	FloatRect initBB;
	float scale = 1.f;

    Mat frame;
    Tracker* tracker = NULL;

    bool run = 1;

    while(run)
    {

        trax::Properties prop;
		trax::Region status;

        int tr = handle.wait(img, reg, prop);

        // There are two important commands. The first one is TRAX_INITIALIZE that tells the
        // tracker how to initialize.
        if (tr == TRAX_INITIALIZE) {

            config.frameWidth = 320;
            config.frameHeight = 240;

        	config.seed = prop.get("seed", (int) time(NULL));
        	config.searchRadius = prop.get("search_radius", 30);
        	config.svmC = prop.get("svm_c", 100.0f);
        	config.svmBudgetSize = prop.get("svm_budged_size", 100);

			string s = prop.get("features", "haar@gaussian@2.0");
			parseFeatures(s, config.features);

			image = trax::image_to_mat(img.get(TRAX_CHANNEL_COLOR));

			if (image.channels() == 3)
				cv::cvtColor(image, gray, CV_BGR2GRAY);
			else
				gray = image;

	    	scale = MIN((float)config.frameWidth/gray.cols, (float)config.frameHeight/gray.rows);
			cv::resize(gray, resized, Size(), scale, scale);

            float x, y, width, height;
            reg.get(&x, &y, &width, &height);
            initBB = FloatRect(x*scale, y*scale, width*scale, height*scale);

            if (tracker) { delete tracker; tracker = NULL; }

            tracker = new Tracker(config);
            tracker->Initialise(resized, initBB);
			const FloatRect& bb = tracker->GetBB();
            status = trax::Region::create_rectangle(bb.XMin()/scale, bb.YMin()/scale, bb.Width()/scale, bb.Height()/scale);

        } else
        // The second one is TRAX_FRAME that tells the tracker what to process next.
        if (tr == TRAX_FRAME) {

            image = trax::image_to_mat(img.get(TRAX_CHANNEL_COLOR));

			if (image.channels() == 3)
				cv::cvtColor(image, gray, CV_BGR2GRAY);
			else
				gray = image;

			cv::resize(gray, resized, Size(), scale, scale);

            tracker->Track(resized);

			const FloatRect& bb = tracker->GetBB();

            status = trax::Region::create_rectangle(bb.XMin()/scale, bb.YMin()/scale, bb.Width()/scale, bb.Height()/scale);

        }
        // Any other command is either TRAX_QUIT or illegal, so we exit.
        else {
			break;
        }

        handle.reply(status, trax::Properties());

    }

    return EXIT_SUCCESS;

}
