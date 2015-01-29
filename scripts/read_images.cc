// Copyright 2015 David Gasquez

#include <opencv2/opencv.hpp>
#include "dirent.h"
#include <iostream>
#include <vector>

using namespace std;
using namespace cv;

// Show an image in a window untill a key is pressed
void ShowImage(Mat const &image, char const *title) {
  imshow(title, image);
  waitKey(0);
  destroyWindow(title);
}

// Read an image given the path
Mat ReadImage(string image_path) {
  Mat output = imread(image_path, CV_LOAD_IMAGE_GRAYSCALE);
  return output;
}

// Read all images from a folder 
vector<Mat> readFolderImages(string path) {

  // Vector to add images
  vector<Mat> images;

  // Cast string to char pointer
  const char *c = path.c_str();

  // Create directory and directory structure
  DIR *directory;
  struct dirent *directory_entry;

  // Read images
  if (directory = opendir(c)) {
    while ((directory_entry = readdir(directory))) {
      string s = directory_entry->d_name;
      Mat temporary = ReadImage(path + s);
      images.push_back(temporary);
    }
    // Close directory
    closedir(directory);
  }
  return images;
}

int main(int argc, char const *argv[])
{
  string path = argv[1];
  vector<Mat> images = readFolderImages(path);
  cout << images.size();
  ShowImage(images[3], "Image");
  return 0;
}
