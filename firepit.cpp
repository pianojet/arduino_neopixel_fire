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

#include <Adafruit_NeoPixel.h>
#include "flame.h"
#include "firepit.h"
#include "palette.h"

using namespace std;

FirePit::FirePit(const int s, const int m, const int p[][RGB])
  : size(s), maxFlames(m)
{
  this->activeFlames = 0;

  // init our local pallate vector from basic array arg
  for (int i = 0; i < PALETTE_ROWS; i++)
  {
    this->palette.push_back( vector<int>() );
    for (int j = 0; j < RGB; j++)
    {
      this->palette[i].push_back(p[i][j]);
    }
  }

  // 
  int zeroRGB[] = {0, 0, 0};
  for (int i = 0; i < this->getSize(); i++)
  {
    this->colorValueSpan.push_back( vector<int>() );
    this->colorValueSpan[i].assign(zeroRGB, zeroRGB+RGB);
    this->intensityValueSpan.push_back(0.0);
    this->paletteIndexSpan.push_back(0);
  }

  for (int i = 0; i < this->getMaxFlames(); i++)
  {
    this->flames.push_back(NULL);
    this->flameOffsets.push_back(-1);
  }
}

void FirePit::resetIntensities()
{
  int zeroRGB[] = {0, 0, 0};
  // this->colorValueSpan.clear();
  // this->intensityValueSpan.clear();
  // this->paletteIndexSpan.clear();

  for (int i = 0; i < this->getSize(); i++)
  {
    //this->colorValueSpan.push_back( vector<int>() );
    this->colorValueSpan[i].assign(zeroRGB, zeroRGB+RGB);
    this->intensityValueSpan[i] = 0.0;
    this->paletteIndexSpan[i] = 0;
  }

}

void FirePit::pushFlame(Flame * flamePtr, int offset)
{
  int c = 0;
  while (this->flames[c] && c < (this->getMaxFlames()-1)) c++;
  this->flames[c] = flamePtr;
  //this->flames.push_back(flamePtr);
}

void setFlame(Flame * flamePtr, int offset)
{
  this->resetIntensities();
  vector<float> flameIntensities = flamePtr->getIntensities();
  for (int i = 0; i < flameIntensities.size(); i++)
  {
    if (offset+i) < this->intensityValueSpan.size()
    {
      this->intensityValueSpan[offset+i] = flameIntensities[i];
    }
  }
}

void FirePit::cleanFlames()
{
  for (int i = 0; i < this->getMaxFlames(); i++)
  {
    if (this->flames[i]->isDead())
    {
      delete this->flames[i];
      this->flames[i] = NULL;
      this->flameOffsets[i] = -1;
      this->activeFlames--;
    }
  }
}

void FirePit::stepFlames()
{
  for (int i = 0; i < this->getMaxFlames(); i++)
  {
    if (this->flames[i]) this->flames[i]->next();
  }
}

void FirePit::lightFlames()
{
//  if (this->)

}

void FirePit::fire()
{
  this->cleanFlames();
  this->stepFlames();
  this->lightFlames();
}

void FirePit::fireToLED(Adafruit_NeoPixel * neo_strip)
{
// // Fill the dots, a la "colorWipe" from strandtest
// void testColor(uint32_t c, uint8_t wait) {
//   for(uint16_t i=0; i<strip.numPixels(); i++) {
//       strip.setPixelColor(i, c);
//       strip.show();
//       delay(wait);
//   }
// }

}

int FirePit::getSize()
{
  return this->size;
}

int FirePit::getMaxFlames()
{
  return this->maxFlames;
}

int FirePit::getActiveFlames()
{
  return this->activeFlames;
}

FirePit::~FirePit()
{

}
