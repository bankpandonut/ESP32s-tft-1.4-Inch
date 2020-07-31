#include <Adafruit_GFX.h> // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <SPI.h>

#include "icons.h"
// These pins will also work for the 1.8" TFT shield

#include <Wire.h>
#include "MAX30105.h" 
#include "heartRate.h" 

MAX30105 particleSensor;

//ESP32-WROOM
#define TFT_DC 12 //A0
#define TFT_CS 13 //CS
#define TFT_MOSI 14 //SDA
#define TFT_CLK 27 //SCK
#define TFT_RST 23 
#define TFT_MISO 0
 
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_CLK, TFT_RST);

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred
 
float beatsPerMinute;
int beatAvg;

void setup(void) 
{
  Serial.begin(115200);
  Serial.println("Initializing...");

  tft.initR(INITR_BLACKTAB);      
  tft.setRotation(0);
  tft.fillScreen(ST7735_BLACK);
  //tft.fillScreen(ST7735_WHITE);

  tft.setCursor(65,35);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print("Heart Rate");

  tft.setCursor(55,88);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(1);
  tft.print("Oxygen Blood");

  int h1 = 20,w1 = 123, row1, col1, buffidx1=0;
  for (row1=5; row1<h1; row1++) 
  { // For each scanline...
    for (col1=93; col1<w1; col1++) 
    { // For each pixel...
      //To read from Flash Memory, pgm_read_XXX is required.
      //Since image is stored as uint16_t, pgm_read_word is used as it uses 16bit address
      tft.drawPixel(col1, row1, pgm_read_word(fullbattery + buffidx1));
      buffidx1++;
    } // end pixel
  }
  
  int h = 65,w = 50, row, col, buffidx=0;
  for (row=30; row<h; row++)
  { // For each scanline...
    for (col=10; col<w; col++)
    { // For each pixel...
      //To read from Flash Memory, pgm_read_XXX is required.
      //Since image is stored as uint16_t, pgm_read_word is used as it uses 16bit address
      tft.drawPixel(col, row, pgm_read_word(heart + buffidx));
      buffidx++;
    } // end pixel
  }
  
  int h2 = 120,w2 = 50, row2, col2, buffidx2=0;
  for (row2=85; row2<h2; row2++)
  { // For each scanline...
    for (col2=10; col2<w2; col2++)
    { // For each pixel...
      //To read from Flash Memory, pgm_read_XXX is required.
      //Since image is stored as uint16_t, pgm_read_word is used as it uses 16bit address
      tft.drawPixel(col2, row2, pgm_read_word(oxygen + buffidx2));
      buffidx2++;
    } // end pixel
  }
   
// Initialize sensor
  if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30105 was not found. Please check wiring/power. ");
    while (1);
  }
  Serial.println("Place your index finger on the sensor with steady pressure.");
 
  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED

}
char _buffer[7];
void loop() 
{
  long irValue = particleSensor.getIR();
 
  if (checkForBeat(irValue) == true)
  {
    //We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();
 
    beatsPerMinute = 60 / (delta / 1000.0);
 
    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; //Store this reading in the array
      rateSpot %= RATE_SIZE; //Wrap variable
 
      //Take average of readings
      beatAvg = 0;
      for (byte x = 0 ; x < RATE_SIZE ; x++)
        beatAvg += rates[x];
        beatAvg /= RATE_SIZE;
    }
  }
 
  Serial.print("IR=");
  Serial.print(irValue);
  Serial.print(", BPM=");
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.print(beatAvg);
 
  if (irValue < 50000)
  {
    Serial.print(" No finger?");
    Serial.println();
  }
  tft.setCursor(85,55);
  tft.setTextColor(ST7735_WHITE);
  tft.setTextSize(2);
  tft.print(beatAvg);
  delay(2000);
}
