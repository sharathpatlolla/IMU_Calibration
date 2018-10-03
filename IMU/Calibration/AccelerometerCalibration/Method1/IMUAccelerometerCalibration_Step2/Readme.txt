//THIS CODE IS FOR ACCELEROMETER CALIBRATION

BEFORE RUNNING THIS CODE RUN THE "IMUAccelerometerCalibration_Attempt1" FILE IN ARDUINO IDE.
ONCE THE POSITION(POSITIVE g) IS CORRECT(FROM THE "IMUAccelerometerCalibration_Attempt1" FILE) RUN THIS CODE IN THE POSITIVE g POSITION FIRST,

THIS ARDUINO CODE WILL HELP YOU IN IMPORTING THE VALUES INTO MATLAB ////MAKE SURE SERIAL MONITOR IS CLOSED
NOW OPEN THE "IMU_AccelerationCalibration.m" IN MATLAB AND RUN THE FILE. THAT FILE OUPUTS  THE AVERAGE VALUES OF THE CALIBRATION DATA, NOTE DOWN THE VALUES (LET BE ADCx0,ADCy0,ADCz0)

NOW RUN THE ARDUINO CODE AGAIN FROM THE "IMUAccelerometerCalibration_Attempt1", THIS TIME POSITION THE IMU IN NEGATIVE G POSITION,ONCE DONE
RUN THE ARDUINO CODE FROM "IMUCalibration_Attempt2" AND RUN THE "IMU_AccelerationCalibration.m" IN MATLAB AGAIN. NOTE DOWN THE VALUES AGAIN (LET BE ADCx1,ADCy1,ADCz1)

NOW RUN THE BELOW CODE IN MATLAB TO FIND THE VALUES OF px,py,pz,qx,qy,qz; SUBSTITUTE THE VALUES OF ADCx0,ADCy0,ADCz0,ADCx1,ADCy1,ADCz1 WHICH WERE NOTED DOWN

////////////////////////////
N=16384;
ADCx0=0.6050;
ADCy0=0.5556;
ADCz0=0.5740;
ADCx1=-0.5992;
ADCy1=-0.5746;
ADCz1=-0.5594;

px=2/(sqrt(3)*(ADCx0-ADCx1));
py=2/(sqrt(3)*(ADCy0-ADCy1));
pz=2/(sqrt(3)*(ADCz0-ADCz1));

qx=-N*(ADCx0+ADCx1)/(sqrt(3)*(ADCx0-ADCx1));
qy=-N*(ADCy0+ADCy1)/(sqrt(3)*(ADCy0-ADCy1));
qz=-N*(ADCz0+ADCz1)/(sqrt(3)*(ADCz0-ADCz1));

//////////////////////

After this is done open the "IMUCalibratedAccelerometer" in arduino IDE and replace the values of px,py,pz,qx,qy,qz in the arduino code with the values obtained from the MATLAB code.

References:

1.http://www.lucidarme.me/?p=5057#
2.High-precision calibration of a three axis accelerometer (AN4399), Pedley, Mark
http://cache.freescale.com/files/sensors/doc/app_note/AN4399.pdf (For Method 1)

"There is readme file in every folder and sub folder. Please go through them step by step to save time and make any edits you feel neccessary. If this is the first ReadMe file you are reading for this calibration, please go back a folder
and read the ReadMe file in that folder"

-Sharath Patlolla



