// Copyright 2015 David Gasquez

#include "testing.h"

void ComputeFolderHistograms(string train_folder_path,
                             const Mat &vocabulary,
                             Mat &training_data,
                             Mat &training_labels) {
  // Cast string to char pointer
  const char *folder_path = train_folder_path.c_str();

  // Create directory and directory entry for main folder
  DIR *directory;
  struct dirent *directory_entry;

  // Create directory and directory entry for sub folders
  DIR *sub_directory;
  struct dirent *sub_directory_entry;

  // Label
  int label = 0;

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

  // Read images from each folder and compute descriptors
  if (directory = opendir(folder_path)) {
    // Iterate over folders
    while ((directory_entry = readdir(directory))) {
      // Dont check . neither ..
      if (strcmp(directory_entry->d_name, ".") == 0 ||
          strcmp(directory_entry->d_name, "..") == 0) {
        continue;
      }

      // Get sub folder name
      string s = directory_entry->d_name;

      // Get sub folder path
      const char *sub_folder = (train_folder_path + s).c_str();

      // Open sub folder
      if (sub_directory = opendir(sub_folder)) {
        // Iterate over files in sub folder
        while (sub_directory_entry = readdir(sub_directory)) {
          // Get file name
          string file_name = sub_directory_entry->d_name;

          // If it's an image, compute histogram
          if (file_name.find("jpg") != string::npos) {
            // Read an image
            string image_path = folder_path + s + "/" + file_name;
            Mat image = imread(image_path, CV_LOAD_IMAGE_GRAYSCALE);

            // Get keypoints
            vector<KeyPoint> keypoints;
            detector->detect(image, keypoints);

            // Create the BoW representation of the image
            Mat bow_histogram;
            bow_descriptor_extractor.compute(image, keypoints, bow_histogram);

            // Add histogram to matrix
            training_data.push_back(bow_histogram);

            // Add label
            training_labels.push_back(label);
          }
        }
        // Close sub directory
        closedir(sub_directory);
        label++;
      }
    }
    // Close directory
    closedir(directory);
  }
}

int main(int argc, char const *argv[]) {

  // Check parameters
  if (argc != 4) {
    cerr << "Wrong number of parameters" << endl;
    cerr << "Usage: ./test <vocabulary_file_path> ";
    cerr << "<SVM_path> <test_images_folder>" << endl;
    return -1;
  }

  // Get parameters
  string vocabulary_file_path = argv[1];
  string SVM_path = argv[2];
  string test_images_folder = argv[3];

  // Read vocabulary and store it
  Mat vocabulary;
  FileStorage fs(vocabulary_file_path, FileStorage::READ);
  fs["vocabulary"] >> vocabulary;
  fs.release();

  // Load the SVM
  CvSVM SVM;
  SVM.load(SVM_path.c_str());

  // Compute histograms from test images
  cout << "Computing test images histograms" << flush;
  Mat test_data;
  Mat test_labels;
  ComputeFolderHistograms(test_images_folder, vocabulary,
                          test_data, test_labels);
  cout << "\t\tDONE" << endl;

  // Get number of categories (last image label)
  int categories = test_labels.at<int>(test_data.rows - 1, 0) + 1;
  Mat confussion_matrix = Mat::zeros(categories, categories, CV_8UC1);

  // Make predictions
  cout << "Making predictions" << flush;
  for (int i = 0; i < test_data.rows; ++i) {
    int predicted_label = SVM.predict(test_data.row(i));
    int label = test_labels.at<int>(i, 0);
    confussion_matrix.at<uchar>(label, predicted_label)++;
  }
  cout << "\t\tDONE" << endl;

  // Print confussion matrix
  cout << "Confussion Matrix" << endl;
  cout << confussion_matrix << endl;

  // Compute test rate
  double correct = 0;
  for (int i = 0; i < confussion_matrix.rows; ++i) {
    correct += confussion_matrix.at<uchar>(i, i);
  }
  double test_rate = correct / test_data.rows;
  cout << "Test rate = " << test_rate << endl;

  return 0;
}
