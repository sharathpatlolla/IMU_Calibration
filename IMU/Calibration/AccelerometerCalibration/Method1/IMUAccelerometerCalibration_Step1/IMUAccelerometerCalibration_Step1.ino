/*
THIS CODE IS FOR ACCELEROMETER CALIBRATION

THIS ARDUINO CODE WILL HELP YOU IN POSITIONING THE IMU IN CORRECT POSITION (WHERE THE ACCELERATION COMPONENTS ARE EACH  1/SQRT(3) OR -1/SQRT(3) IN THE UNITS OF g 
THE TOLERENCE USED IS 0.02

WHEN THE POSITION IS ALMOST CORRECT YOU CAN SEE "WHATS UP" IN THE SERIAL MONITOR 
AFTER THIS IS DONE, OPEN "IMUAccelerometerCalibration_Step2"
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
  

  // Read accelerometer and gyroscope
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS,0x3B,14,Buf);
  
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

  if( ((1/sqrt(3)-0.02 < Converted_ax) && (Converted_ax < 1/sqrt(3)+0.02) && (1/sqrt(3)-0.02 < Converted_ay)&&(Converted_ay < 1/sqrt(3)+0.02) && (1/sqrt(3)-0.02 < Converted_az)&&(Converted_az < 1/sqrt(3)+0.02)) || ((-1/sqrt(3)+0.02 > Converted_ax) && (Converted_ax > -1/sqrt(3)-0.02) && (-1/sqrt(3)+0.02 > Converted_ay)&&(Converted_ay > -1/sqrt(3)-0.02) && (-1/sqrt(3)+0.02 > Converted_az)&&(Converted_az > -1/sqrt(3)-0.02))  ){    
    Serial.print (Converted_ax,4); 
    Serial.print ("\t");
    Serial.print (Converted_ay,4);
    Serial.print ("\t");
    Serial.print (Converted_az,4);  
    Serial.print ("\t \t");
    Serial.print("THIS IS THE REQUIRED ANGLE \t \t");     
  }
  else{
    
    Serial.print (Converted_ax,4); 
    Serial.print ("\t");
    Serial.print (Converted_ay,4);
    Serial.print ("\t");
    Serial.print (Converted_az,4);  
    Serial.print ("\t \t"); 
  }
  Serial.println("");
}






