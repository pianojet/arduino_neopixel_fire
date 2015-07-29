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

  public:
    FirePit(const int s, const int m, const int p[][RGB]);
    void resetIntensities();
    void pushFlame(Flame * flamePtr, int offset = 0);
    void setFlame(Flame * flamePtr, int offset = 0);
    void mergeFlame(Flame * flamePtr, int offset = 0);
    void mergeIntensities(vector<float> intensities, int offset);
    void cleanFlames();
    void stepFlames();
    void lightFlames();
    void fire();
    void updateColors();
    void printColors();
    int getSize();
    int getMaxFlames();
    int getActiveFlames();
    void fireToLED(Adafruit_NeoPixel * neo_strip);
    vector< vector<int> > getPalette();
    ~FirePit();
};

#endif
