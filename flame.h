/*\
 |*| Author:
 |*|   Justin Taylor
 |*|   pianojet@gmail.com
 |*|   July 2015
 |*|
 |*| Some basic bits taken from
 |*|   the Adafruit_NeoPixel code for "strandtest"
 \*/

#ifndef __FLAME_H__
#define __FLAME_H__

#include <stdlib.h>
#include <stdint.h>

using namespace std;


// An individual flame that is logically represented by a vector style container
//   with which the size is the size of the flame, and each intensity value
//   represents a percent of brightness.  The intensities have a gaussian distribution
//   within the size of the vector to mimic a smooth, individual flame.  Each "step"
//   will increase the flame intensities to an initialized max, then back down, ebbing
//   for as long as the given "strength" value.
class Flame {
private:
    uint8_t
        size,
        strength,
        cycles,
        amplitudePercent,
        rage,
        maxIntense;

    bool
        grow,
        dead;

    uint8_t * flameIntensities;
    
public:
    Flame(const uint8_t w, const uint8_t r = 1.0, const uint8_t mI = 1.0, const uint8_t s = 1);
    void makeTest();
    void step();
    void newIntensities();
    void next();
    uint8_t getSize();
    float gaussian(uint8_t w);
    bool isDead();
    ~Flame();

    uint8_t & operator[](uint8_t i);
};

#endif
