/*\
|*| Author: 
|*|   Justin Taylor
|*|   pianojet@gmail.com
|*|   July 2015
|*|
|*| Some basic bits taken from 
|*|   the Adafruit_NeoPixel code for "strandtest"
\*/

#ifndef __FIREPIT_H__
#define __FIREPIT_H__

#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <vector>

#include <Adafruit_NeoPixel.h>
#include "flame.h"
#include "palette.h"

using namespace std;

// Container and processor for Flames, with a bit of facade for handling palette, 
//   NeoPixel strip, and flames easily.  Use pushFlame() to push Flame objects
//   into the container, fire() to drive iterations and processing for flames,
//   and fireToLED to transfer output values to a given NeoPixel strip.
//
// When intensities are calculated for each 'step' (the ebb and flow of the flames), 
//   the follow steps occur under the hood:

//   1) remove flames that are dead
//   2) 'step' all existing flames (flame objects increments/decrements their own intensity)
//   3) determine new intensities (which translate to palette indices for eventual output)
//      3.a) reset all intensities (merging will occur later and this will prevent bloat)
//      3.b) "setFlame" directly adds the intensities of first flame to pit
//      3.c) each other flame is merged in, with simple averages during overlap
//   1) 
//   3) calculate intensity values for the whole pit based on flame intensities and merges
//   5)
//
class FirePit {
  private:
    int 
      maxFlames,
      activeFlames;
    float size;

    vector<int> flameOffsets;
    vector<int> paletteIndexSpan;
    vector<float> intensityValueSpan;
    vector<Flame *> flames;
    vector< vector<int> > palette; // local palette
    vector< vector<int> > colorValueSpan; // RGB values for the entire strip

    void resetIntensities();
    void setFlame(Flame * flamePtr, int offset = 0);
    void mergeFlame(Flame * flamePtr, int offset = 0);
    void mergeIntensities(vector<float> intensities, int offset);
    void cleanFlames();
    void stepFlames();
    void lightFlames();
    void updateColors();

  public:
    FirePit(const int s, const int m, const int p[][RGB]);
    void pushFlame(Flame * flamePtr, int offset = 0);
    void fire();
    void printColors();
    int getSize();
    int getMaxFlames();
    int getActiveFlames();
    void fireToLED(Adafruit_NeoPixel * neo_strip);
    vector< vector<int> > getPalette();
    ~FirePit();
};

#endif
