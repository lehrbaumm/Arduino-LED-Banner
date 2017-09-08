#include <Adafruit_NeoPixel.h>
#include "LED_Lib.h"




#define PIN            6
#define NUMPIXELS      420
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
uint32_t low = pixels.Color(0, 0, 0); 
uint32_t high = pixels.Color(0, 100, 100);


int delayval = 10; // delay for half a second

int incomingByte = 0;   // for incoming serial data

void out_bytes(int Screen[7][60]) {
  for (int i = 0; i < 7; i++) {
    for (int j = 0; j < 60; j++) {
      int position = (i*60)+(j);
      if (Screen[i][j] == 1)
      {
        pixels.setPixelColor(position, high);
      }
      else
      {
        pixels.setPixelColor(position, low);
      }
    }
  }
      pixels.show();
}

int Ordered[7][60] = { 0 };
int SCREEN[7][60] = { 0 };

void setup() {
  Serial.begin(9600);
  pixels.begin();
  pixels.show();
  char Output[14] = "LAB Team\0";
  int stream[420 * 3] = { 0 };
  generate_from_string(SCREEN, Output);
  order(SCREEN, Ordered);
}
int counter = 0;

void loop() {
  out_bytes(Ordered);
  if (Serial.available() > 0) {
    char data[11] = { 0 };
    data[10] = 0;
    int i = 0;
    while ((incomingByte = Serial.read()) != -1) {
      // read the incoming byte:
      data[i] = incomingByte;
      Serial.println(data);
      Serial.println(incomingByte);
      delay(delayval*4);
      i++;
    }
    for (i = 0; i < 7; i++) {
      for (int j = 0; j < 60; j++) {
        SCREEN[i][j] = 0;
        Ordered[i][j] = 0;
      }
    }
    generate_from_string(SCREEN, data);
    order(SCREEN, Ordered);
    counter = -1;
  }
  else if (counter % 2 == 0) {
    move_left(SCREEN);
    order(SCREEN, Ordered);
  }
  counter++;
}
