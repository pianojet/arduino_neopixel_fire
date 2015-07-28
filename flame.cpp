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

#include "flame.h"

using namespace std;

Flame::Flame(const int w, const float r, const float mI, const int s)
  : width(w), rage(r), maxIntense(mI), strength(s)
{
  amplitudePercent = 0;
  grow = true;
  rage_inc = 15*(rage);
  for (int i = 0; i < width; i++)
  {
    this->flameIntensities.push_back(0.0);
  }
  cycles = 0;
  dead = false;
}

bool Flame::isDead()
{
  return this->dead;
}

Flame::~Flame()
{
  
}
