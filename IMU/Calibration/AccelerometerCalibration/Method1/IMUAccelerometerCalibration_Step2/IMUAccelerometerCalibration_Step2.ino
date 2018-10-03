/*
 * //THIS CODE IS FOR ACCELEROMETER CALIBRATION

BEFORE RUNNING THIS CODE RUN THE "IMUAccelerometerCalibration_Attempt1" FILE IN ARDUINO IDE.
ONCE THE POSITION(POSITIVE g) IS CORRECT(FROM THE "IMUAccelerometerCalibration_Attempt1" FILE) RUN THIS CODE 
FIRST IS POSITIVE g POSITION ,

THIS ARDUINO CODE WILL HELP YOU IN IMPORTING THE VALUES INTO MATLAB ////MAKE SURE SERIAL MONITOR IS CLOSED WHEN YOU RUN THE MATLAB CODE
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


REFER TO "http://cache.freescale.com/files/sensors/doc/app_note/AN4399.pdf" FOR MORE INFORMATION

 */

 
#include <Wire.h>
#include <TimerOne.h>
#include "MatrixMath.h"

#define    MPU9250_ADDRESS            0x68

#define    GYRO_FULL_SCALE_250_DPS    0x00  
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00  
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18


float ConversionFactor_Gyro_2000DPS=16.4;
float ConversionFactor_Acc_16g=2048;
float ConversionFactor_Gyro_250DPS=131;
float ConversionFactor_Acc_2g=16384;
long int ti;
volatile bool intFlag=false;

int sgn(int val){
   if (val>0)
    return 1;
   if (val<0)
    return -1;
   return 0;  
}

void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();
  
  // Read Nbytes
  Wire.requestFrom(Address, Nbytes); 
  uint8_t index=0;
  while (Wire.available())
    Data[index++]=Wire.read();
}

// Write a byte (Data) in device (Address) at register (Register)
void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}

void setup()
{
  Wire.begin();
  Serial.begin(115200);
 
  // Configure gyroscope range
  I2CwriteByte(MPU9250_ADDRESS,27,GYRO_FULL_SCALE_250_DPS);
  // Configure accelerometers range
  I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_2_G);
  
  Timer1.initialize(2000);         // initialize timer1, and set a 1/2 second period
  Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt
  
  Serial.println("TIME(in ms)ax \t ay \t az \t gx \t gy \t gz \t theta_az \t Filtered_THETA \t");
  // Store initial time 
  ti=millis();
  
}

void callback()
{ 
  intFlag=true;
  digitalWrite(13, digitalRead(13) ^ 1);
}

void loop()
{  
  while (!intFlag);
   intFlag=false;
  
  // ____________________________________
  // :::  accelerometer and gyroscope ::: 

  // Read accelerometer and gyroscope
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS,0x3B,14,Buf);
  
  // Create 16 bits values from 8 bits data
  
  // Accelerometer
  int16_t ax=-(Buf[0]<<8 | Buf[1]);
  int16_t ay=-(Buf[2]<<8 | Buf[3]);
  int16_t az=Buf[4]<<8 | Buf[5];

  // Gyroscope
  int16_t gx=-(Buf[8]<<8 | Buf[9]);
  int16_t gy=-(Buf[10]<<8 | Buf[11]);
  int16_t gz=Buf[12]<<8 | Buf[13];
  
  float Converted_ax=(float)ax/(float)ConversionFactor_Acc_2g;
  float Converted_ay=(float)ay/(float)ConversionFactor_Acc_2g;
  float Converted_az=(float)az/(float)ConversionFactor_Acc_2g;
  float Converted_gx=(float)gx/(float)ConversionFactor_Gyro_250DPS;
  float Converted_gy=(float)gy/(float)ConversionFactor_Gyro_250DPS;
  float Converted_gz=(float)gz/(float)ConversionFactor_Gyro_250DPS;

  float temp1=sgn(Converted_az)*sqrt(0.1*Converted_ax*Converted_ax + Converted_az*Converted_az);
  float RollAngle=atan2(Converted_ay,temp1)*180/3.14;//Roll angle is wrt x axis (phi)
  float temp2=sqrt(Converted_ay*Converted_ay + Converted_az*Converted_az);
  float PitchAngle=atan2(-Converted_ax,temp2)*180/3.14;//pitch angle is wrt y axis(theta)
  

  Serial.print (millis()-ti,DEC);
  Serial.print ("\t");
  Serial.print (Converted_ax,4); 
  Serial.print ("\t");
  Serial.print (Converted_ay,4);
  Serial.print ("\t");
  Serial.print (Converted_az,4);
  Serial.println ("");
}

