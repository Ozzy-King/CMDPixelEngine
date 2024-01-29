#include <iostream>
#include <Windows.h>
#include <libloaderapi.h>
#include <string>

#include "GDIEngine.h"
#include "GDISprite.h"

COLORREF regColour = RGB(255,0,0);

void scrolltext(std::string& str) {
	std::string newStr = str;
	for (int i = str.length()-1; i >= 0; i--) {
		if (i == 0) {
			newStr[i] = str[str.length() - 1];
		}
		else {
			newStr[i] = str[i - 1];
		}
	}
	str = newStr;
}

int main() {

	char title[] = "NULL";
	if (GDinit(80, 80, 4, 4, title)) {
		return 0;
	}
	srand(time(NULL));
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << _GDpixelSetType;

	char fileName[] = "./textTest.bmp";
	struct GDSPsprite newSorite = GDSPcreateSprite(fileName, 20, 20, 10, 10, 1, RGB(0,0,0));

	int start = 1;
	int end = 2;

	while (true) { //not good practice
		GDsetTitle(std::to_string((double)1/ ((double)(end-start)/ CLOCKS_PER_SEC)).c_str());
		start = (int)clock();

		GDclear(RGB(255,255,255));
		for (int x = 0; x < _GDwidth; x++) {
			for (int y = 0; y < _GDheight; y++) {
				GDdrawPixel(x,y ,RGB(rand()%256, rand()%256, rand()%256));
			}
		}

		GDSPdrawSprite(0, 0, 40, 40, &newSorite, 3);
		GDSPdrawSprite(40, 40, 40,40, &newSorite, 0);

		GDdrawBackBuffer();


		end = (int)clock();
	}

	GDdeInit();

	std::cin.ignore(); //testing get rid of
	
	std::cout << "hello World!\n";
	return 0;
}