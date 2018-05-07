#include <cassert>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <dos.h>
#include <iostream>
#include <time.h>
#include <string.h>
#include <windows.h>
#include <cctype>

using namespace std;

#define WHITE 15

const int ESC =27;
const int UP = 72;
const int DOWN = 80;
const int ENTER = 13;
const int LEFT_ARROW_INPUT = 124;// my define. this is used for nhapChu
const int RIGHT_ARROW_INPUT = 125;// my define. this is used for nhapChu

const int LEFT_ARROW = 75;// real value
const int RIGHT_ARROW = 77;// real value

const int BACKSPACE = 8;
const int DELETE_INPUT = 126 ;// my define

const int CONFIRM = 1;
const int EXIT = 0;

void ShowCur(bool CursorVisibility)
{
    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursor = {1, CursorVisibility};
    SetConsoleCursorInfo(handle, &cursor);
}

void gotoxy(int x , int y)
{
     COORD coord;
     coord.X = x;
     coord.Y = y;
     SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int wherex( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.X;
}

int wherey( void )
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);
    return screen_buffer_info.dwCursorPosition.Y;
}
void clreol( ) {
COORD coord;
DWORD written;
CONSOLE_SCREEN_BUFFER_INFO info;
GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
coord.X = info.dwCursorPosition.X;
coord.Y = info.dwCursorPosition.Y;
FillConsoleOutputCharacter (GetStdHandle(STD_OUTPUT_HANDLE), ' ',
  info.dwSize.X - info.dwCursorPosition.X * info.dwCursorPosition.Y, coord, &written);
gotoxy (info.dwCursorPosition.X + 1, info.dwCursorPosition.Y + 1);
}

void SetColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    wAttributes &= 0xfff0;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void SetBGColor(WORD color)
{
    HANDLE hConsoleOutput;
    hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

    CONSOLE_SCREEN_BUFFER_INFO screen_buffer_info;
    GetConsoleScreenBufferInfo(hConsoleOutput, &screen_buffer_info);

    WORD wAttributes = screen_buffer_info.wAttributes;
    color &= 0x000f;
    color <<= 4;
    wAttributes &= 0xff0f;
    wAttributes |= color;

    SetConsoleTextAttribute(hConsoleOutput, wAttributes);
}
void Normal () {
	SetColor(0);
	SetBGColor(255);
}
void HighLight () {
	SetColor(15);
	SetBGColor(66);
}
void drawLine(int x,int y,int w, int charInt=220){
	gotoxy(x,y);
	Normal();
	SetColor(0);
	for (int i=0;i<w/2;i++){
		cout<<char(charInt)<<char(charInt);
	}
	cout<<char(charInt);
	Normal();
}
void drawVertical(int x,int y, int height, int charInt=220){
	
	for (int i=1;i<height;i++){
		gotoxy(x,y+i);
		if (i!=1){
			SetBGColor(0);
		}
		cout<<char(charInt)<<"";
	}
}
void disableMinimizeButton(){
	 HWND hwnd  = GetConsoleWindow();
		SetWindowLong(hwnd, GWL_STYLE,
               GetWindowLong(hwnd, GWL_STYLE) & ~WS_MAXIMIZEBOX);
}

void setFullScreen(){
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	
	SMALL_RECT rect;
    COORD coord;
    coord.X = 168; // Defining our X and
    coord.Y = 44;  // Y size for buffer.

    rect.Top = 0;
    rect.Left = 0;
    rect.Bottom = coord.Y-1; // height for window
    rect.Right = coord.X-1;  // width for window

    HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE); // get handle
    SetConsoleWindowInfo(hwnd, TRUE, &rect);    
}

void drawRectangle(int x,int y, int width,int height){
	
	int charHeight=254;
	
	drawLine(x,y+2,width);
	
	drawVertical(x,y+1,height);
	
	drawVertical(x+width,y+2,height-1);
	
	drawLine(x+1,y+height,width-2);
}

