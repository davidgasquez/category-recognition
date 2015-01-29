// Copyright 2015 David Gasquez

#include <boost/filesystem.hpp>
#include <opencv2/opencv.hpp>
#include <algorithm>
#include <iostream>
#include <iterator>

using namespace std;
using namespace cv;
using namespace boost::filesystem;

// Show an image in a window untill a key is pressed
void ShowImage(Mat const &image, char const *title) {
  imshow(title, image);
  waitKey(0);
  destroyWindow(title);
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    cerr << "Usage: ./show_images path";
    return -1;
  }

  // Path variable
  path folder_path(argv[1]);

  // If path is a directory
  if (exists(folder_path) && is_directory(folder_path)) {
    // Fill image paths
    vector<path> image_paths;
    copy(directory_iterator(folder_path),
         directory_iterator(),
         back_inserter(image_paths));


    for (vector<path>::const_iterator it (image_paths.begin());
         it != image_paths.end(); ++it) {
      if (extension(*it) != ".jpg") {
        continue;
      }
      cout << "Reading image: " << *it << endl;
      Mat img = imread(it->c_str(), CV_LOAD_IMAGE_COLOR);

      ShowImage(img, it->c_str());
    }
  } else {
    cout << "Path not correct";
  }
  return 0;
}
