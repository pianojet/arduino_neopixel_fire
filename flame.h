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

#include <StandardCplusplus.h>
#include <system_configuration.h>
#include <unwind-cxx.h>
#include <utility.h>
#include <vector>

using namespace std;


// An individual flame that is logically represented by a vector style container
//   with which the size is the size of the flame, and each intensity value 
//   represents a percent of brightness.  The intensities have a gaussian distribution
//   within the size of the vector to mimic a smooth, individual flame.  Each "step" 
//   will increase the flame intensities to an initialized max, then back down, ebbing
//   for as long as the given "strength" value. 
class Flame {
  private:
    int
      width,
      strength,
      cycles;

    float
      rage,
      maxIntense,
      amplitudePercent,
      rage_inc;

    bool
      grow,
      dead;

    vector<float> flameIntensities;

  public:
    Flame(const int w, const float r = 1.0, const float mI = 1.0, const int s = 1);
    void makeTest();
    void step();
    void newIntensities();
    void next();
    int getWidth();
    float gaussian(int w);
    bool isDead();
    vector<float> getIntensities();
    ~Flame();
};

#endif
