/*\
|*| Author: 
|*|   Justin Taylor
|*|   pianojet@gmail.com
|*|   July 2015
|*|
|*| Some basic bits taken from 
|*|   the Adafruit_NeoPixel code for "strandtest"
\*/

#include <Adafruit_NeoPixel.h>
#include "flame.h"
#include "firepit.h"
#include "palette.h"

#define PIN 6
#define STRIPSIZE 60
#define DELAY 10

// Global settings for flame parameters and reasonable ranges.
// mins and maxes (not impl) may be helpful later when
// user control of flame parameters is desired via controllers.
int numFlamesLevel = 10;
int numFlamesMin = 1;
int numFlamesMax = 12;

int fSizeRange[] = {9, 20};
int fSizeMin = 3;
int fSizeMax = 30;

int rageRange[] = {60, 99};
int rageMin = 10;
int rageMax = 100;

int maxIntenseRange[] = {90, 100};
int maxIntenseMin = 50;
int maxIntenseMax = 100;

int strengthRange[] = {1, 2};
int strengthMin = 1;
int strengthMax = 3;

int offsetRange[] = {0, 59};
int offsetMin = 0;
int offsetMax = 59;

// standard nepixel strip of 60 LEDs
Adafruit_NeoPixel * strip = new Adafruit_NeoPixel(STRIPSIZE, PIN, NEO_GRB + NEO_KHZ800);

// "firepit" container of flames
FirePit * firepit = new FirePit(STRIPSIZE, numFlamesLevel, PALETTE_REG_FIRE);

// calculate randomized flame parameters using reasonable ranges from above
// then push to the firepit container
void addFlame(FirePit * pit)
{
    uint8_t rSize = random(fSizeRange[0], fSizeRange[1]);
    uint8_t rRage = random(rageRange[0], rageRange[1]);
    uint8_t rIntense = random(maxIntenseRange[0], maxIntenseRange[1]);
    uint8_t rStrength = random(strengthRange[0], strengthRange[1]);
    uint8_t rOffset = random(offsetRange[0], offsetRange[1]);
//    Serial.println("pushing flame");
//    Serial.print("rSize: ");
//    Serial.println(rSize);
//    Serial.print("rRage: ");
//    Serial.println(rRage);
//    Serial.print("rIntense: ");
//    Serial.println(rIntense);
//    Serial.print("rStrength: ");
//    Serial.println(rStrength);
//    Serial.print("rOffset: ");
//    Serial.println(rOffset);
//    Serial.println();

    pit->pushFlame(new Flame(rSize, rRage, rIntense, rStrength), rOffset);
}

// arduino logic initialization
void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));

  strip->begin();
  strip->show(); // Initialize all pixels to 'off'
}

// arduino logic loop
void loop() {
  while (firepit->getActiveFlames() < firepit->getMaxFlames()) addFlame(firepit);
  firepit->fire();
  firepit->fireToLED(strip);
  strip->show();
  delay(5);
  //colorWipe(strip->Color(255, 0, 0), 50); // Red
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip->numPixels(); i++) {
      strip->setPixelColor(i, c);
      strip->show();
      delay(wait);
  }
}

