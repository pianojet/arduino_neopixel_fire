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

class Flame {
  private:
    int
      width,
      strength,
      amplitudePercent,
      cycles;

    float
      rage,
      maxIntense,
      rage_inc;

    bool
      grow,
      dead;

    vector<float> flameIntensities;

  public:
    Flame(const int w, const float r = 1.0, const float mI = 1.0, const int s = 1);
    void makeTest();
    void next();
    int getWidth();
    float gaussian(int w);
    bool isDead();
    vector<float> getIntensities();
    ~Flame();
};

#endif
