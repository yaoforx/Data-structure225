#include "Image.h"
#include "StickerSheet.h"

int main() {

  //
  // Reminder:
  //   Before exiting main, save your creation to disk as myImage.png
  //

  // Image alma; alma.readFromFile("tests/alma.png");
  // Image i;    i.readFromFile("tests/i.png");

  // StickerSheet sheet(alma, 5);
  // sheet.addSticker(i, 20, 200

	Image alma; alma.readFromFile("tests/alma.png");

	Image data; data.readFromFile("tests/data-structure.png");
	Image handshake; handshake.readFromFile("tests/handshake.png");
	Image wade; wade.readFromFile("tests/wade.png");
	wade.scale(0.5);
	//wade.writeToFile("myImage.png");
	handshake.scale(0.5);
    StickerSheet sheet(alma, 3);
	sheet.addSticker(data, 400,50);

	sheet.addSticker(handshake, 300, 100);
	sheet.addSticker(wade, 100, 100);
	(sheet.render()).writeToFile("myImage.png");


  return 0;
}
