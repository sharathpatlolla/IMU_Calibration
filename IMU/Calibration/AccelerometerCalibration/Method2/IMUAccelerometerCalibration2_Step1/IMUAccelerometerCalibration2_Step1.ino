

#include <Wire.h>
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
float tolerance=0.04;
long int ti;

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

    // Set accelerometers low pass filter at 5Hz
  I2CwriteByte(MPU9250_ADDRESS,29,0x06);
  // Set gyroscope low pass filter at 5Hz
  I2CwriteByte(MPU9250_ADDRESS,26,0x06);
  
  // Configure gyroscope range
  I2CwriteByte(MPU9250_ADDRESS,27,GYRO_FULL_SCALE_250_DPS);
  // Configure accelerometers range
  I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_2_G);

  ti=millis();
  
}

void loop()
{  
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

  if((0.98<Converted_ax)&&(Converted_ax<1.02)){
    Serial.print("Gravity is in positive X axis \t \t");
  }
  else if((Converted_ax<-0.98)&&(Converted_ax>-1.02)){
        Serial.print("Gravity is in negative X axis \t \t");
  }
  else if((0.98<Converted_ay)&&(Converted_ay<1.02)){
        Serial.print("Gravity is in positive Y axis \t \t");
  }
  else if((Converted_ay<-0.98)&&(Converted_ay>-1.02)){
        Serial.print("Gravity is in negative Y axis \t \t");
  }  
  else if((0.98<Converted_az)&&(Converted_az<1.02)){
        Serial.print("Gravity is in positive Z axis \t \t");
  }
  else if((Converted_az<-0.98)&&(Converted_az>-1.02)){
        Serial.print("Gravity is in negative Z axis \t \t");
  }
  else if( ((1/sqrt(3)-tolerance < Converted_ax) && (Converted_ax < 1/sqrt(3)+tolerance) && (1/sqrt(3)-tolerance < Converted_ay)&&(Converted_ay < 1/sqrt(3)+tolerance) && (1/sqrt(3)-tolerance < Converted_az)&&(Converted_az < 1/sqrt(3)+tolerance)) || ((-1/sqrt(3)+tolerance > Converted_ax) && (Converted_ax > -1/sqrt(3)-tolerance) && (-1/sqrt(3)+tolerance > Converted_ay)&&(Converted_ay > -1/sqrt(3)-tolerance) && (-1/sqrt(3)+tolerance > Converted_az)&&(Converted_az > -1/sqrt(3)-tolerance))  ){    
    Serial.print("IMU is along (1,1,1) or (-1,-1,-1)\t \t");     
  }

  Serial.print (Converted_ax,4); 
  Serial.print ("\t");
  Serial.print (Converted_ay,4);
  Serial.print ("\t");
  Serial.print (Converted_az,4);  
  Serial.print ("\t \t");
  

  Serial.println("");
}


