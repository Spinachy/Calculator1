/*
  AJM Apr 2022

  -- First attempt at a "Calculator application"
  -- Display :
  -- Three Sparkfun "OpenSegment" 7 segment displays, each with 4 digits, for a total of 12 digits of display
  --
  -- I am driving these on an I2C bus, using addresses "0x71", "0x72", and "0x73"
  --
  --
  -- Product Page is here : https://www.sparkfun.com/products/retired/11644
  --
  --Tutorial Here : https://learn.sparkfun.com/tutorials/using-opensegment
  --
  -- See also, similar:  Serial7Segment by Jim Lindblom.(https://www.sparkfun.com/products/11442)
  -- 
  -- See:  https://github.com/sparkfun/Serial7SegmentDisplay/wiki/Serial-7-Segment-Display-Datasheet
  -- 
  -- See: https://github.com/sparkfun/Serial7SegmentDisplay/tree/master/firmware/Serial%207-Segment%20Display/Arduino_Examples
  --
  -- Wiring :
  -- Arduino VIN to Breadboard & then on to "opensegment" "PWR" pin
  -- Arduino Gnd to Breadboard & then on to "opensegment" "GND" pin
  -- Arduino A5 to SCL
  -- Arduino A4 to SDA
 
*/

#include <Wire.h>

#define DISPLAY_ADDRESS0 0x71 // Rightmost 4 digits of display. This is the default address of the OpenSegment 
#define DISPLAY_ADDRESS1 0x72 // Centre 4 digirs of disply. I used the sketch "SparkQuad7ChangeI2C" to program this address in to the 2nd display
#define DISPLAY_ADDRESS2 0x73 // Leftmost 4 digits of display. I used the sketch "SparkQuad7ChangeI2C" to program this address in to the 3rd display

void setup() 
{
  Wire.begin(); //Join the bus as master

  //By default .begin() will set I2C SCL to Standard Speed mode of 100kHz
//  Wire.setClock(400000); //Optional - set I2C SCL to High Speed Mode of 400kHz

  Serial.begin(9600); //Start serial communication at 9600 for debug statements
  Serial.println("OpenSegment Example Code");

  //Send the reset command to the display - this forces the cursor to return to the beginning of the display
  HighBrightness(DISPLAY_ADDRESS2);
  HighBrightness(DISPLAY_ADDRESS1);
  HighBrightness(DISPLAY_ADDRESS0);
  clearDisplay(DISPLAY_ADDRESS2);
  clearDisplay(DISPLAY_ADDRESS1);
  clearDisplay(DISPLAY_ADDRESS0);
}

int delayVal = 500;

void loop()
{
// char str[13] = "012345678901";
// char *strPtr = str;
// while(strPtr++)
// {
  //if(*strPtr == '9') *strPtr = '0';
  //else (*strPtr)++;
// }
  FillDisplayString("012345678901");
  delay(delayVal);
  FillDisplayString("123456789010");
  delay(delayVal);
  FillDisplayString("234567890101");
  delay(delayVal);
  FillDisplayString("345678901012");
  delay(delayVal);
  FillDisplayString("456789010123");
  delay(delayVal);
  FillDisplayString("567890101234");
  delay(delayVal);
  FillDisplayString("678901012345");
  delay(delayVal);
  FillDisplayString("789010123456");
  delay(delayVal);
  FillDisplayString("890101234567");
  delay(delayVal);
  FillDisplayString("901012345678");
  delay(delayVal);
  FillDisplayString("010123456789");
  delay(delayVal);
  FillDisplayString("101234567890");
  delay(delayVal);
}



void SendTestPattern(int DisplayToUse) 
{

  i2cSendValue("0123",DisplayToUse); //Send the four characters to the display
  delay(delayVal);
  i2cSendValue("1234",DisplayToUse); //Send the four characters to the display
  delay(delayVal);
  i2cSendValue("2345",DisplayToUse); //Send the four characters to the display
  delay(delayVal);
  i2cSendValue("3456",DisplayToUse); //Send the four characters to the display
  delay(delayVal);
  i2cSendValue("4567",DisplayToUse); //Send the four characters to the display
  delay(delayVal);
  i2cSendValue("5678",DisplayToUse); //Send the four characters to the display
  delay(delayVal);
  i2cSendValue("6789",DisplayToUse); //Send the four characters to the display
  delay(delayVal);
  i2cSendValue("7890",DisplayToUse); //Send the four characters to the display
  delay(delayVal);
  i2cSendValue("8901",DisplayToUse); //Send the four characters to the display
  delay(delayVal);
  i2cSendValue("9012",DisplayToUse); //Send the four characters to the display
  delay(delayVal);
  DecimalPoint(DisplayToUse);
  delay(delayVal);
  clearDisplay(DisplayToUse);
}

