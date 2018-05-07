#include <iostream>


using namespace std;


DocGiaTree dsDocGia;


char WELCOME [6][80] ={

	" 000000   00       00000000 00     0 00     0   0000   000 00 0000000 000    00",
	"00     0  00          00    00     0 00     0    00     0  00 00      00 0   00",
	"00     0  00          00    00000000 00     0     00   0   00 000000  00  0  00",
	"00  00 0  00          00    00     0 00     0      00 0    00 00      00   0 00",
	" 000000   000000      00    00     0 00000000       00     00 0000000 00    000",
	"       00                                                                      "
};

char MENU_TABLE [MENU_ITEM][50] = {
							"1. Doc gia                               ",
			                "2. In danh sach doc gia                  ",
			                "3. Nhap dau sach va danh ma sach tu dong ",
			                "4. In danh sach dau sach                 ",
			                "5. Tim sach                              ",
			                "6. Muon sach                             ",
			                "7. Tra sach                              ",
							"8. Liet ke sach cua mot doc gia muon     ", 
							"9. In danh sach doc gia muon qua han     ",
							"10.In 10 sach co so luong muon cao nhat  ",
							"11.Thoat                                 " };
	
char DOC_GIA_CHOOSE [DOC_GIA_ITEM][50] = {
	"1. Them doc gia         +                ",
	"2. Xoa doc gia          -                ",
	"3. Sua doc gia          #                ",
	"4. Quay lai             <-               "};		
											  
char XOA_MENU_2 [DOC_GIA_ITEM][50] = {
							"                                         ",
			                "                                         ",
			                "                                         ",
							"                                         "};
							
int MenuChoose (char td [MENU_ITEM][50], int chon){
  	Normal();
  	int i; 
  	for ( i=0; i< MENU_ITEM ; i++)
  	{ 
  		gotoxy(X_MENU_1, Y_MENU_1 +i);
    	cout << td[i];
  	}
  	HighLight();
  	gotoxy(X_MENU_1,Y_MENU_1+chon);
  	cout << td[chon];
  	char kytu;
	do {
		if (kbhit()){
  		kytu = getch();
  		if (kytu==0) kytu = getch();
  		switch (kytu) {
    		case UP :
				if (chon+1 >1){
  		        	Normal();
              		gotoxy(X_MENU_1,Y_MENU_1+chon);
              		cout << td[chon];
              		chon --;
              		HighLight();
              		gotoxy(X_MENU_1,Y_MENU_1+chon);
              		cout << td[chon];	
  			  	} else {
  			  		Normal();
              		gotoxy(X_MENU_1,Y_MENU_1+chon);
              		cout << td[chon];
  			  		chon = MENU_ITEM-2;
  			  		
              		gotoxy(X_MENU_1,Y_MENU_1+chon);
              		cout << td[chon];
              		chon ++;
              		HighLight();
              		gotoxy(X_MENU_1,Y_MENU_1+chon);
              		cout << td[chon];
				}
  			  	break;
  		case DOWN :
	  			if (chon+1 <MENU_ITEM){
  		        	Normal();
              		gotoxy(X_MENU_1,Y_MENU_1+chon);
              		cout << td[chon];
              		chon ++;
              		HighLight();
              		gotoxy(X_MENU_1,Y_MENU_1+chon);
              		cout << td[chon];	
  			  	} else {
  			  		Normal();
              		gotoxy(X_MENU_1,Y_MENU_1+chon);
              		cout << td[chon];
  			  		chon = 1;
              		gotoxy(X_MENU_1,Y_MENU_1+chon);
              		cout << td[chon];
              		chon --;
              		HighLight();
              		gotoxy(X_MENU_1,Y_MENU_1+chon);
              		cout << td[chon];	
				}
  			  	break;
  	case ESC: 
  		exit(1);
	  	break;
  	case ENTER : 
	  return chon+1;
	case RIGHT_ARROW:
		return chon+1;
  }  // end switch
  }
  } while (1);
}

