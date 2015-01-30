// Copyright 2015 David Gasquez

#ifndef CLUSTERING_H_
#define CLUSTERING_H_

#include "dirent.h"
#include <opencv2/opencv.hpp>
#include <opencv2/nonfree/nonfree.hpp>
#include <string>
#include <vector>

using namespace std;
using namespace cv;

namespace clustering {

// Read Image from path
extern Mat ReadImage(string image_path);

// Computes descriptors of forlder's images
extern Mat ComputeDescriptors(string path, int number_of_descriptors);

// Cluster the features into K bags
extern Mat CreateVocabulary(Mat &descriptors, int K);

}  // namespace clustering

#endif  // CLUSTERING_H_
