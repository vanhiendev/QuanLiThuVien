
#include<iostream>

using namespace std;

#define MENU_ITEM 11
#define DOC_GIA_ITEM  4

#define Y_MENU_1 15
#define X_MENU_1 30 

#define Y_MENU_2  15
#define X_MENU_2  90

#define WELCOME_HEIGHT 15
#define WELCOME_WITDH 80


int MenuChoose (char td [MENU_ITEM][50], int chon);
int DocGiaChoose (char td [DOC_GIA_ITEM][50], int chon);
void xoaMenu2(char td [DOC_GIA_ITEM][50]);
void menuDocGia(int chooseFromMenu1,int chooseFromMenu2);
void showMenu1(int chon);
void backMenu1(int chooseOld);
void showTitle(int x,int y);



