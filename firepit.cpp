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

#include <Adafruit_NeoPixel.h>
#include "flame.h"
#include "firepit.h"
#include "palette.h"

using namespace std;

FirePit::FirePit(const int s, const int m, const int p[][RGB])
  : size(s), maxFlames(m)
{
  this->activeFlames = 0;

  // init our local palette vector from basic array arg
  for (int i = 0; i < PALETTE_ROWS; i++)
  {
    this->palette.push_back( vector<int>() );
    for (int j = 0; j < RGB; j++)
    {
      this->palette[i].push_back(p[i][j]);
    }
  }

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
  this->flameOffsets[c] = offset;
  this->activeFlames++;
}

void FirePit::setFlame(Flame * flamePtr, int offset)
{
  this->resetIntensities();
  vector<float> flameIntensities = flamePtr->getIntensities();
  for (int i = 0; i < flameIntensities.size(); i++)
  {
    if ((offset+i) < this->intensityValueSpan.size())
    {
      this->intensityValueSpan[offset+i] = flameIntensities[i];
    }
  }
}

void FirePit::mergeFlame(Flame * flamePtr, int offset)
{
  this->mergeIntensities(flamePtr->getIntensities(), offset);
  this->updateColors();
}

void FirePit::mergeIntensities(vector<float> intensities, int offset)
{
  for (int i = 0; i < intensities.size(); i++)
  {
    if ((offset+i) < this->intensityValueSpan.size())
    {
      float currentI = this->intensityValueSpan[offset+i];
      float newI = intensities[i];
      this->intensityValueSpan[offset+i] = (currentI+newI)/2;
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
  if (this->activeFlames > 0)
  {
    // find a non-null pointer in case the first one was dead and made NULL
    int c = 0;
    while (!this->flames[c]) c++;
    this->setFlame(this->flames[c], this->flameOffsets[c]);
    c++;
    for (int i = c; i < this->getMaxFlames(); i++)
    {
      if (this->flames[i])
      {
        this->mergeFlame(this->flames[i], this->flameOffsets[i]);
      }
    }
  }
}

void FirePit::fire()
{
  this->cleanFlames();
  this->stepFlames();
  this->lightFlames();
}

void FirePit::updateColors()
{
  int paletteIndex = 0;
  for (int i = 0; i < this->intensityValueSpan.size(); i++)
  {
    paletteIndex = floor(this->intensityValueSpan[i] * this->palette.size());
    if (paletteIndex >= this->palette.size()) paletteIndex = this->palette.size()-1;
    else if (paletteIndex < 0) paletteIndex = 0;
    for (int j = 0; j < RGB; j++)
    {
      this->colorValueSpan[i][j] = this->palette[paletteIndex][j];
    }
  }
}

void FirePit::printColors()
{
  printf("####---- LED COLORS ----####\n");
  for (int i = 0; i < this->getSize(); i++)
  {
    printf("LED %02d  -  ", i);
    for (int j = 0; j < RGB; j++)
    {
        printf("%03d ", this->colorValueSpan[i][j]);
    }
    printf("\n");
  }
  
  printf("\n");
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

void FirePit::fireToLED(Adafruit_NeoPixel * neo_strip)
{

}

vector< vector<int> > FirePit::getPalette()
{
  return this->palette;
}

FirePit::~FirePit()
{

}
