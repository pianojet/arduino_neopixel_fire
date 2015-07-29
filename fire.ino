/*\
|*| Author: 
|*|   Justin Taylor
|*|   pianojet@gmail.com
|*|   July 2015
|*|
|*| Some basic bits taken from 
|*|   the Adafruit_NeoPixel code for "strandtest"
\*/

#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <vector>

#include <Adafruit_NeoPixel.h>
#include "flame.h"
#include "firepit.h"
#include "palette.h"

using namespace std;

#define PIN 6
#define STRIPSIZE 60
#define DELAY 10

// Global settings for flame parameters and reasonable ranges.
// mins and maxes (not impl) may be helpful later when
// user control of flame parameters is desired via controllers.
int numFlamesLevel = 9;
int numFlamesMin = 1;
int numFlamesMax = 12;

int fSizeRange[] = {4, 10};
int fSizeMin = 3;
int fSizeMax = 30;

int rageRange[] = {20, 50};
int rageMin = 10;
int rageMax = 100;

int maxIntenseRange[] = {90, 100};
int maxIntenseMin = 50;
int maxIntenseMax = 100;

int strengthRange[] = {1, 2};
int strengthMin = 1;
int strengthMax = 3;

int offsetRange[] = {0, 31};
int offsetMin = 0;
int offsetMax = 31;

// standard nepixel strip of 60 LEDs
Adafruit_NeoPixel * strip = new Adafruit_NeoPixel(STRIPSIZE, PIN, NEO_GRB + NEO_KHZ800);

// "firepit" container of flames
FirePit * firepit = new FirePit(STRIPSIZE, 1, PALETTE_REG_FIRE);

// calculate randomized flame parameters using reasonable ranges from above
// then push to the firepit container
void addFlame(FirePit * pit)
{
    int rSize = random(fSizeRange[0], fSizeRange[1]);
    float rRage = random(rageRange[0], rageRange[1])/100;
    float rIntense = random(maxIntenseRange[0], maxIntenseRange[1])/100;
    int rStrength = random(strengthRange[0], strengthRange[1]);
    int rOffset = random(offsetRange[0], offsetRange[1]);

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
  delay(DELAY);
  // testColor(strip.Color(255, 0, 0), 50); // Red
  // testColor(strip.Color(0, 255, 0), 50); // Red
  // testColor(strip.Color(0, 0, 255), 50); // Red

  // rainbow(20);
}
