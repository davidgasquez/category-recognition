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
void ComputeFolderHistograms(string train_folder_path,
                             const Mat &vocabulary,
                             Mat &training_data,
                             Mat &training_labels);

#endif  // BOW_H_
