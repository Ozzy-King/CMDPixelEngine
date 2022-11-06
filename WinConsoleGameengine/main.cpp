#include <iostream>
#include <Windows.h>


	#include "GDIEngine.h"


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
	if (GDinit(25, 25, 2, 2, title)) {
		return 0;
	}
	srand(time(NULL));
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << _GDpixelSetType;

	while (true) { //not good practice

		GDclear(RGB(255,255,255));
		for (int x = 0; x < _GDwidth - 5; x++) {
			for (int y = 0; y < _GDheight - 5; y++) {
				GDdrawPixel(x,y ,RGB(rand()%256, rand()%256, rand()%256));
			}
		}

		GDdrawBackBuffer();
	}

	GDdeInit();

	std::cin.ignore(); //testing get rid of
	
	std::cout << "hello World!\n";
	return 0;
}