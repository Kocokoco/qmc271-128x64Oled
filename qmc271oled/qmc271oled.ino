#include <Wire.h> //I2C Arduino Library
#include "U8glib.h"

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE|U8G_I2C_OPT_DEV_0);

#define addr 0x0D //I2C Address for The HMC5883

void setup() {

  Serial.begin(9600);
  Wire.begin();


  Wire.beginTransmission(0x0D); //start talking
  Wire.write(0x0B); // Tell the HMC5883 to Continuously Measure
  Wire.write(0x01); // Set the Register
  Wire.endTransmission();
  Wire.beginTransmission(0x0D); //start talking
  Wire.write(0x09); // Tell the HMC5883 to Continuously Measure
  Wire.write(0x1D); // Set the Register
  Wire.endTransmission();
}

void loop() {

  int x, y, z; //triple axis data

  //Tell the HMC what regist to begin writing data into


  Wire.beginTransmission(0x0D);
  Wire.write(0x00); //start with register 3.
  Wire.endTransmission();

  //Read the data.. 2 bytes for each axis.. 6 total bytes
  Wire.requestFrom(0x0D, 6);
  if (6 <= Wire.available()) {
    x = Wire.read(); //MSB  x
    x |= Wire.read() << 8; //LSB  x
    z = Wire.read(); //MSB  z
    z |= Wire.read() << 8; //LSB z
    y = Wire.read(); //MSB y
    y |= Wire.read() << 8; //LSB y
 
  }

   //Show Values
  Serial.print("X Value: ");
  Serial.println(x);
  Serial.print("Y Value: ");
  Serial.println(y);
  Serial.print("Z Value: ");
  Serial.println(z);
  Serial.print("t Value: ");
  

  u8g.firstPage();  
  do {
  u8g.setFont(u8g_font_gdr14);
  u8g.setPrintPos(0, 15);
  u8g.print("x=");
  u8g.setPrintPos(30, 15);
  u8g.print(x);

  u8g.setPrintPos(0, 36);
  u8g.print("y=");
  u8g.setPrintPos(30,36);
  u8g.print(y);

  u8g.setPrintPos(0, 63);
  u8g.print("z=");
  u8g.setPrintPos(30, 63);
  u8g.print(z);

  
  } while( u8g.nextPage() );
  
  delay(100);
}

