Category Recognition
====================

This tool allows image classification into different categories using OpenCV
and Machine Learning techniques.

Dependencies
------------
  - OpenCV

Resources Structure
-------------------
 - resources/
  - random_images/ 
  - categories_train/
    - category_1/
    - category_2/
    - category_3/
    - ...
  - categories_test/
    - category_1/
    - category_2/
    - category_3/
    - ...

Run
---

1. Fork, clone or download the source from GitHub
2. Compile it using `make`
3. Create vocabulary file with a bunch of random images `./make_vocabulary <imgaes_folder_path>`
4. Make a folder to add categories folders with images to train SVM
5. Create Bag of Words descriptors of your categories train images `./bow <vocabulary_file_path> <train_images_folder>`
6. Now you have a file with the trained SVM and in console output you have the labels.
7. Classify with `./classify <vocabulary_file_path> <SVM_path> <new_image_path>"`. It will return a number you must match in the computed labels when computing Bag of Words
