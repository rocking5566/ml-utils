svm-scale -s right_all_train_hog_lbp_321.range right_all_train_hog_lbp_321 > right_all_train_hog_lbp_321_scale
svm-train -s 0 -c 8 -g 1 -b 1 right_all_train_hog_lbp_321_scale
pause