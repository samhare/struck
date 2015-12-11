TARGET	= struck

CC = g++
CFLAGS = -c -Wall -O3 -DNDEBUG
LDFLAGS = 

# /opt/local is used by MacPorts,
# under Linux this will probably be /usr/local
BASE_DIR := /opt/local

INCLUDE_DIRS =	-I$(BASE_DIR)/include \
				-I$(BASE_DIR)/include/eigen2

LIB_DIRS = -L$(BASE_DIR)/lib

LIBS =	-lopencv_core \
		-lopencv_highgui \
		-lopencv_imgproc

SOURCES =	src/Config.cpp \
			src/Features.cpp \
			src/HaarFeature.cpp \
			src/HaarFeatures.cpp \
			src/HistogramFeatures.cpp \
			src/ImageRep.cpp \
			src/LaRank.cpp \
			src/MultiFeatures.cpp \
			src/RawFeatures.cpp \
			src/Sampler.cpp \
			src/Tracker.cpp \
			src/main.cpp \
			src/GraphUtils/GraphUtils.cpp

OBJECTS = $(SOURCES:%.cpp=%.o)
DEPS = $(OBJECTS:.o=.d)

.PHONY: all clean

all: $(TARGET)

-include $(DEPS)
	
$(TARGET): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(LIB_DIRS) $(LIBS) $(OBJECTS) -o $@

%.o : %.cpp
	$(CC) $(CFLAGS) -MM -MF $(patsubst %.o,%.d,$@) $(INCLUDE_DIRS) $(INCLUDES) $<
	$(CC) $(CFLAGS) $(INCLUDE_DIRS) $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJECTS)
	rm -f $(DEPS)
	rm -f $(TARGET)

