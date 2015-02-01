// Copyright 2015 David Gasquez

#include "bow.h"

Mat ComputeHistograms(string folder_path, Mat &vocabulary) {
  // Cast string to char pointer
  const char *c = folder_path.c_str();

  // Create directory and directory structure
  DIR *directory;
  struct dirent *directory_entry;

  // To store all descriptors
  Mat histograms;

  // Matcher
  Ptr<DescriptorMatcher> matcher(new BFMatcher());

  // Detector
  Ptr<FeatureDetector> detector(new DenseFeatureDetector());

  // Extractor
  Ptr<DescriptorExtractor> extractor(new SiftDescriptorExtractor());

  // BOW descriptor extractor
  BOWImgDescriptorExtractor bow_descriptor_extractor(extractor, matcher);

  // Set the dictionary
  bow_descriptor_extractor.setVocabulary(vocabulary);

  // Read images and get descriptors
  if (directory = opendir(c)) {
    while ((directory_entry = readdir(directory))) {
      // Get filename
      string s = directory_entry->d_name;

      // Read only jpg files
      if (s.find("jpg") != string::npos) {
        // Read an image
        Mat image = imread(folder_path + s, CV_LOAD_IMAGE_GRAYSCALE);

        vector<KeyPoint> keypoints;
        detector->detect(image, keypoints);

        // Create the BoW representation of the image
        Mat bow_histogram;
        bow_descriptor_extractor.compute(image, keypoints, bow_histogram);

        // Add histogram to matrix
        histograms.push_back(bow_histogram);
      }
    }
    // Close directory
    closedir(directory);
  }
  return histograms;
}

int main(int argc, char const *argv[]) {
  // Check parameters
  if (argc != 3) {
    cerr << "Wrong number of parameters" << endl;
    cerr << "Usage: ./bow <vocabulary_file_path> <train_images_folder>" << endl;
    return -1;
  }
  cout << endl;

  // Get parameters
  string vocabulary_file_path = argv[1];
  string train_images_folder = argv[2];

  // Read vocabulary and store it
  Mat vocabulary;
  cout << "Reading vocabulary" << flush;
  FileStorage fs(vocabulary_file_path, FileStorage::READ);
  fs["vocabulary"] >> vocabulary;
  fs.release();
  cout << "\t\tDONE" << endl;

  // Compute histograms from training images
  cout << "Computing histograms" << flush;
  Mat training_histograms = ComputeHistograms(train_images_folder, vocabulary);
  cout << "\t\tDONE" << endl;

  return 0;
}
