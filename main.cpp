#include <iostream>

#include "Views.h"
#include "DateTime.h"
#include "MuonTra.h"
#include "DocGia.h"
#include "MenuMain.h"
#include "mylib.h"

#include "MaDocGia.cpp"
#include "Views.cpp"
#include "DateTime.cpp"
#include "MuonTra.cpp"
#include "DocGia.cpp"
#include "MenuMain.cpp"

using namespace std;					

int main (){
	system("color F1");
	setFullScreen();
	disableMinimizeButton();

   	ShowCur(false);
   	
	drawRectangle(25,1,120,80);
	drawLine(26,13,119);
	drawLine(26,27,119);
	drawLine(26,62,119);
	showTitle(43,6);
	showVersion(120,12,"1.1.0");
	
	initDocGiaTree(dsDocGia);
	LoadFileDocGia(dsDocGia,"DocGiaData.txt");
	showMenu1(-1);
    return 0;
}

