// Copyright 2015 David Gasquez

#ifndef BOW_H_
#define BOW_H_

#include "dirent.h"
#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

namespace bow {

// Compute histogram from an image
extern Mat ComputeHistograms(Mat &image);

// Compute histograms from images in folder path
extern Mat ComputeHistograms(string image_path);

}  // namespace bow

#endif  // BOW_H_
