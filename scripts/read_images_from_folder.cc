#include <iostream>
#include <iterator>
#include <algorithm>
#include <opencv2/opencv.hpp>
#include <boost/filesystem.hpp>

using namespace cv;
using namespace std;
using namespace boost::filesystem;

// Muestra una imagen por pantalla hasta que se pulsa una tecla
void ShowImage(Mat const &image, char const *title) {
  // Mostramos la imagen
  imshow(title, image);

  // Esperar pulsación de tecla para seguir
  waitKey(0);

  // Destruir la ventana
  destroyWindow(title);
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    cerr << "Usage: ./show_images path";
    return -1;
  }

  path folder_path (argv[1]);

  if (exists(folder_path) && is_directory(folder_path)) {
    vector<path> image_paths;
    copy(directory_iterator(folder_path), directory_iterator(), back_inserter(image_paths));
    for (vector<path>::const_iterator it (image_paths.begin()); it != image_paths.end(); ++it) {
      if (extension(*it) != ".jpg") {
        continue;
      }
      cout << "Reading image: " << *it << endl;
      Mat img = imread( it->c_str(), CV_LOAD_IMAGE_COLOR);

      ShowImage(img, it->c_str());
    }
  } else {
    cout << "Path not correct";
  }
  
  return 0;
}
