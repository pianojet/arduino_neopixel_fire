/*\
|*| Author:
|*|   Justin Taylor
|*|   pianojet@gmail.com
|*|   July 2015
|*|
|*| Some basic bits taken from
|*|   the Adafruit_NeoPixel code for "strandtest"
\*/

#include <stdlib.h>
#include <math.h>

#include "flame.h"


Flame::Flame(const uint8_t w, const uint8_t r, const uint8_t mI, const uint8_t s)
: size(w), strength(s)
{
    amplitudePercent = 0;
    grow = true;
    rage = round(15*(r/100.0));
    maxIntense = mI/100.0;
    this->flameIntensities = new uint8_t [size];
    for (uint8_t i = 0; i < size; i++)
    {
        this->flameIntensities[i] = 0;
    }
    cycles = 0;
    dead = false;
}

// processing for how to alter the flame.
// We need to choose whether to increase or decrease the
// intensity, whether to render the flame dead, and determine what
// relative amplitude the flame's gaussian distribution will be
// (which translates to the intensity later)
void Flame::step()
{
    if (this->grow) this->amplitudePercent += this->rage;
    else this->amplitudePercent -= this->rage;
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
    uint8_t percent;
    for (uint8_t i = 0; i < this->size; i++)
    {
        percent = round(this->gaussian(i) * this->amplitudePercent);
        this->flameIntensities[i] = percent;
    }
}

void Flame::next()
{
    this->step();
    this->newIntensities();
}

uint8_t Flame::getSize()
{
    return this->size;
}

// gaussian function using Flame's own parameters to smooth
// the flame intensities.
float Flame::gaussian(uint8_t w)
{
    float m = 6.0 - (5.0*this->maxIntense);// Math.sqrt(2 * Math.PI);
    float e = exp(-pow(w - (this->size/2.5), 2) / (2 * this->size));
    return e / m;
}

bool Flame::isDead()
{
    return this->dead;
}

Flame::~Flame()
{
    delete[] this->flameIntensities;
}

uint8_t& Flame::operator[](uint8_t i)
{
    return this->flameIntensities[i];
}
