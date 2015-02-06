// Copyright 2015 David Gasquez

#ifndef SRC_CLUSTERING_H_
#define SRC_CLUSTERING_H_

#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <string>
#include <vector>
#include "dirent.h"

using namespace std;
using namespace cv;

// Read Image from path
Mat ReadImage(string image_path);

// Computes descriptors of forlder's images
Mat ComputeDescriptors(string path, int number_of_descriptors);

// Cluster the features into K bags
Mat CreateVocabulary(const Mat &descriptors, int K);

#endif  // SRC_CLUSTERING_H_
