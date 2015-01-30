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
  Mat features_unclustered;

  // Read images and get descriptors
  if (directory = opendir(c)) {
    cout << "Computing descriptors from images in folder: " << path << endl;
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

        Mat image = ReadImage(path + s);
        detector.detect(image, keypoints);
        detector.compute(image, keypoints, descriptors);
        features_unclustered.push_back(descriptors);
        cout << "." << flush;
      }
    }
    cout << endl << "Descriptors obtained" << endl;
    // Close directory
    closedir(directory);
  }
  return features_unclustered;
}

} // namespace clustering
