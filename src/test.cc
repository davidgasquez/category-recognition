// Copyright 2015 David Gasquez

#include "test.h"

int main(int argc, char const *argv[]) {

  // Check parameters
  if (argc != 4) {
    cerr << "Wrong number of parameters" << endl;
    cerr << "Usage: ./test <vocabulary_file_path> <SVM_path> <image_path>" << endl;
    return -1;
  }
  cout << endl;

  // Get parameters
  string vocabulary_file_path = argv[1];
  string image_path = argv[3];

  // Read vocabulary and store it
  Mat vocabulary;
  cout << "Reading vocabulary" << flush;
  FileStorage fs(vocabulary_file_path, FileStorage::READ);
  fs["vocabulary"] >> vocabulary;
  fs.release();
  cout << "\t\tDONE" << endl;

  // Load the SVM
  cout << "Reading SVM" << flush;
  CvSVMParams SVM_params;
  CvSVM SVM;
  SVM.load(argv[1]);
  cout << "\t\tDONE" << endl;

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

  Mat image = imread(image_path, CV_LOAD_IMAGE_GRAYSCALE);

  // Get keypoints
  vector<KeyPoint> keypoints;
  detector->detect(image, keypoints);

  // Create the BoW representation of the image
  Mat bow_histogram;
  bow_descriptor_extractor.compute(image, keypoints, bow_histogram);

  cout << endl << SVM.predict(bow_histogram) << endl;

  return 0;
}
