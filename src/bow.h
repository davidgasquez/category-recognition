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

// Compute histograms from images in folder path
Mat ComputeHistograms(string image_path, Mat &vocabulary);

#endif  // BOW_H_