void drawRectangleInput(int x, int y, int width, int height){
	int color=1;
	for (int i=1;i<=width;i++){
		gotoxy(x+i,y);
		SetColor(color);
		if (i==1){
			cout<<char(201);
		} else {
			if (i==width){
				cout<<char(187);
			} else 
			cout<<char(205);
  		}
	}
	for (int i=1;i<=height;i++){
		
		for (int j= 1 ;j<=width;j++){
			gotoxy(x+j,y+i);
			SetColor(color);
			if (j==1|| j ==width){
				cout<<char(186);
			}else {
				cout<<" ";
			}
		}
	}
	for (int i=1;i<=width;i++){
		gotoxy(x+i,y+height);
		SetColor(color);
		if (i==1){
			cout<<char(200);
		} else {
			if (i==width){
				cout<<char(188);
			} else 
			cout<<char(205);
  		}
	}
}
bool isAlphabet(char c){
	if ((c >= 65 && c<=90) || (c>=97 && c<=122)){
		return true;
	}
	return false;
}
bool isUpperCase(char c){
	if (c>=65&&c<=90){
		return true;
	}
	return false;
}
bool isLowerCase(char c){
	if (c>=97&&c<=122){
		return true;
	}
	return false;
}
bool isNumber(char c){
	if (c>=48&&c<=57){
		return true;
	}
	return false;
}
string upperFirstLetter(string str){
	str[0] = toupper(str[0]);
	return str;
}
void deleteInput(int x, int y, int length){
	for (int i=0;i<length;i++){
		gotoxy(x+i,y);
		cout<<" ";
	}
}
void showInput(int x, int y, string value,int curson){
	gotoxy(x,y);
	cout<<value;
	gotoxy(x+curson,y);
}

