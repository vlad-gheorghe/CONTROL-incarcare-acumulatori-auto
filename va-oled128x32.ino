/*********************************************************************
This is an example for our Monochrome OLEDs based on SSD1306 drivers

  Pick one up today in the adafruit shop!
  ------> http://www.adafruit.com/category/63_98

This example is for a 128x32 size display using I2C to communicate
3 pins are required to interface (2 I2C and one reset)

Adafruit invests time and resources providing this open source code, 
please support Adafruit and open-source hardware by purchasing 
products from Adafruit!

Written by Limor Fried/Ladyada  for Adafruit Industries.  
BSD license, check license.txt for more information
All text above, and the splash screen must be included in any redistribution
*********************************************************************/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define VT_PIN A0 
#define AT_PIN A1
unsigned long tpmasurare;  // variabila pentru memorare timp masurare (in ms)
float sumatensiune = 0.;   // valoare insumare tensiune pentru calcul medie
float sumacurent = 0.;
int trcurent = 0;
int trtensiune = 0;

float current = 0.;   // valoare curent
float tensiune = 0.; // valoare tensiune

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

void setup()   {                
  Serial.begin(9600);
analogReference(INTERNAL); // punem referinta interna de 1,1V;
  \
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
 
  display.display();
  delay(50);
 pinMode(10, OUTPUT); 
digitalWrite(10, LOW);
  // Clear the buffer.
  display.clearDisplay();

 

}


void loop() {
sumatensiune = 0;

  sumacurent = 0;
    for (int i=1; i <= 20; i++)
  {
 trtensiune = analogRead(VT_PIN);
 
 sumatensiune = sumatensiune + trtensiune;
  trcurent = analogRead(AT_PIN);

  sumacurent = sumacurent + trcurent;
delay (20);  // pauza de 20ms intre masuratori
    }
sumacurent = sumacurent/20.;
sumatensiune = sumatensiune/20.;
tensiune=(float)(97.5+.974)/.974*1.08*sumatensiune/1023;
current=(float)1.08/0.1*sumacurent/1023;  
display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("U:");
  display.fillRect(30, 0, 62, 17, BLACK);display.display();
  //delay(3000);
   display.setCursor(30,0);display.setTextColor(WHITE,BLACK);
   display.println(tensiune+.32);display.display();
    display.setCursor(95,0); display.println("V");
  display.setCursor(0,18);
   
  display.println("I:");
  display.setCursor(30,18);display.setTextColor(WHITE,BLACK);
  display.fillRect(30, 18, 62, 17, BLACK);display.display();
   display.println(current);display.display();
   display.setCursor(95,18); display.println("A");
  display.display();
   if ((tensiune+.32) > 14.1)
  digitalWrite(10,LOW);
  if ((tensiune+.32) < 14.1)
  digitalWrite(10, HIGH);
}

