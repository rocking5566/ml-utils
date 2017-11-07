rem search appropriate parameter (C and g) by cross validation
python grid.py -log2c -5,5,1 -log2g -4,0,1 -v 5 -m 300 -gnuplot "C:\Program Files\gnuplot\bin\gnuplot.exe" right_ULSee_all_train_hog_32x64_144_with_left_flip
pause