int nhapChu(EditText edt){
	int x=edt.x;
	int y=edt.y;
	int lenght = edt.length;
	string value = *edt.value;
	ShowCur(true);
	gotoxy(x,y);
	cout<<value;
	int curson = value.size();
	
	gotoxy(x+curson,y);
	bool isSHIFT=false;
	char eventKeyboard;
	
	while(1){
		if (kbhit()){
		eventKeyboard = getch();
		if (eventKeyboard==0) eventKeyboard = getch();
			//detect up and down
		if (GetAsyncKeyState(VK_SHIFT)){
			isSHIFT = true;
		}else {
			isSHIFT = false;
		}
	
		if (!isSHIFT){
			switch(eventKeyboard){
				case 'K':
					eventKeyboard = char(LEFT_ARROW_INPUT);
					break;
				case 'M':
					eventKeyboard = char(RIGHT_ARROW_INPUT);
					break;
				case 'S':
					eventKeyboard = char(DELETE_INPUT);
					break;
				case UP :
					if (value.size()>0){
						if (!isUpperCase(value[0])){
							*edt.value = upperFirstLetter(value);
						} else {
							*edt.value = value;
						}
					}else {
					*edt.value = "";
				}
					return UP;
				case DOWN: 
					if (value.size()>0){
						if (!isUpperCase(value[0])){
							*edt.value = upperFirstLetter(value);
						} else {
							*edt.value = value;
						}
					}else {
					*edt.value = "";
				}
					return DOWN;
					
			}
		}
		switch(eventKeyboard){
			case ESC:
				return ESC;
			case ENTER:
				if (value.size()>0){
						if (!isUpperCase(value[0])){
							*edt.value = upperFirstLetter(value);
						} else {
							*edt.value = value;
						}
				} else {
					*edt.value = "";
				}
				return ENTER;
				break;
			case BACKSPACE:
					if (curson>0){
							if(curson == value.size()){
								curson--;
								gotoxy(x+curson,y);
								cout<<" ";
								value.erase(curson);
								gotoxy(x+curson,y);
							} else {
								curson--;
								value.erase(curson,1);						
								deleteInput(x,y,lenght);
								showInput(x,y,value,curson);
							}
							
						}
						
				break;
			case LEFT_ARROW_INPUT:
				if (curson > 0){
					curson--;
					gotoxy(x+curson,y);
				}
				break;
			case RIGHT_ARROW_INPUT:
				if (curson<lenght && curson<value.size()){
					curson++;
					gotoxy(x+curson,y);	
				} else {
					if (value.size()>0){
						if (!isUpperCase(value[0])){
							*edt.value = upperFirstLetter(value);
						} else {
							*edt.value = value;
						}
					}
					return RIGHT_ARROW;
				}
				break;
			case DELETE_INPUT:
				if (curson<lenght-1){
					value.erase(curson,1);
					deleteInput(x,y,lenght);
					showInput(x,y,value,curson);
				} else {
					if(curson==lenght-1){
						value.erase(curson,1);
						gotoxy(x+curson,y);
						cout<<" ";
						gotoxy(x+curson,y);
					} 
				}
				break;
	
			default:
				if (isAlphabet(eventKeyboard)&&value.size()<lenght){
					if (curson==0){
						
						if (value.size()==0){
							value.insert(0,1,eventKeyboard);
							gotoxy(x,y);
							cout<<eventKeyboard;
							curson++;
							gotoxy(x+curson,y);
						} else {
							value.insert(0,1,eventKeyboard);
							deleteInput(x,y,lenght);
							showInput(x,y,value,1);
							curson = 1;
						}		
					} else {
							if(curson==value.size()){
								value.insert(curson,1,eventKeyboard);
								gotoxy(x+curson,y);
								cout<<eventKeyboard;
								curson++;
								gotoxy(x+curson,y);
							} else {
								value.insert(curson,1,eventKeyboard);
								deleteInput(x,y,lenght);
								curson++;
								showInput(x,y,value,curson);		
							} 
							
					}		
				}
				break;		
		}
		
		}// end if kbhit 
	}
}
int nhapSo(EditText edt){
	int x=edt.x;
	int y=edt.y;
	int lenght = edt.length;
	string value = *edt.value;
	ShowCur(true);
	gotoxy(x,y);
	cout<<value;
	int curson = value.size();
	gotoxy(x+curson,y);
	char eventKeyboard;
	
	while(1){
		if (kbhit()){
		eventKeyboard = getch();
		if (eventKeyboard==0) eventKeyboard = getch();
				
		switch(eventKeyboard){
			case ESC:
				return ESC;
			case ENTER:
				*edt.value = value;
				return eventKeyboard;
				break;
			case UP :
				*edt.value = value;
				return UP;
			case DOWN: 
				*edt.value = value;
				return DOWN;
			case BACKSPACE:
					if (curson>0){
							if(curson == value.size()){
								curson--;
								gotoxy(x+curson,y);
								cout<<" ";
								value.erase(curson);
								gotoxy(x+curson,y);
							} else {
								curson--;
								value.erase(curson,1);
						
								deleteInput(x,y,lenght);
								showInput(x,y,value,curson);
							}
							
						}
						
				break;
			case LEFT_ARROW:
				if (curson > 0){
					curson--;
					gotoxy(x+curson,y);
				}
				break;
			case RIGHT_ARROW:
				if (curson<lenght && curson<value.size()){
					curson++;
					gotoxy(x+curson,y);	
				} else {
					if (value.size()>0){
						if (!isUpperCase(value[0])){
							*edt.value = upperFirstLetter(value);
						} else {
							*edt.value = value;
						}
					}
					return RIGHT_ARROW;
				}
				break;
			case DELETE_INPUT:
				if (curson<lenght-1){
					value.erase(curson,1);
					deleteInput(x,y,lenght);
					showInput(x,y,value,curson);
				} else {
					if(curson==lenght-1){
						value.erase(curson,1);
						gotoxy(x+curson,y);
						cout<<" ";
						gotoxy(x+curson,y);
					} 
				}
				break;
	
			default:
				if (isNumber(eventKeyboard)&&value.size()<lenght){
					if (curson==0){
						if (value.size()==0){
							value.insert(0,1,eventKeyboard);
							gotoxy(x,y);
							cout<<eventKeyboard;
							curson++;
							gotoxy(x+curson,y);
						} else {
							value.insert(0,1,eventKeyboard);
							deleteInput(x,y,lenght);
							showInput(x,y,value,1);
							curson = 1;
						}		
					} else {
							if(curson==value.size()){
								value.insert(curson,1,eventKeyboard);
								gotoxy(x+curson,y);
								cout<<eventKeyboard;
								curson++;
								gotoxy(x+curson,y);
							} else {
								value.insert(curson,1,eventKeyboard);
								deleteInput(x,y,lenght);
								curson++;
								showInput(x,y,value,curson);		
							} 
							
					}		
				}
				break;		
		}
		
		}// end if kbhit 
	}
}

