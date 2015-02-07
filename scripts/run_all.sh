#! /bin/sh

clear
echo
echo "\t\t\t  Making vocabulary"
echo 
echo "-------------------------------------------------------------------------"
./bin/make_vocabulary resources/random_images/ 50000 200
echo "-------------------------------------------------------------------------"

echo
echo "\t\t  Computing Bag of Words and training SVM"
echo

echo "-------------------------------------------------------------------------"
./bin/bow resources/vocabulary.yml resources/categories_train_images/
echo "-------------------------------------------------------------------------"

echo
echo "\t\t\t\tTesting"
echo

echo "-------------------------------------------------------------------------"
./bin/test resources/vocabulary.yml resources/SVM.xml resources/categories_test_images/
echo "-------------------------------------------------------------------------"