//Given a number, i2cSendValue chops up an integer into four values and sends them out over I2C
void i2cSendValue(const char str4DigitValue[], int DisplayToUse)
{
  Wire.beginTransmission(DisplayToUse); // transmit to specified device
  Wire.write(*str4DigitValue++);
  Wire.write(*str4DigitValue++);
  Wire.write(*str4DigitValue++);
  Wire.write(*str4DigitValue++);
  Wire.endTransmission(); //Stop I2C transmission
}

void clearDisplay(int DisplayToUse)
{
  Wire.beginTransmission(DisplayToUse); // transmit to specified device
  Wire.write(0x76);
  Wire.endTransmission(); //Stop I2C transmission
}


void DecimalPoint(int DisplayToUse)
{
  Wire.beginTransmission(DisplayToUse); // transmit to specified device
  Wire.write(0x77);
  Wire.write(0b00001000);     // last 4 bits - bit 0 for left most digit decimal point, bit 3 for right most digit decimal point
  Wire.endTransmission(); //Stop I2C transmission
}


void LowBrightness(int DisplayToUse) 
{
  Serial.println("Low brightness"); //Just a debug statement
  Wire.beginTransmission(DisplayToUse);
  Wire.write(0x7A); // Brightness control command
  Wire.write(10); // Set brightness level: 0% to 100%
  Wire.endTransmission();
//  i2cSendString("b000",DisplayToUse); //Send the four characters to the display
}



void MidBrightness(int DisplayToUse) 
{
  Serial.println("Mid brightness"); //Just a debug statement
  Wire.beginTransmission(DisplayToUse);
  Wire.write(0x7A); // Brightness control command
  Wire.write(50); // Set brightness level: 0% to 100%
  Wire.endTransmission();
}

void HighBrightness(int DisplayToUse) 
{
  Serial.println("High brightness"); //Just a debug statement
  Wire.beginTransmission(DisplayToUse);
  Wire.write(0x7A); // Brightness control command
  Wire.write(100); // Set brightness level: 0% to 100%
  Wire.endTransmission();
}

//Given a string, i2cSendString chops up the string and sends out the first four characters over i2c
void i2cSendString(const char toSend[],int DisplayToUse)
{
  Wire.beginTransmission(DisplayToUse); // transmit to device #1
  for(byte x = 0 ; x < 4 ; x++)
    Wire.write(toSend[x]); //Send a character from the array out over I2C
  Wire.endTransmission(); //Stop I2C transmission
}


//Given a string, i2cSendString chops up the string and sends out the first four characters over i2c
void FillDisplayString(const char toSend[])
{
  Wire.beginTransmission(DISPLAY_ADDRESS2); // transmit to device 
  Wire.write(0x79); // set cursor position
  Wire.write(0x00); // to the left most position
  for(byte x = 0 ; x < 4 ; x++)
    Wire.write(toSend[x]); //Send a character from the array out over I2C
  Wire.endTransmission(); //Stop I2C transmission
  Wire.beginTransmission(DISPLAY_ADDRESS1); // transmit to device 
  Wire.write(0x79); // set cursor position
  Wire.write(0x00); // to the left most position
  for(byte x = 4 ; x < 8 ; x++)
    Wire.write(toSend[x]); //Send a character from the array out over I2C
  Wire.endTransmission(); //Stop I2C transmission
  Wire.beginTransmission(DISPLAY_ADDRESS0); // transmit to device 
  Wire.write(0x79); // set cursor position
  Wire.write(0x00); // to the left most position
  for(byte x = 8 ; x < 12 ; x++)
    Wire.write(toSend[x]); //Send a character from the array out over I2C
  Wire.endTransmission(); //Stop I2C transmission
}
