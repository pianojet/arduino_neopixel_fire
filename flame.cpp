/*\
|*| Author: 
|*|   Justin Taylor
|*|   pianojet@gmail.com
|*|   July 2015
|*|
|*| Some basic bits taken from 
|*|   the Adafruit_NeoPixel code for "strandtest"
\*/
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

void Flame::step()
{
  printf("\nFlame step()\n");
  if (this->grow) this->amplitudePercent += this->rage_inc;
  else this->amplitudePercent -= this->rage_inc;
  if (this->amplitudePercent >= 100) this->grow = false;
  else if (this->amplitudePercent <= 0)
  {
    this->grow = true;
    this->cycles++;
    if (this->cycles >= this->strength) this->dead = true;
  }
  printf("ampPct=%f; dead=%d;", this->amplitudePercent, this->dead);
}

void Flame::newIntensities()
{
  printf("\nFlame, newIntensities()\n");
  float percent;
  for (int i = 0; i < this->width; i++)
  {
    percent = this->gaussian(i) * (this->amplitudePercent/100);
    this->flameIntensities[i] = percent;
    printf(" %f ", percent);
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
