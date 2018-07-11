/**
 * @file StickerSheet.h
 * Contains your declaration of the interface for the StickerSheet class.
 */
#ifndef STICKERSHEET_H_
#define STICKERSHEET_H_

#include "Image.h"
using namespace cs225;

class StickerSheet{
public:
	StickerSheet(const Image & picture, unsigned max);
	~StickerSheet();
	StickerSheet(const StickerSheet &other);
	const StickerSheet & operator=(const StickerSheet &other);
	void changeMaxStickers(unsigned max);
	int addSticker(Image &sticker, unsigned x, unsigned y);
	bool translate(unsigned index, unsigned x, unsigned y);
	void removeSticker(unsigned index);
	Image render() const;
	Image * getSticker(unsigned index) const;
	

private:
	Image picture_;
	unsigned max_;
	
	Image * Sticker_;// User defined
	unsigned *x_cor;
	unsigned *y_cor;//document every coordinate of a sticker
	
	bool *HasSticker;//Indentify if this layer has a sticker already

	unsigned x_;

	
	//Image & sticker_;
	unsigned y_;
	unsigned index_;
	void _copy(const StickerSheet &other);
	void _destroy();
};


#endif
 