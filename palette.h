/*\
 |*| Author:
 |*|   Justin Taylor
 |*|   pianojet@gmail.com
 |*|   July 2015
 |*|
 |*| Some basic bits taken from
 |*|   the Adafruit_NeoPixel code for "strandtest"
 \*/

#ifndef __PALETTE_H__
#define __PALETTE_H__

// Palettes shall define a fire gradient with 32 values of RGB color values
static const uint8_t PALETTE_ROWS = 32;
static const uint8_t RGB = 3;

// Global palettes can be defined here; each palette can define a color style for the fire,
// e.g. blue fire, green fire, etc.  Only red is defined below, currently.
//
// Palette arrays, index 0 to MAX, represent a scale of intensity from lowest to highest,
//   respectively.
//
// For now, if changing palette of different sizes is desired, code changes and recompiling is necessary.
static const uint8_t PALETTE_REG_FIRE[PALETTE_ROWS][RGB] =
{
    {0, 0, 0},
    {50, 0, 0},
    {100, 0, 0},
    {125, 0, 0},
    {150, 0, 0},
    
    {175, 0, 0},
    {200, 0, 0},
    {225, 0, 0},
    {250, 25, 0},
    {250, 50, 0},
    
    {250, 75, 0},
    {250, 100, 0},
    {250, 125, 0},
    {250, 150, 0},
    {250, 175, 0},
    
    {250, 200, 0},
    {250, 225, 0},
    {250, 250, 0},
    {250, 250, 25},
    {255, 255, 50},
    
    {255, 255, 75},
    {250, 250, 100},
    {250, 250, 125},
    {255, 255, 150},
    {255, 255, 150},
    
    {255, 255, 175},
    {255, 255, 175},
    {255, 255, 200},
    {255, 255, 200},
    {255, 255, 225},
    
    {255, 255, 255},
    {255, 255, 255}
};

#endif
