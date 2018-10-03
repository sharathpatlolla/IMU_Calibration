Before you run this code go to "IMUAccelerometerCalibration2_Step1" and follow the instructions, 
This code provides input for the MATLAB code(IMU_AccelerometerCalibration2). The IMU has to placed in 8 orientations while this code is running, the first orientation can be fixed by using "IMUAccelerometerCalibration2_Step1", once the 
position is fixed run the "IMU_AccelerometerCalibration2.m" in MATLAB (make sure that the serial monitor is closed while you run the code in MATLAB). 

The MATLAB code takes the average of accelerometer values in each position and calculates the BiasMatrix, MisalignmentMatrix and ScalarFactorMatrix. When you run the MATLAB code placing the IMU in the first position, it takes the required
values and tells you to "change the orientation" once it gets the values, now keep changing the position of IMU by placing it such that the gravity is along +x,-x,+y,-y,+z,-z. Care should be taken so that the IMU is almost fixed in each
position. After this 7 out of 8 positions is done, now the final position is either +60/-60 degrees(which ever was not the first position). Once all the positions are done the MATLAB code ends and ouputs the BiasMatrix, MisalignmentMatrix
 and ScalarFactorMatrix.

After this is done go to IMUCalibratedAccelerometer2 and substitute the obtained values of BiasMatrix, MisalignmentMatrix and ScalarFactorMatrix in that arduino code.


References:

1.http://www.lucidarme.me/?p=5057#
2.Calibration of Deterministic IMU Errors, Prescott, Honors Ferguson, Jeff
http://commons.erau.edu/cgi/viewcontent.cgi?article=1001&context=pr-honors-coe (For Method 2)

"There is readme file in every folder and sub folder. Please go through them step by step to save time and make any edits you feel neccessary. If this is the first ReadMe file you are reading for this calibration, please go back a folder
and read the ReadMe file in that folder"

-Sharath Patlolla
