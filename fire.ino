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

// standard nepixel strip of 60 LEDs
Adafruit_NeoPixel * strip = new Adafruit_NeoPixel(STRIPSIZE, PIN, NEO_GRB + NEO_KHZ800);

// "firepit" of flames
FirePit firepit = FirePit(STRIPSIZE, 1, PALETTE_REG_FIRE);

// arduino logic initialization
void setup() {
  Flame * flame = new Flame(5, 0.5, 1.0, 1);
  flame->makeTest();
  firepit.pushFlame(flame);
  strip->begin();
  strip->show(); // Initialize all pixels to 'off'
}

// arduino logic loop
void loop() {
  firepit.fire();
  firepit.fireToLED(strip);
  strip->show();
  // testColor(strip.Color(255, 0, 0), 50); // Red
  // testColor(strip.Color(0, 255, 0), 50); // Red
  // testColor(strip.Color(0, 0, 255), 50); // Red

  // rainbow(20);
}
