#include "cs225/PNG.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <cmath>

using namespace cs225;


void rotate(std::string inputFile, std::string outputFile) {
  // Part 2
	PNG image;
	image.readFromFile(inputFile);
	PNG output;
	output.readFromFile(inputFile);
	unsigned int width = image.width();
	unsigned int height = image.height();

	for (unsigned int x = 0; x < width; x ++){
		for (unsigned int y = 0; y < height; y++){
			HSLAPixel * p = image.getPixel(x,y);
            HSLAPixel * o = output.getPixel(width - 1 - x, height - 1 -  y);
            *o = *p;
           


		} 
	}
	output.writeToFile(outputFile);

}

PNG myArt(unsigned int width, unsigned int height) {
  PNG png(width, height);
  //png.resize(800,800);
  for(unsigned int x = 0; x < width; x++){
  	for(unsigned int y = 10; y < height; y ++){
  		
  		HSLAPixel * pixel = png.getPixel(x,y);
  		HSLAPixel * prev = png.getPixel(x,y - 10);
      pixel->a = 1.0;
      pixel->l = prev->l *(double) sin(3.1415*x/800);
      pixel->s = 1.0;
  		pixel->h = prev->h + 10*(double) sin(3.1415*y/800);
  		//pixel->h = (double)x / (double)width * 360;

  		
  		
  		}
  	}
  


  return png;
}
