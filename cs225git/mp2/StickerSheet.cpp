#include "StickerSheet.h"

using namespace cs225;

StickerSheet::StickerSheet(const Image & picture, unsigned max){

	max_ = max;
	picture_ = picture;
	Sticker_ = new Image[max_];
	x_cor = new unsigned[max_];
	y_cor = new unsigned[max_];
	HasSticker = new bool[max_];
	index_ = 0;
	for (unsigned i = 0; i < max_;i++){
		HasSticker[i] = false;
		y_cor[i] = 0;
		x_cor[i] = 0;
	}

	
}
StickerSheet::~StickerSheet(){
	
	delete[] Sticker_;
	delete[] x_cor;
	delete[] y_cor;
	delete[] HasSticker;

	
}
StickerSheet::StickerSheet(const StickerSheet &other){
		 Sticker_ = NULL;
		 x_cor = NULL;
		 y_cor = NULL;
		 HasSticker = NULL;

		_copy(other);
	

}
void StickerSheet::_copy(const StickerSheet &other){
	delete[] Sticker_;
	delete[] x_cor;
	delete[] y_cor;
	delete[] HasSticker;
	x_ = other.x_;
	y_ = other.y_;
	max_ = other.max_;
	index_ = other.index_;
	picture_ = other.picture_;
	Sticker_ = new Image[max_];
	x_cor = new unsigned[max_];
	y_cor = new unsigned[max_];
	HasSticker = new bool[max_];
	for (unsigned i = 0; i < max_; i++) {
		x_cor[i] = other.x_cor[i];
		y_cor[i] =other.y_cor[i];
		HasSticker[i] = other.HasSticker[i];
		Sticker_[i] = other.Sticker_[i];
	}
	

}
void StickerSheet::_destroy(){
	delete[] Sticker_;
	

}
const StickerSheet & StickerSheet::operator=(const StickerSheet &other){
	if(this != &other){
		delete[] Sticker_;
		delete[] x_cor;
		delete[] y_cor;
		delete[] HasSticker;
		Sticker_ = NULL;
		 x_cor = NULL;
		 y_cor = NULL;
		 HasSticker = NULL;
		_copy(other);
	}
return *this;
}
void StickerSheet::changeMaxStickers(unsigned max){

    Image *temp = new Image[max];
    bool * tempHas = new bool[max];
	if(max_< max){
		for(unsigned i = 0; i < max_ ; i++){
			temp[i] = Sticker_[i];
		}
	delete[] Sticker_;
	Sticker_ = temp;
		for(unsigned i = 0; i < max_; i++){
		tempHas[i] = HasSticker[i];
		}
		for(unsigned i = max_; i< max; i++){
		tempHas[i] = false;
		}
    delete[] HasSticker;
	HasSticker = tempHas;
	}
   else  {
   		for(unsigned i = 0; i < max ; i++){
   		temp[i] = Sticker_[i];
		}
	delete[] Sticker_;
	Sticker_ = temp;
		for(unsigned i = 0; i< max;i++){
		tempHas[i] = HasSticker[i];
		}
	delete[] HasSticker;
	HasSticker = tempHas;
    }
 max_ = max;
 

}
int StickerSheet::addSticker(Image &sticker, unsigned x, unsigned y){
	
		for(unsigned i = 0; i < max_;i++){
		   if(HasSticker[i]==false){	
				Sticker_[i] = sticker;
				HasSticker[i] = true;
				x_cor[i] = x;
				y_cor[i] = y;
				if(index_<=i){
				index_ = i;
				}
				return i;
			}
		}

	
		return -1;

}

bool StickerSheet::translate(unsigned index, unsigned x, unsigned y){
	if(HasSticker[index]){
		x_cor[index] = x;
		y_cor[index] = y;
		return true;
	}
	else
		return false;
}
void StickerSheet::removeSticker(unsigned index){
	if(index < max_)
	HasSticker[index] = false;
	
	
}
Image * StickerSheet::getSticker(unsigned index) const{
	
	if(HasSticker[index]){
		return Sticker_;
	}
	else{
		return NULL;
	}
}
Image StickerSheet::render() const{


for(unsigned i = 0; i <= index_; i++){
	if(HasSticker[i]){
		for(unsigned w = x_cor[i]; w < (Sticker_[i].width()+x_cor[i]); w++){
			for(unsigned h = y_cor[i]; h < (Sticker_[i].height()+y_cor[i]); h++){
				
				if(Sticker_[i].getPixel(w - x_cor[i],h - y_cor[i]).a != 0 && w < picture_.width() && h < picture_.height())
					if((w-x_cor[i]) < Sticker_[i].width() && (h-y_cor[i]) < Sticker_[i].height() ){

				HSLAPixel & p = picture_.getPixel(w,h);
				HSLAPixel & s = Sticker_[i].getPixel(w-x_cor[i],h-y_cor[i]);
				p = s;
			}	

			}
		}
		
	}
}

	
	

	return picture_;
}






