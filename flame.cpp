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
#include <math.h>

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

void Flame::makeTest()
{
  int percent;
  for (int i = 0; i < this->width; i++)
  {
    percent = this->gaussian(i);
    this->flameIntensities[i] = percent;
  }
}

void Flame::next()
{

}

int Flame::getWidth()
{
  return this->width;
}

float Flame::gaussian(int w)
{
  float m = 6.0 - (5.0*this->maxIntense);// Math.sqrt(2 * Math.PI);
  float e = exp(-pow(w - (this->width/2.5), 2) / (2 * this->width));
  return e / m;
}

bool Flame::isDead()
{
  return this->dead;
}

vector<float> Flame::getIntensities()
{
  return this->flameIntensities;
}

Flame::~Flame()
{
  
}
