Before calibrating gyroscope, accelerometer calibration has to be performed. Please refer to the folder-'AccelerometerCalibration' to do this. Once the acceleration calibration is done, copy the BiasMatrix from that code.

The order to execute the files is 

IMUGyroscopeCalibration_Step1 -> This code outputs the values which are the input for the MATLAB code.
IMUCalibratedGyroscope	  -> This code outputs the calibrated acceleration values.

References:

1.http://www.lucidarme.me/?p=5057#
2.Calibration of Deterministic IMU Errors, Prescott, Honors Ferguson, Jeff
http://commons.erau.edu/cgi/viewcontent.cgi?article=1001&context=pr-honors-coe (For Method 2)

"There is readme file in every folder and sub folder. Please go through them step by step to save time and make any edits you feel neccessary. If this is the first ReadMe file you are reading for this calibration, please go back a folder
and read the ReadMe file in that folder"

-Sharath Patlolla
