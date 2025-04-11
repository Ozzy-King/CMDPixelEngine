#include <iostream>
#include <Windows.h>
#include <string>
#include "GDIEngine.h"
#include "GDISprite.h"

COLORREF regColour = RGB(255,0,0);

//void scrolltext(std::string& str) {
//	std::string newStr = str;
//	for (int i = str.length()-1; i >= 0; i--) {
//		if (i == 0) {
//			newStr[i] = str[str.length() - 1];
//		}
//		else {
//			newStr[i] = str[i - 1];
//		}
//	}
//	str = newStr;
//}


int main() {

	char title[] = "NULL";
	if (GDinit(255, 255, 1, 1, title)) {
		return 0;
	}
	srand(time(NULL));
	std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n" << _GDpixelSetType;

	char fileName[] = "./Cards.jpg";
	struct GDSPsprite newSorite = GDSPcreateSprite(fileName, 1040, 1580, 104, 158, 0, RGB(0,0,0));

	int start = 1;
	int end = 2;

	while (1) { //not good practice
		GDsetTitle(std::to_string((double)1/ ((double)(end-start)/ CLOCKS_PER_SEC)).c_str());
		start = (int)clock();

		GDSPdrawSprite(0, 0, 104, 158, &newSorite, 3);

		GDdrawBackBuffer();


		end = (int)clock();
		//std::cin.ignore();
	}

	GDdeInit();

	//std::cin.ignore(); //testing get rid of
	
	std::cout << "hello World!\n";
	return 0;
}