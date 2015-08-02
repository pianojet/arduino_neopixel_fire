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

#include <Adafruit_NeoPixel.h>
#include "flame.h"
#include "palette.h"


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
    uint8_t
        maxFlames,
        activeFlames,
        size;

    uint8_t palette[PALETTE_ROWS][RGB];
    
    Flame ** flames;
    int8_t * flameOffsets;
    uint8_t * colorValueSpan;
    uint8_t * intensityValueSpan;
    
    void resetIntensities();
    void setFlame(Flame * flamePtr, uint8_t offset = 0);
    void mergeFlame(Flame * flamePtr, uint8_t offset = 0);
    
public:
    FirePit(const uint8_t s, const uint8_t m, const uint8_t p[][RGB]);
    void pushFlame(Flame * flamePtr, int8_t offset = 0);

    void cleanFlames();
    void stepFlames();
    void lightFlames();
    void updateColors();


    void fire();
    uint8_t getSize();
    uint8_t getMaxFlames();
    uint8_t getActiveFlames();
    void fireToLED(Adafruit_NeoPixel * neo_strip);
    ~FirePit();
};

#endif
