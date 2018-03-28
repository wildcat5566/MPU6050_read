#include"Wire.h"
#include"I2Cdev.h"
#include"MPU6050.h"

#define ExtResetPin 23

MPU6050 mpu;
float imu[6];
int16_t ax, ay, az, gx, gy, gz;
float gx_offset = -502.42;
float gy_offset = 248.72;
float gz_offset = 15.75;
float ax_offset = 140.79;
float ay_offset = 122.76;
float az_offset = 1219.97;
float gyro_sen = 131.0;
float acc_sen = 16384.0;

void setup() {
  pinMode(ExtResetPin, OUTPUT);
  digitalWrite(ExtResetPin, LOW);
  delay(10);
  digitalWrite(ExtResetPin, HIGH);
  
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();
  mpu.setRate(400);
  Serial.println(mpu.testConnection() ? "MPU6050 connection successful" : "MPU6050 connection failed");
}

void loop() {
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  imu[0] = (ax - ax_offset) / acc_sen;
  imu[1] = (ay - ay_offset) / acc_sen;
  imu[2] = (az - az_offset) / acc_sen;
  imu[3] = (gx - gx_offset) / gyro_sen;
  imu[4] = (gy - gy_offset) / gyro_sen;
  imu[5] = (gz - gz_offset) / gyro_sen;
  for(int i = 0; i < 6; i ++){
    Serial.print(imu[i]);   Serial.print(", ");
  }
  Serial.println();
}
