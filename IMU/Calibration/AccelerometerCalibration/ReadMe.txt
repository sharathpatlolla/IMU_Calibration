
\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\READ THE LINE BELOW

In the documentation below, "Method 2" refers to "Method 2" in the final report and "Method 2-2" refers to "Method 1" in the final report.



Calibration of Accelerometer is done in 3 methods. 

Method 1: 
In this method the accelerometer(IMU) is placed in orientation1(+60 degrees in X,Y,Z axes) & orientation2 (-60 degrees in X,Y,Z axes) and the accelerometer readings are taken to calculate the offset matrix and the misalignment matrix. 

Method 2:
In this method the accelerometer(IMU) is placed in 8 orientations, 6 orientations are in which the gravity is in +ve and -ve side of each coordinate axes(+X,-X,+Y,-Y,+Z,-Z), the other 2 orientations are the orientations used in Method1.

Method 2-2:
In this method the accelerometer(IMU) is placed in 6 orientations in which the gravity is in +ve and -ve side of each coordinate axes(+X,-X,+Y,-Y,+Z,-Z)

Usage:
Method 2 or Method 2-2 is best to use in almost any case, It is more easy to calibrate using method 2/2-2 and also the readings are more accurate. Method 1 was just the first method used to calibrate and also Method 1 is not properly documented :P

NOTE:-> "USE METHOD 2 ONLY IF YOU HAVE PROPER APPARATUS TO HOLD THE IMU IN PRECISE ANGLES REQUIRED, IF NOT JUST USE METHOD 2-2 "
     -> "MAKE SURE THAT WHEN YOU HOLD THE IMU IN SPECIFIC POSITION USING SOME KIND OF APPARATUS, DON'T HOLD IT TIGHT BECUASE ACCELEROMETER ACTUALLY MEASURES SPECIFIC FORCES AND IT WOULD GIVE AN ERROR IN THE READINGS "

References:

1.http://www.lucidarme.me/?p=5057#
2.High-precision calibration of a three axis accelerometer (AN4399), Pedley, Mark
http://cache.freescale.com/files/sensors/doc/app_note/AN4399.pdf (For Method 1)
3. Calibration of Deterministic IMU Errors, Prescott, Honors Ferguson, Jeff
http://commons.erau.edu/cgi/viewcontent.cgi?article=1001&context=pr-honors-coe (For Method 2)

"There is readme file in every folder and sub folder. Please go through them step by step to save time and make any edits you feel neccessary. If this is the first ReadMe file you are reading for this calibration, please go back a folder
and read the ReadMe file in that folder"

-Sharath Patlolla
