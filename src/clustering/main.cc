// Copyright 2015 David Gasquez

#include "clustering/clustering.h"

int main(int argc, char const *argv[]) {
  // Check parameters
  if (argc != 4) {
    cerr << "Wrong number of parameters" << endl;
    cerr << "Usage: ./clustering <images path>";
    cerr << "<number of descriptors> <number of clusters>" << endl;
    return -1;
  }
  cout << endl;

  // Get parameters
  string path = argv[1];
  int number_of_descriptors = atoi(argv[2]);
  int K = atoi(argv[3]);

  // Compute decriptors for images in folder path
  cout << "Computing descriptors" << flush;
  Mat descriptors = clustering::ComputeDescriptors(path, number_of_descriptors);
  cout << "\t\tDONE" << endl;

  // Cluster the descriptors
  cout << "Creating vocabulary";
  Mat vocabulary = clustering::CreateVocabulary(descriptors, K);
  cout << "\t\tDONE" << endl;

  return 0;
}
