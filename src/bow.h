// Copyright 2015 David Gasquez

#ifndef SRC_BOW_H_
#define SRC_BOW_H_

#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <string>
#include <vector>
#include "dirent.h"

using namespace std;
using namespace cv;

// Compute histograms from images in folder path
void ComputeFolderHistograms(string train_folder_path,
                             const Mat &vocabulary,
                             Mat &training_data,
                             Mat &training_labels);

#endif  // SRC_BOW_H_
