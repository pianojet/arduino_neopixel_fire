/*\
|*| Author:
|*|   Justin Taylor
|*|   pianojet@gmail.com
|*|   July 2015
|*|
|*| Some basic bits taken from
|*|   the Adafruit_NeoPixel code for "strandtest"
\*/

#include <math.h>

#include <Adafruit_NeoPixel.h>
#include "flame.h"
#include "firepit.h"
#include "palette.h"


FirePit::FirePit(const uint8_t s, const uint8_t m, const uint8_t p[][RGB])
: size(s), maxFlames(m)
{
    //this->palette = p;
    this->activeFlames = 0;
    
    // init our local palette vector from basic array arg
    for (uint8_t i = 0; i < PALETTE_ROWS; i++)
    {
        for (uint8_t j = 0; j < RGB; j++)
        {
            this->palette[i][j] = p[i][j];
        }
    }
    
    // init our containers that track parameters for each LED
    this->colorValueSpan = new uint8_t [size*RGB];
    this->intensityValueSpan = new uint8_t [size];
    this->resetIntensities();
    
    // init our flame containers
    this->flames = new Flame* [maxFlames];
    this->flameOffsets = new int8_t [maxFlames];
    for (uint8_t i = 0; i < this->getMaxFlames(); i++)
    {
        this->flames[i] = NULL;
        this->flameOffsets[i] = -1;
    }
}

// need to provide resetting to avoid value bloat
void FirePit::resetIntensities()
{
    for (uint8_t i = 0; i < this->getSize(); i++)
    {
        uint8_t rgbIndex = i*RGB;
        this->colorValueSpan[rgbIndex] = this->colorValueSpan[rgbIndex+1] = this->colorValueSpan[rgbIndex+2] = 0;
        this->intensityValueSpan[i] = 0;
    }
}

// add a flame to the pit where possible
void FirePit::pushFlame(Flame * flamePtr, int8_t offset)
{
    int c = 0;
    // seek valid location
    while (this->flames[c] && c < (this->getMaxFlames()-1))
    {
        c++;
    }

    // if we're forcing a push to the end where one already exists...
    if (this->flames[c])
    {
        delete this->flames[c];
    }
    else 
    {
        this->activeFlames++;
    }
    
    // assign the flame
    this->flames[c] = flamePtr;
    this->flameOffsets[c] = offset;
}

// resets pit intensities and adds a flame.
// designed to be followed by merges in order to
// fully account for all flames correctly
void FirePit::setFlame(Flame * flamePtr, uint8_t offset)
{
    this->resetIntensities();
    for (uint8_t i = 0; i < flamePtr->getSize(); i++)
    {
        uint8_t thisIndex = offset+i;
        if (thisIndex < this->getSize())
        {
            this->intensityValueSpan[thisIndex] = (*flamePtr)[i];
        }
    }
}

// merge given flame into the existing span of intensities
void FirePit::mergeFlame(Flame * flamePtr, uint8_t offset)
{
    for (uint8_t i = 0; i < flamePtr->getSize(); i++)
    {
        uint8_t thisIndex = offset+i;
        if (thisIndex < this->getSize())
        {
            uint8_t currentI = this->intensityValueSpan[thisIndex];
            uint8_t newI = (*flamePtr)[i];
            uint8_t newValue = round((currentI+newI)/2);
            this->intensityValueSpan[thisIndex] = newValue;
        }
    }

}

// remove all dead flames
void FirePit::cleanFlames()
{
    for (uint8_t i = 0; i < this->getMaxFlames(); i++)
    {
        if (this->flames[i] && this->flames[i]->isDead())
        {
            delete this->flames[i];
            this->flames[i] = NULL;
            this->flameOffsets[i] = -1;
            this->activeFlames--;
        }
    }
}

// increment flame intensities
void FirePit::stepFlames()
{
    for (uint8_t i = 0; i < this->getMaxFlames(); i++)
    {
        if (this->flames[i])
        {
            this->flames[i]->next();
        }
    }
}

// accounts for setting the entire span of intensities using
// flames in container
void FirePit::lightFlames()
{
    if (this->activeFlames > 0)
    {
        uint8_t c = 0;
        // seek for a non-null pointer in case the first one was dead and made NULL
        while (!this->flames[c]) c++;
        this->setFlame(this->flames[c], this->flameOffsets[c]);
        c++;
        for (uint8_t i = c; i < this->getMaxFlames(); i++)
        {
            if (this->flames[i]) // test again, multiple flames may have 'burned out' after the c index
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
    this->updateColors();
}

// translate intensities into specific colors from given palette
void FirePit::updateColors()
{
    uint8_t paletteIndex = 0;
    for (uint8_t i = 0; i < this->getSize(); i++)
    {
        uint8_t rgbIndex = i*RGB;
        // the lowest row in palette matches 0% intensity, and highest row matches 100% intensity
        paletteIndex = floor((this->intensityValueSpan[i]/100.0) * PALETTE_ROWS);

        // ensure valid bounds
        if (paletteIndex >= PALETTE_ROWS) paletteIndex = PALETTE_ROWS-1;
        else if (paletteIndex < 0) paletteIndex = 0;
        for (uint8_t j = 0; j < RGB; j++)
        {
            this->colorValueSpan[rgbIndex+j] = this->palette[paletteIndex][j];
        }
    }
}

uint8_t FirePit::getSize()
{
    return this->size;
}

uint8_t FirePit::getMaxFlames()
{
    return this->maxFlames;
}

uint8_t FirePit::getActiveFlames()
{
    return this->activeFlames;
}

// transfer colorValues from pit to strip
void FirePit::fireToLED(Adafruit_NeoPixel * neo_strip)
{
    for (uint8_t i = 0; i < this->getSize(); i++)
    {
        uint8_t rgbIndex = i*RGB;
        neo_strip->setPixelColor(i, neo_strip->Color(this->colorValueSpan[rgbIndex], this->colorValueSpan[rgbIndex+1], this->colorValueSpan[rgbIndex+2]));
    }
}

FirePit::~FirePit()
{
    delete[] this->colorValueSpan;    
    delete[] this->flames;
    delete[] this->flameOffsets;
    delete[] this->intensityValueSpan;
}
