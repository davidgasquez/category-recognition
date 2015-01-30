// Copyright 2015 David Gasquez

#include "clustering/clustering.h"

namespace clustering {

Mat ReadImage(string image_path) {
  Mat output = imread(image_path, CV_LOAD_IMAGE_GRAYSCALE);
  return output;
}

Mat ComputeDescriptors(string path, int number_of_descriptors) {
  // Cast string to char pointer
  const char *c = path.c_str();

  // Create directory and directory structure
  DIR *directory;
  struct dirent *directory_entry;

  // To store all descriptors
  Mat descriptors_unclustered;

  // Read images and get descriptors
  if (directory = opendir(c)) {
    while ((directory_entry = readdir(directory))) {
      // Get filename
      string s = directory_entry->d_name;

      // Read only jpg files
      if (s.find("jpg") != string::npos) {
        // Image keypoints and descriptors
        vector<KeyPoint> keypoints;
        Mat descriptors;

        // Calculate maximum descriptors per image
        // TODO: 500 is the number of images in the train folder. Should be
        // calculated, not a magic number
        int max_descriptors = number_of_descriptors / 500;

        // Create SIFT feature descriptor extractor
        SiftDescriptorExtractor detector(max_descriptors);

        // Read an image
        Mat image = ReadImage(path + s);

        // Compute descriptors
        detector.detect(image, keypoints);
        detector.compute(image, keypoints, descriptors);

        // Add descriptors
        descriptors_unclustered.push_back(descriptors);
      }
    }
    // Close directory
    closedir(directory);
  }
  return descriptors_unclustered;
}

Mat CreateVocabulary(Mat &descriptors, int K) {
  // Initialize a TermCriteria with 100 iterations and 0.001 as error
  TermCriteria tc(CV_TERMCRIT_ITER, 100, 0.001);

  // Create vocabulary and
  Mat labels;
  Mat vocabulary;

  // Apply K-means
  kmeans(descriptors, K, labels, tc, 1, KMEANS_PP_CENTERS, vocabulary);
  
  return vocabulary;
}

}  // namespace clustering
