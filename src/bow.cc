// Copyright 2015 David Gasquez

#include "bow.h"

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
  cout << "Computing training histograms" << flush;
  Mat training_data;
  Mat training_labels;
  ComputeFolderHistograms(train_images_folder, vocabulary,
                          training_data, training_labels);
  cout << "\t\tDONE" << endl;

  // TODO: Save SVM, not this
  cout << "Saving training histograms" << flush;
  FileStorage output("resources/histograms.yml", FileStorage::WRITE);
  output << "histograms" << training_data;
  output << "labels" << training_labels;
  output.release();
  cout << "\t\tDONE" << endl;

  /*
    // Train the SVM
    cout << "Training SVM" << flush;
    CvSVMParams SVM_params;
    CvSVM SVM;
    SVM.train_auto(training_data, training_labels, Mat(), Mat(), SVM_params);
    SVM.save("test.xml");
    SVM.load("test.xml");
    cout << "\t\tDONE" << endl;
  */

  return 0;
}
