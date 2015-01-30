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

  // Get parameters
  string path = argv[1];
  int number_of_descriptors = atoi(argv[2]);
  int K = atoi(argv[3]);

  // Compute decriptors for images in folder path
  Mat features_unclustered = clustering::ComputeDescriptors(path, number_of_descriptors);

  // Cluster the descriptors
  cout << "Creating vocabulary" << endl;
  // TermCriteria(int type, int maxCount, double epsilon) 
  TermCriteria tc(CV_TERMCRIT_ITER, 100, 0.001);
  Mat vocabulary;
  Mat centers;
  kmeans(features_unclustered, K, vocabulary, tc, 1, KMEANS_PP_CENTERS, centers);
  cout << "Vocabulary created" << endl;

  return 0;
}
