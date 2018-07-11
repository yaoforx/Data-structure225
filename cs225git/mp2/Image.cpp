#include "Image.h"
#include "cs225/HSLAPixel.h"
#include <string>
#include <cmath>

using namespace cs225;

void Image::lighten(){
    w_ = this->width();
	h_ = this->height();

	for (unsigned int x = 0; x < w_; x ++){
		for (unsigned int y = 0; y < h_; y++){
			HSLAPixel & p = this->getPixel(x,y);	
			p.l = p.l + 0.1;
			if(p.l<0.0 || p.l > 1.0)
			p.l = 1.0;
		}
	}
}

		
	


void Image::lighten(double amount){
	amount_ = amount;
	w_ = this->width();
	h_ = this->height();
	for (unsigned int x = 0; x < w_; x ++){
		for (unsigned int y = 0; y < h_; y++){
			HSLAPixel & p = this->getPixel(x,y);
			//while(p.l + amount_ <= 1.0 && p.l + amount_ >=0.0)
		
				p.l = p.l + amount_;
			if(p.l< 0.0 )
				p.l = 0.0;
			else if(p.l >1.0)
				p.l = 1.0;

		}
	}

}
void Image::darken(double amount){
	amount_ = amount;
	w_ = this->width();
	h_ = this->height();
	for (unsigned int x = 0; x < w_; x ++){
		for (unsigned int y = 0; y < h_; y++){
			
			HSLAPixel & p = this->getPixel(x,y);
			p.l = p.l - amount_;
			if(p.l<0.0 )
			p.l = 0.0;
		}
	}

}
void Image::saturate(){
	
	w_ = this->width();
	h_ = this->height();
	for (unsigned int x = 0; x < w_; x ++){
		for (unsigned int y = 0; y < h_; y++){
			HSLAPixel & p = this->getPixel(x,y);
			p.s = p.s + 0.1;
			if(p.s< 0.0 )
				p.s = 0.0;
			else if(p.s >1.0)
				p.s = 1.0;
		}
	}

}
void Image::saturate(double amount){
	amount_ = amount;
	w_ = this->width();
	h_ = this->height();
	for (unsigned int x = 0; x < w_; x ++){
		for (unsigned int y = 0; y < h_; y++){
			HSLAPixel & p = this->getPixel(x,y);
			p.s = p.s + amount_;
			if(p.s< 0.0 )
				p.s = 0.0;
			else if(p.s >1.0)
				p.s = 1.0;
		}
	}

}
void Image::desaturate(double amount){
	amount_ = amount;
	w_ = this->width();
	h_ = this->height();
	for (unsigned int x = 0; x < w_; x ++){
		for (unsigned int y = 0; y < h_; y++){
			HSLAPixel & p = this->getPixel(x,y);
			while(p.s - amount_ <= 1.0 &&p.s - amount_>=0.0)
			p.s = p.s - amount_;
		}
	}

}
void Image::rotateColor(double degrees){
	degrees_ = degrees;
	w_ = this->width();
	h_ = this->height();
	for (unsigned int x = 0; x < w_; x ++){
		for (unsigned int y = 0; y < h_; y++){
			HSLAPixel & p = this->getPixel(x,y);
			if((p.h+degrees_) >= 360)
			p.h = (p.h + degrees_) - 360;
			else if(p.h + degrees_ <= 0)
			p.h = (p.h + degrees_)+360;
			else
				p.h = p.h + degrees_;


			
		}
	}

}
void Image::scale(double factor){
	factor_ = factor;
	
	unsigned nw_ = this->width()*factor_;
	unsigned nh_ = this->height()*factor_;
	
	HSLAPixel * newImageData = new HSLAPixel[nw_*nh_];
	for (unsigned x = 0; x < nw_ ; x ++){
		for (unsigned y = 0; y < nh_ ; y++){
			if (x < nw_ -1&& y < nh_ -1) {
				
				HSLAPixel & oldPixel= this->getPixel(ceil(x*1.0/factor_),ceil(y*1.0/factor_));
				newImageData[ (x + (y * nw_)) ]= oldPixel;
				
				
			   
		    }
				
			}
		}
		this->resize(nw_,nh_);

for (unsigned x = 0; x < nw_ ; x ++){
		for (unsigned y = 0; y < nh_ ; y++){
			if (x < nw_ -1&& y < nh_ -1)
			this->getPixel(x,y) = newImageData[ (x + (y * nw_)) ];
		}
	}
	//delete this;

    // Update the image to reflect the new image size and data
    


		

}
