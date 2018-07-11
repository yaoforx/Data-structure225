#include "../cs225/HSLAPixel.h"
#include "../Point.h"

#include "ColorPicker.h"
#include "MyColorPicker.h"
#include <cmath>
#define PI 3.14159
using namespace cs225;

/**
 * Picks the color for pixel (x, y).
 * Using your own algorithm
 */
MyColorPicker::MyColorPicker(double incr): hue(0), saturation(0),incre(incr) { };
HSLAPixel MyColorPicker::getColor(unsigned x, unsigned y) {
  /* @todo [Part 3] */
  HSLAPixel pixel(hue, saturation, 0.5);

  hue += incre;
  saturation = sin(PI*incre);
  if (hue >= 360) { hue -= 360; }
  return pixel;
  return HSLAPixel();
}