int DocGiaChoose (char td [DOC_GIA_ITEM][50], int chon){
  	Normal();
  	int i; 
  	for ( i=0; i< DOC_GIA_ITEM ; i++)
  	{ 
  		gotoxy(X_MENU_2, Y_MENU_2 +i);
    	cout << td[i];
  	}
  	HighLight();
  	gotoxy(X_MENU_2,Y_MENU_2+chon);
  	cout << td[chon];
  	char kytu;
	do {
		if (kbhit()){
  		kytu = getch();
  		if (kytu==0) kytu = getch();
  		switch (kytu) {
    		case UP :
				if (chon+1 >1){
  		        	Normal();
              		gotoxy(X_MENU_2,Y_MENU_2+chon);
              		cout << td[chon];
              		chon --;
              		HighLight();
              		gotoxy(X_MENU_2,Y_MENU_2+chon);
              		cout << td[chon];	
  				}else {
  			  		Normal();
              		gotoxy(X_MENU_2,Y_MENU_2+chon);
              		cout << td[chon];
  			  		chon = DOC_GIA_ITEM-2;
  			  	
              		gotoxy(X_MENU_2,Y_MENU_2+chon);
              		cout << td[chon];
              		chon ++;
              		HighLight();
              		gotoxy(X_MENU_2,Y_MENU_2+chon);
              		cout << td[chon];
				}
  				break;
  			case DOWN :
	  			if (chon+1 <DOC_GIA_ITEM){
  		        	Normal();
              		gotoxy(X_MENU_2,Y_MENU_2+chon);
              		cout << td[chon];
              		chon ++;
              		HighLight();
              		gotoxy(X_MENU_2,Y_MENU_2+chon);
              		cout << td[chon];	
  			  	} else {
  			  		
  			  		Normal();
              		gotoxy(X_MENU_2,Y_MENU_2+chon);
              		cout << td[chon];
              		
  			  		chon = 1;
  			  		
              		gotoxy(X_MENU_2,Y_MENU_2+chon);
              		cout << td[chon];
              		chon --;
              		HighLight();
              		gotoxy(X_MENU_2,Y_MENU_2+chon);
              		cout << td[chon];	
				}
  			 	break;
  			case LEFT_ARROW:
  				return LEFT_ARROW;
  				break;
  			case ESC:
  				return ESC;
  				break;
  	case ENTER : 
	  return chon+1;
  }  // end switch
  } 
  }while (1);
}

void xoaMenu2(char td [DOC_GIA_ITEM][50]){
	for ( int i=0; i< DOC_GIA_ITEM ; i++)
  	{ 
  		Normal();
  		gotoxy(X_MENU_2, Y_MENU_2 +i);
    	cout << td[i];
  	}
}

void menuDocGia(int chooseFromMenu1,int chooseFromMenu2){
	int c = DocGiaChoose(DOC_GIA_CHOOSE,chooseFromMenu2);
	switch (c){
		case 1: 
      		insertDocGiaUI(dsDocGia,chooseFromMenu1, c-1);
			break;
        case 2:
			deleteDocGiaUI(dsDocGia,chooseFromMenu1, c-1);
			break;
		case 3: 
			editDocGiaUI(dsDocGia,chooseFromMenu1, c-1);
			break;
		case 4: 
			backMenu1(chooseFromMenu1);
			break;
		case ESC:
			backMenu1(chooseFromMenu1);
			break;
		case LEFT_ARROW:
			backMenu1(chooseFromMenu1);
			break;
	}
}		

void showMenu1(int chon){
	if (chon==-1){
		chon = MenuChoose (MENU_TABLE,0);
	} else {
		chon = MenuChoose(MENU_TABLE,chon);
	}
        	switch (chon) {
        		case 1:
      				menuDocGia(chon,0);
					break;
        		case 2:
					gotoxy(5,20); 
					cout<<"\nchon "<<chon;
					break;
				case 3: 
					gotoxy(5,20);	cout<<"\nchon "<<chon;
					break;
      			case 4:gotoxy(5,20); 	cout<<"\nchon "<<chon;
					break;
        		case 5:gotoxy(5,20);	cout<<"\nchon "<<chon;
					break;
				case 6: gotoxy(5,20);	cout<<"\nchon "<<chon;
					break;
				case 7:	gotoxy(5,20); cout<<"\nchon "<<chon;
					break;
        		case 8: gotoxy(5,20);	cout<<"\nchon "<<chon;
					break;
				case 9:	gotoxy(5,20);cout<<"\nchon "<<chon;
					break;
				case 10: gotoxy(5,20);	cout<<"\nchon "<<chon;
					break;
				case 11: 
					SaveFileDocGia(dsDocGia,"DocGiaData.txt");
					exit(1);	
					break;
		}	
	}

void backMenu1(int chooseOld){
	xoaMenu2(XOA_MENU_2);
	showMenu1(chooseOld-1);
}


void showTitle(int x,int y){
	
	for (int i=0;i<8;i++){
		gotoxy(x,y);
		SetColor(0);	
	
		for (int j=0;j<80;j++){
			if (WELCOME[i][j] == 48){
				WELCOME[i][j] = char(178);
			}
		}		
		cout<<WELCOME[i]<<"\n";	
		y++;	
	}
}



