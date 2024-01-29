#include <iostream>
#include <Windows.h>
#include <libloaderapi.h>
#include <string>
#include <thread>

#include "GDIEngine.h"
#include "GDISprite.h"
#include "world.h"

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
	if (GDinit(255, 255, 2, 2, title)) {
		return 0;
	}
	srand(time(NULL));
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << _GDpixelSetType;

	char fileName[] = "./textTest.bmp";
	struct GDSPsprite newSorite = GDSPcreateSprite(fileName, 20, 20, 10, 10, 1, RGB(0,0,0));

	int start = 1;
	int end = 2;

	//my game stuff
	world MyWorld;
	MyWorld.start();

	int tempX = 0; int tempY = 0;

	while (true) { //not good practice
		GDsetTitle(std::to_string((double)1/ ((double)(end-start)/ CLOCKS_PER_SEC)).c_str());
		start = (int)clock();


		MyWorld.update();

		GDdrawBackBuffer();


		end = (int)clock();
	}

	MyWorld.destory();
	GDdeInit();

	std::cin.ignore(); //testing get rid of
	
	std::cout << "hello World!\n";
	return 0;
}