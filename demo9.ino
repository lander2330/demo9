// Sketch: demo9.ino
// Version: Version 2026.06.05
// Author: Larry Anderson
//
// This ESP32 microcontroller project shows how to access the ds3231 real time clock module.
// I typically like to include the clock module in my projects so I can
// include the current date and time when writing various sensor information
// to a microsd memory card for later historical graphing and/or analysis. 

// DS3231 realtime clock library
#include "RTClib.h"
RTC_DS3231 rtc;

// I2C library
#include <Wire.h>
#define SDA_PIN 21
#define SCL_PIN 22

void setup()
  {
  Serial.begin(9600);
  delay(2000);

  Wire.begin(SDA_PIN,SCL_PIN);

  // if clock initialization fails
  if (! rtc.begin())
    {
    Serial.println("check clock wiring and clock battery");
    while (true)
      {
      // loop forever          
      }    
    }

  // if clock lost power, the date and time is not accurate
  if (rtc.lostPower())
    {
    Serial.println("Show how to set clock to 06/05/2026 15:01:02");
    setClock("20260605150102"); // date and time specified as ccyymmddhhmmss 
    } 
  }

void loop()
  {
  showDate();
  showTime();
  showDuration();
  delay(1000);
  }

void showDate()
  {
  DateTime datetime;
  char myDate[10+1] = "mm/dd/ccyy";
  datetime = rtc.now();
  sprintf(myDate, "%02d/%02d/%04d", datetime.month(), datetime.day(), datetime.year());     // mm/dd/ccyy
  Serial.print("Date:");
  Serial.println(myDate);  
  } 

void showTime()
  {
  DateTime datetime;
  char myTime[8+1] = "hh:mm:ss"; 
  datetime = rtc.now();
  sprintf(myTime, "%02d:%02d:%02d", datetime.hour(), datetime.minute(), datetime.second()); // hh:mm:ss
  Serial.print("Time:");
  Serial.println(myTime); 
  }   

void showDuration()
  {
  unsigned long durationMillis = 0;
  unsigned long durationSeconds = 0;
  unsigned long durationMinutes = 0;
  unsigned long durationHours = 0;
  unsigned long durationDays = 0;
  char myDuration[15+1] = "00d:00h:00m:00s";

  durationMillis = millis(); // total milliseconds since ESP32 powered on    

  durationDays = durationMillis / (1000L*60L*60L*24L);
  durationMillis = durationMillis % (1000L*60L*60L*24L);
  
  durationHours = durationMillis / (1000L*60L*60L);
  durationMillis = durationMillis % (1000L*60L*60L);

  durationMinutes = durationMillis / (1000L*60L);
  durationMillis = durationMillis % (1000L*60L);
    
  durationSeconds = durationMillis / 1000L;
  durationMillis = durationMillis % 1000L;

  sprintf(myDuration,"%02lu%s%02lu%s%02lu%s%02lu%s",durationDays,"d:",durationHours,"h:",durationMinutes,"m:",durationSeconds,"s");
  Serial.print("Duration:");
  Serial.println(myDuration);
  }

void setClock(char * ccyymmddhhmmss)
  {
  char ccyyChars[4 + 1] = "";
  char monthChars[2 + 1] = "";
  char dayChars[2 + 1] = "";
  char hourChars[2 + 1] = "";
  char minuteChars[2 + 1] = "";
  char secondChars[2 + 1] = "";

  copyChars(ccyymmddhhmmss, 0, 4, ccyyChars);
  copyChars(ccyymmddhhmmss, 4, 2, monthChars);
  copyChars(ccyymmddhhmmss, 6, 2, dayChars);
  copyChars(ccyymmddhhmmss, 8, 2, hourChars);
  copyChars(ccyymmddhhmmss, 10, 2, minuteChars);
  copyChars(ccyymmddhhmmss, 12, 2, secondChars);

  rtc.adjust(DateTime(atoi(ccyyChars), atoi(monthChars), atoi(dayChars), atoi(hourChars), atoi(minuteChars), atoi(secondChars)));
  }

void copyChars(char * inBuf, int startPos, int copyCount, char * outBuf)
  {
  int outPos = 0;
  while (copyCount > 0)
    {
    outBuf[outPos] = inBuf[startPos];
    startPos++;
    outPos++;
    copyCount--;
    }
  outBuf[outPos] = 0;
  } 

// these statements show my software development environment
// Microsoft Windows 11 
// Arduino IDE 2.3.6
// Board: ESP32C6 Dev Module (specifically Espressif Systems ESP32-C6-DEVKITC-1-N8 Microcontroller)
// Using library RTClib at version 2.0.2 in folder: C:\Users\larry\OneDrive\Documents\Arduino\libraries\RTClib 
// Using library Adafruit BusIO at version 1.17.1 in folder: C:\Users\larry\OneDrive\Documents\Arduino\libraries\Adafruit_BusIO 
// Using library Wire at version 3.3.0 in folder: C:\Users\larry\AppData\Local\Arduino15\packages\esp32\hardware\esp32\3.3.0-alpha1\libraries\Wire 
// Using library SPI at version 3.3.0 in folder: C:\Users\larry\AppData\Local\Arduino15\packages\esp32\hardware\esp32\3.3.0-alpha1\libraries\SPI     
  