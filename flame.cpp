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
  amplitudePercent = 0.0;
  grow = true;
  rage_inc = 15*(rage);
  for (int i = 0; i < width; i++)
  {
    this->flameIntensities.push_back(0.0);
  }
  cycles = 0;
  dead = false;
}

// produces a maximum intensity for the flame, useful for test
void Flame::makeTest()
{
  printf("\nFlame, makeTest()\n");
  float percent;
  for (int i = 0; i < this->width; i++)
  {
    percent = this->gaussian(i);
    this->flameIntensities[i] = percent;
    printf(" %f ", percent);
  }
}

// processing for how to alter the flame.
// We need to choose whether to increase or decrease the
// intensity, whether to render the flame dead, and determine what
// relative amplitude the flame's gaussian distribution will be
// (which translates to the intensity later)
void Flame::step()
{
  if (this->grow) this->amplitudePercent += this->rage_inc;
  else this->amplitudePercent -= this->rage_inc;
  if (this->amplitudePercent >= 100) this->grow = false;
  else if (this->amplitudePercent <= 0)
  {
    this->grow = true;
    this->cycles++;
    if (this->cycles >= this->strength) this->dead = true;
  }
}

// assign intensities using a gaussian distribution based on intended
// amplitude power
void Flame::newIntensities()
{
  float percent;
  for (int i = 0; i < this->width; i++)
  {
    percent = this->gaussian(i) * (this->amplitudePercent/100);
    this->flameIntensities[i] = percent;
  }
}

void Flame::next()
{
  this->step();
  this->newIntensities();
}

int Flame::getWidth()
{
  return this->width;
}

// gaussian function using Flame's own parameters to smooth
// the flame intensities.
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
