// Copyright 2015 David Gasquez

#include "bow/bow.h"

int main(int argc, char const *argv[]) {
  // Check parameters
  if (argc != 3) {
    cerr << "Wrong number of parameters" << endl;
    cerr << "Usage: ./bow <vocabulary_file_path> <image_path>" << endl;
    return -1;
  }
  cout << endl;

  // Get parameters
  string vocabulary_file_path = argv[1];

  // Read vocabulary and store it
  Mat vocabulary;
  cout << "Reading vocabulary" << flush;
  FileStorage fs(vocabulary_file_path, FileStorage::READ);
  fs["vocabulary"] >> vocabulary;
  fs.release();
  cout << "\t\tDONE" << endl;

  // For each folder, take 70% of pictures
  // Train 101 SVM

  // TODO: Test with more matchers, detectors and extractors
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

  Mat image = imread(argv[2], CV_LOAD_IMAGE_GRAYSCALE);
  vector<KeyPoint> keypoints;
  detector->detect(image, keypoints);

  //Create the BoW representation of the image
  Mat bow_histogram;
  bow_descriptor_extractor.compute(image, keypoints, bow_histogram);

  return 0;
}