void deleteEditTexts(EditText editArr[], int length){
	for (int i = 0 ;i<length;i++){
		delete editArr[i].value;
		delete editArr[i].isError;
	}
}

void resetAllEditTexts(EditText editArr[], int length){
	for (int i = 0 ;i<length;i++){
		*editArr[i].value = "";
		*editArr[i].isError = true;
	}
}


int onConfirm(int x,int y,string confirmName){
	ShowCur(false);
	string arr[2]={confirmName,"Thoat                       <-"};
	
	HighLight();
	gotoxy(x,y);
	cout<<arr[0];
	
	char eventKeyboard;
	int currentChoose=0;
	while(1){
		if (kbhit()){
			eventKeyboard = getch();
			if (eventKeyboard == 0) eventKeyboard = getch();
			switch(eventKeyboard){
				case RIGHT_ARROW:
					Normal();
					if(currentChoose>0){
						gotoxy(x,y+currentChoose+1);
					} else {
						gotoxy(x,y+currentChoose);
					}
					cout<<arr[currentChoose];
					return RIGHT_ARROW;
					break;
				case LEFT_ARROW:
					Normal();
					if(currentChoose>0){
						gotoxy(x,y+currentChoose+1);
					} else {
						gotoxy(x,y+currentChoose);
					}
					cout<<arr[currentChoose];
						
					return LEFT_ARROW;
					break;
				case UP:
					if (currentChoose>0){
						Normal();
						gotoxy(x,y+currentChoose+1);
						cout<<arr[currentChoose];
							
						currentChoose--;
							
						HighLight();
						gotoxy(x,y+currentChoose);
						cout<<arr[currentChoose];
					} else {
						Normal();
						gotoxy(x,y+currentChoose);
						cout<<arr[currentChoose];
						return UP;
					}
					break;
				case DOWN:
						if (currentChoose<1){
							
							Normal();
							gotoxy(x,y+currentChoose);
							cout<<arr[currentChoose];
							
							currentChoose++;
							
							HighLight();
							gotoxy(x,y+currentChoose+1);
							cout<<arr[currentChoose];
							
						} else {
							Normal();
							gotoxy(x,y+currentChoose+1);
							cout<<arr[currentChoose];
							return DOWN;
						}
					break;
				case ENTER:
					Normal();
					gotoxy(x,y+currentChoose);
					cout<<arr[currentChoose];	
					if (currentChoose==0){
						//xac nhan confirm
						return CONFIRM;
					} else {
						//thoat hoan toan nhap lieu ra menu chinh
				
						return EXIT;
						
					}
					break;
				case ESC:
					Normal();
					
					if (currentChoose==0){
						gotoxy(x,y+currentChoose);
					} else {
						gotoxy(x,y+currentChoose+1);	
					}
					cout<<arr[currentChoose];
					return ESC;
			}
		}
	}
}
	
void clearScreen(int x, int y, int width, int height){
	Normal();
	string w="";
	for (int i = 0 ;i<width;i++){
		w +=" ";
	}
		for (int i=0;i<height;i++){
			gotoxy(x,y+i);
			cout<<w;
		}
}

void showError(int x,int y, string error){
	ShowCur(false);
	SetColor(12);
	SetBGColor(255);
	gotoxy(x,y);
	cout<<error;
	SetColor(0);
}
void dimissErrorInput(int x, int y, int width){
	ShowCur(false);
	for(int i=0;i<width;i++){
		gotoxy(x+i,y);
		cout<<" ";
	}
}
void showCorrect(int x, int y, string content){
	ShowCur(false);
	SetColor(49);
	SetBGColor(255);
	gotoxy(x,y);
	cout<<content;
	SetColor(0);
	ShowCur(true);
}
void clearState(){
	Normal();
	gotoxy(115,58);
	cout<<"                              ";
}
void showState(string result){
	SetColor(49);
	gotoxy(115,58);
	cout<<result;
	SetColor(0);
}
void showVersion(int x, int y, string version){
	gotoxy(x,y);
	cout<<"[version: "<<version<<"]";	
}

