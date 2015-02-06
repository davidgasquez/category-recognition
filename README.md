Category Recognition
====================

This tool allows image classification into 101 different categories using OpenCV
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
  - categories_test/
    - category_1/
    - category_2/
    - category_3/

Run
---

1. Fork, clone or download the source from GitHub
2. Compile it using `make`
3. Create vocabulary file with a bunch of random images `./make_vocabulary <imgaes_folder_path>`
4. Make a folder to add categories folders with images to train SVM
5. Create Bag of Words descriptors of your categories train images `./bow <vocabulary_file_path> <train_images_folder>`
6. Now you have a file with the trained SVM.
7. Classify! `./classify <vocabulary_file_path> <SVM_path> <new_image_path>"`
