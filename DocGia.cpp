#include<iostream>

using namespace std;

void initDocGiaTree(DocGiaTree &tree){
	 tree= NULL;
}

DocGiaTree createDocGiaNode(DocGia dg){
	DocGiaTree node = new DOCGIATREE;
	if (node !=NULL){
		node -> pleft = NULL;
		node -> pright = NULL;
		node -> docGia = dg;
		return node;
	}
	//het bo nho
	return NULL;
}

int insertDocGia(DocGiaTree &tree, DocGia dg){
	if (tree == NULL){
		//cay rong
		DocGiaTree node = createDocGiaNode(dg);
		if (node != NULL){
			tree = node;
			return 1;
		}
		//het bo nho
		return 0;
	} else {
		if (dg.maDocGia < tree->docGia.maDocGia){
			return insertDocGia(tree->pleft, dg);
		}  else
		if (dg.maDocGia > tree->docGia.maDocGia){
			return insertDocGia(tree->pright, dg);
		}
	}
}

DocGiaNode* searchDocGia(DocGiaTree tree, int maDocGia){
	if (tree == NULL){
		return NULL;
	} else {
		if (tree->docGia.maDocGia > maDocGia){
			searchDocGia(tree->pleft,maDocGia );
		} else {
			if (tree->docGia.maDocGia < maDocGia){
				searchDocGia(tree->pright,maDocGia );
			} else {
				return tree;
			}
		}
	}
}

int editDocGia(DocGiaTree &tree,DocGia dg){
	if (tree == NULL)  return 0;
	
	dg.firstMuonTra = tree->docGia.firstMuonTra;
	tree->docGia= dg;
	
	return 1;
}

//swap tree a va b voi b la "node trai nhat ben phai"
// b la cay ben phai
void swapDocGiaNode(DocGiaTree &a, DocGiaTree &b){
	if (b->pleft!=NULL){
		swapDocGiaNode(a,b->pleft);
	} else {
		//xoa con tro trong a
		deleteAllNodeMuonTra(a->docGia.firstMuonTra);
		a->docGia = b->docGia;
		a = b;
		b = b->pright;
	}
}
int deleteDocGia(DocGiaTree &tree, int maDocGia){
	if (tree == NULL){
		// khong tim thay doc gia
		return 0;
	}
	if (maDocGia < tree->docGia.maDocGia){
		deleteDocGia(tree->pleft , maDocGia);
	}  else {
		if (maDocGia > tree->docGia.maDocGia){
			deleteDocGia(tree->pright , maDocGia);
		} else {
			//tim thay doc gia
			DocGiaNode * node = tree;
			// xoa node co 1 con va 0 con
			if (tree->pleft == NULL){
				tree = tree->pright;
			} else {
				if (tree->pright == NULL){
					tree = tree->pleft;
				} else {
					swapDocGiaNode(node, tree->pright);
				}
			}
			
			//----------------------------
			delete node;
			return 1;
		}
	}
	
}
int slDocGia(DocGiaTree t){
	if (t == NULL) return 0;
	else return slDocGia(t->pright)+slDocGia(t->pleft)+1;
}

void SaveFileDocGia (DocGiaTree dsDocGia,char *tenfile){
  	ofstream f(tenfile); 
	int sl;
	if (f.fail()) {
  		return ; // null
  	}
	// save So Luong doc gia
  	sl = slDocGia(dsDocGia);
  	f<<sl<<endl;
  	if (dsDocGia!=NULL){
				DocGia arrDocGia[sl];
				DocGia dg;
				NodeMuonTra np;
				MuonTra muonTra;
				DateTime dateTimeMuon,dateTimeTra;
				int x=0;
				getDocGiaArr(dsDocGia,arrDocGia,x);
				for (int i=0;i<sl;i++){
						
					//----------------------------------------------------------------------------------
					dg = arrDocGia[i];
					// save Data Doc Gia(maDocGia; ho[11];ten[11]; phai;trangThaiThe;)
  					f<<dg.maDocGia<<" "<<dg.ho<<" "<<dg.ten<<" "<<dg.phai<<" "<<dg.trangThaiThe<<endl;
  					// save data Muon tra nam trong Doc Gia
					int luongMuonTra = soLuongNodeMuonTra(dg.firstMuonTra);
  		
  					//save so luong muon tra
					f<<luongMuonTra<<endl;
  						for (np=dg.firstMuonTra; np!=NULL; np=np->nextNode){
  							muonTra = np->muonTra;
  							dateTimeMuon = muonTra.dateMuon;
  							dateTimeTra = muonTra.dateTra;
  							
  							//save so Data muon tra (maSach, trang thai)
							f<<muonTra.maSach<<" "<<muonTra.trangThai<<" ";
		
							//save ngay muon - ngay tra
  							f<<dateTimeMuon.Day<<" "<<dateTimeMuon.Month<<" "<<dateTimeMuon.Year<<" ";
							f<<dateTimeTra.Day<<" "<<dateTimeTra.Month<<" "<<dateTimeTra.Year<<endl;
						}
					
					//----------------------------------------------------------------------------------
		}
	}
	f.close();
}
void LoadFileDocGia (DocGiaTree &dsDocGia,char *tenfile){
  	ifstream f(tenfile); 
	if (f.fail()) {
  		return ; // null
  	}
  	int slDG=0,i, j ; 
  //get so luong Doc gia
  	f>>slDG;
  	
  	if (slDG>0){

  		DocGia L;
  		MuonTra muonTra;
	   	DateTime ngayMuon; 
		DateTime ngayTra;
		int soLuongMuonTra = 0;
  //lay data cua tung Doc Gia
	  	for (i=0 ; i < slDG ;i++) {
	  		  
	    	f>>L.maDocGia;
	    	f>>L.ho;
	    	f>>L.ten;
	    	f>>L.phai;
	    	f>>L.trangThaiThe;
	    	
			L.firstMuonTra=NULL;
	    
	    	f>>soLuongMuonTra;
	   		if (soLuongMuonTra>0){
		  		for ( j=0; j <soLuongMuonTra; j++)
		  		{
			  		f>>muonTra.maSach;
			  		f>>muonTra.trangThai;
			  		
			  		f>>ngayMuon.Day;
			  		f>>ngayMuon.Month;
			  		f>>ngayMuon.Year;
			  		
			  		f>>ngayTra.Day;
			  		f>>ngayTra.Month;
			  		f>>ngayTra.Year;
			  		
			  		muonTra.dateMuon = ngayMuon;
			  		muonTra.dateTra = ngayTra;
			  		
			  		NodeMuonTra nodeMuonTra = createNodeMuonTra(muonTra);
			  		
			  		insertNodeMuonTra(L.firstMuonTra,nodeMuonTra);
		  		}
	  		}
	  		insertDocGia(dsDocGia,L);
	  }
	}
  f.close();
}


void deleteAllDocGia(DocGiaTree &dsDocGia){
	if (dsDocGia!=NULL){
		deleteAllDocGia(dsDocGia->pleft);
		deleteAllDocGia(dsDocGia->pright);
		
		deleteAllNodeMuonTra(dsDocGia->docGia.firstMuonTra);
		delete dsDocGia;
	}
}

void handelOutOfDocGia(int maDocGia){
	if (maDocGia==-1){	
		showError(60,35,"***********< So luong Doc Gia da day! >***********");
	} 
	if (maDocGia == -2){
		showError(54,35,"***********< Duong dan toi file du lieu bi loi! >***********");
	}
	showCorrect(73,37,"Nhan ENTER de quay lai!");
		char c;
		while(1){
			if (kbhit()){
				c= getch();
				if (c == ENTER){
					clearScreen(54,35,60,3);
					ShowCur(false);
					break;
				}
			}
		}
}

int onHanldeConfirmThemDocGiaUI(int &inputCurrent,int inputItem, int xConfirm, int yConfirm, string confirmName){
		int chooseFromConfirm;
		chooseFromConfirm = onConfirm(xConfirm,yConfirm,confirmName);
		switch(chooseFromConfirm){
			case UP:
				inputCurrent = inputItem-1;
				ShowCur(true);
				break;
			case DOWN:
				inputCurrent = 0;
				ShowCur(true);
				break;	
			case LEFT_ARROW:
				inputCurrent = 0;
				ShowCur(true);
				break;	
			case RIGHT_ARROW:
				inputCurrent = 0;
				ShowCur(true);	
				break;
			// other event: ESC, ENTER( CONFRIM || EXIT) is nothing to hanlde here
		}			
		return chooseFromConfirm;
						
}

void drawInsertDocGiaUI(){
	Normal();
	gotoxy(65,30);
	cout<<"*********** THEM DOC GIA ***********";
	SetColor(1);	
	gotoxy(30,35);
	cout<<"Ma doc gia: ";
	gotoxy(30,38);
	cout<<"Ho: ";
	drawRectangleInput(45,37,15,2);
	gotoxy(30,41);
	cout<<"Ten: ";
	drawRectangleInput(45,40,15,2);
	gotoxy(30,44);
	cout<<"Phai: ";
	drawRectangleInput(45,43,7,2);
	gotoxy(30,47);
	cout<<"Trang thai the: ";
	drawRectangleInput(45,46,5,2);
	
	gotoxy(30,50);SetColor(8);
	cout<<"(Ghi chu:";
	gotoxy(32,51);
	cout<<"Phai: Nam hoac Nu";
	gotoxy(32,52);
	cout<<"Trang thai the:";
	gotoxy(50,52);
	cout<<"0:Bi khoa";
	gotoxy(50,53);
	cout<<"1:Dang hoat dong)";
	SetColor(0);
	
	gotoxy(101,40);cout<<"Them Doc Gia                 +";
	gotoxy(101,42);cout<<"Thoat                       <-";
	
}
DocGia createDocGia(EditText arr[], int maDocGia){
	DocGia rs;
	rs.maDocGia = maDocGia;
	rs.firstMuonTra = NULL;
	string ho = *arr[0].value;
	string ten = *arr[1].value;
	string phai = *arr[2].value;
	string the = *arr[3].value;
	rs.ho = ho;
	rs.ten = ten;
	rs.phai = phai;
	rs.trangThaiThe = atoi(the.c_str());
	return rs;
}

void insertDocGiaUI(DocGiaTree &dsDocGia, int chooseFromMenu1,int chooseFromMenu2){
	int maDocGia = getIdRandomDocGia();
	
	if (maDocGia==-1||maDocGia==-2){
		handelOutOfDocGia(maDocGia);
		menuDocGia(chooseFromMenu1,chooseFromMenu2);
		return;
	}
	
	drawInsertDocGiaUI();
	
	// set value Ma doc fia random	
	gotoxy(48,35);
	cout<<maDocGia;
	Normal();
	int xConfirm = 101,yConfirm = 40;
	string confirmName="Them Doc Gia                 +";
	EditText edtHo;
	edtHo.x = 48;
	edtHo.y = 38;
	edtHo.length = 6;
	edtHo.value = new string("");
	edtHo.isError = new bool (true);
	edtHo.type = ALPHABET_TYPE;
	
	EditText edtTen;
	edtTen.x = 48;
	edtTen.y = 41;
	edtTen.length = 6;
	edtTen.value = new string("");
	edtTen.isError = new bool (true);
	edtTen.type = ALPHABET_TYPE;

	
	EditText edtPhai;
	edtPhai.x = 48;
	edtPhai.y = 44;
	edtPhai.length = 3;
	edtPhai.value = new string("");
	edtPhai.isError = new bool (true);
	edtPhai.type = ALPHABET_TYPE;
	
	
	EditText edtThe;
	edtThe.x = 48;
	edtThe.y = 47;
	edtThe.length = 1;
	edtThe.value = new string("");
	edtThe.isError = new bool (true);
	edtThe.type = NUMBER_TYPE;
	
	int inputItem = 4;
	EditText edtArr[inputItem];
	edtArr[0]= edtHo;
	edtArr[1]= edtTen;
	edtArr[2]= edtPhai;
	edtArr[3]= edtThe;
	
	int inputCurrent = 0;
	int chooseFromConfirm;
	EditText edtCurrent;
	char eventKeyboard;
	ShowCur(true);	
	bool isExit= false;
	bool isInsert;
	do{
			edtCurrent = edtArr[inputCurrent];
			//choose type input for edittext
			switch(edtCurrent.type){
				case NUMBER_TYPE:
					eventKeyboard = nhapSo(edtCurrent);
					break;
				case ALPHABET_TYPE:
					eventKeyboard = nhapChu(edtCurrent);
					break;
			}
			//handle error/complete with each edittext
			if (edtCurrent.value->size()==0){
				//error with input
				*edtCurrent.isError = true;
				showError(65,edtCurrent.y,"Khong de trong!");
			} else {
				if (edtCurrent.isError){
					*edtCurrent.isError = false;
					dimissErrorInput(65,edtCurrent.y,15);
				}
				//cac truong hop dac biet
				string v = *edtCurrent.value;
				switch(inputCurrent){
					case 2:
						if (!v.compare("Nam") || !v.compare("Nu") ){
							showCorrect(65,edtCurrent.y,"Hoan thanh     ");
						}else {	
							*edtCurrent.isError = true;
							showError(65,edtCurrent.y,"Nhap sai!       ");
						}
						break;
					case 3:
						if (!v.compare("0")||!v.compare("1")){
							showCorrect(65,edtCurrent.y,"Hoan thanh     ");
						} else {
							*edtCurrent.isError = true;
							showError(65,edtCurrent.y,"Nhap sai!         ");
						}
						break;
					default:
						showCorrect(65,edtCurrent.y,"Hoan thanh        ");
						break;
				}
				
			}
			//hanlde event down |up |right |esc key
	  		switch (eventKeyboard) {
	  			case DOWN :
	  				if  (inputCurrent<inputItem-1){
						inputCurrent++;
					} else {
						inputCurrent = 0 ;
					}
	  			  	break;
	  			case RIGHT_ARROW:
	  					//move to confirm menu on right
						chooseFromConfirm = onHanldeConfirmThemDocGiaUI(inputCurrent,inputItem,xConfirm,yConfirm,confirmName);
						if (chooseFromConfirm == CONFIRM){
							isInsert=true;
								for (int i=0;i<inputItem; i++){
									if (*edtArr[i].isError == true){
										inputCurrent = i;
										isInsert = false;
										break;
									}
								}
								if (isInsert){
									// all are fine to insert to Doc Gia Tree
									int r = insertDocGia(dsDocGia,createDocGia(edtArr,maDocGia));
									SaveFileDocGia(dsDocGia,"DocGiaData.txt");
									if(r==1){			
										deleteFirstIdRandomDocGia();
										clearState();
										showState("Da them Doc gia: "+*edtArr[0].value+" "+*edtArr[1].value);
									} else {
										showState("Co loi xay ra. Vui long thu lai sau!");
										inputCurrent = 0;
										break;
									}
									
									maDocGia = getIdRandomDocGia();	
									clearScreen(30,30,101,20);
									if (maDocGia==-1||maDocGia==-2){
										handelOutOfDocGia(maDocGia);
										isExit= true;
										break;
									}
								
									gotoxy(48,35);
									cout<<maDocGia;
									
									drawInsertDocGiaUI();
									resetAllEditTexts(edtArr,inputItem);
									
									inputCurrent = 0;
								}
						} else {
							if (chooseFromConfirm == ESC || chooseFromConfirm == EXIT){
								isExit = true;
							}
						}

	  				break;
				case UP :
					if  (inputCurrent>0){
						inputCurrent--;
					} else {
						inputCurrent = inputItem-1;
					}
	  			  	break;
	  			  	
	  			case ESC:
	  				isExit = true;
	  				break;
	  			case ENTER :
					if (inputCurrent<inputItem-1){
		  				inputCurrent++;
					}
	  				break;
	  		}  // end switch
	  	} while (!isExit);
	  	
	  	deleteEditTexts(edtArr,inputItem);
	  	clearState();
		clearScreen(30,30,101,24);
		ShowCur(false);
	  	menuDocGia(chooseFromMenu1,chooseFromMenu2);
}

void drawDeleteDocGiaUI(){
	Normal();
	gotoxy(65,30);
	cout<<"*********** XOA DOC GIA ***********";
	gotoxy(65,33);
	cout<<"      NHAP MA DOC GIA CAN XOA     ";
	drawRectangleInput(75,35,10,2);
	
	SetColor(0);
	drawVertical(81,38,12);
	Normal();
	gotoxy(40,39);
	cout<<"Thong Tin Doc Gia";
	
	SetColor(1);
	gotoxy(30,41);
	cout<<"Ho:"; 
	gotoxy(30,44);
	cout<<"Ten:"; 
	gotoxy(30,47);
	cout<<"Phai:"; 
	gotoxy(30,50);
	cout<<"Trang thai the:"; 
	
	SetColor(8);
	
	gotoxy(30,53);
	cout<<"(Ghi chu:";
	gotoxy(33,55);
	cout<<"Phai: Nam hoac Nu";
	gotoxy(33,56);
	cout<<"Trang thai the:";
	gotoxy(53,56);
	cout<<"0:Bi khoa";
	gotoxy(53,57);
	cout<<"1:Dang hoat dong";
	gotoxy(33,58);
	cout<<"Trang thai sach: ";
	gotoxy(53,58);
	cout<<"0:Sach dang muon ";
	gotoxy(53,59);
	cout<<"1:Da tra";
	gotoxy(53,60);
	cout<<"2:Lam mat sach)";
	
	SetColor(0);
	gotoxy(110,39);
	cout<<"Danh Sach Muon/Mat: ";
	gotoxy(95,41);
	cout<<"Ma Sach ";
	gotoxy(110,41);
	cout<<"Ngay Muon ";
	gotoxy(125,41);
	cout<<"Trang Thai ";
	
	gotoxy(103,53);cout<<"Xoa Doc Gia                  -";
	gotoxy(103,55);cout<<"Thoat                       <-";
	
	
}
int soLuongMuonTraDetail(int trangThai, NodeMuonTra node){
	int sl=0;
	for (NodeMuonTra p= node; p!=NULL; p = p->nextNode){
		if (p->muonTra.trangThai == trangThai){
			sl++;
		}
	}
	return sl;
}
void showDocGiaUI(int x, int y, DocGia dg){
	gotoxy(x,y)   ;cout<<dg.maDocGia;
	gotoxy(x+10,y);cout<<dg.ho;
	gotoxy(x+20,y);cout<<dg.ten;
	gotoxy(x+30,y);cout<<dg.phai;
	gotoxy(x+40,y);cout<<dg.trangThaiThe;
	
	gotoxy(x+60,y);cout<<soLuongMuonTraDetail(DANG_MUON,dg.firstMuonTra);
	gotoxy(x+80,y);cout<<soLuongMuonTraDetail(DA_TRA,dg.firstMuonTra);
	gotoxy(x+100,y);cout<<soLuongMuonTraDetail(MAT_SACH,dg.firstMuonTra);
}

void getDocGiaArr(DocGiaTree ds,DocGia arrDocGia[], int &couter){
	if (ds!=NULL){
		getDocGiaArr(ds->pleft,arrDocGia,couter);
		arrDocGia[couter] = ds->docGia;
		couter++;
		getDocGiaArr(ds->pright,arrDocGia,couter);
	}
}
void showNDocGiaDau(int n, DocGiaTree dsDocGia){
	gotoxy(60,64);
	cout<<"*********** DANH SACH DOC GIA ***********";
	gotoxy(30,66);cout<<"Ma";
	gotoxy(40,66);cout<<"Ho";
	gotoxy(50,66);cout<<"Ten";
	gotoxy(60,66);cout<<"Phai";
	gotoxy(70,66);cout<<"Trang thai the";
	gotoxy(90,66);cout<<"So luong muon";
	gotoxy(110,66);cout<<"So luong tra";
	gotoxy(130,66);cout<<"So luong mat";
	
	int sl = slDocGia(dsDocGia);
	ShowCur(false);
	if (sl==0) {
		gotoxy(72,68);
		SetColor(8);
		cout<<"Danh sach rong!!!";
		return;	
	}			
	
	DocGia arrDocGia[sl];
	int c=0;
	getDocGiaArr(dsDocGia,arrDocGia,c);
	
	clearScreen(30,68,101,n);
	
	int couter = 68;
	for(int i = 0;i<c;i++){
		if (i<n){
			showDocGiaUI(30,couter++,arrDocGia[i]);
		} else {
			break;
		}
	}
}
//page start from 1 to N*
int showDanhSachDocGiaUI(DocGiaTree dsDocGia,int slGet=5){

	int sl = slDocGia(dsDocGia);
	ShowCur(false);
	if (sl==0) {
		gotoxy(72,68);
		SetColor(8);
		cout<<"Danh sach rong!!!";
		return -1;	
	}			
	
	DocGia arrDocGia[sl];
	
	int x=0;
	getDocGiaArr(dsDocGia,arrDocGia,x);

	int psStart;
	int page=1;
	int maxPage= sl/slGet;
	if (sl % slGet!=0 ){
		maxPage += 1;
	}
	int couter=68;
	
	
	char event;
	while(1){
		if (kbhit()){
			event = getch();
			if (event==0) event = getch();
			switch(event){
				case LEFT_ARROW:
					if (page>1){
						page -- ;
						psStart = (page-1) * slGet;
						ShowCur(false);
						clearScreen(30,68,101,slGet);
			
						for(int i = psStart;i<sl;i++){
							if (i<slGet+psStart){
								showDocGiaUI(30,couter++,arrDocGia[i]);
							} else {
								break;
							}
						}
						ShowCur(true);
						couter = 68;					
					}
					break;
				case RIGHT_ARROW:
					if (page < maxPage){
						page++;
						
						psStart = (page-1) * slGet;
						ShowCur(false);
						clearScreen(30,68,101,slGet);
			
						for(int i = psStart;i<sl;i++){
							if (i<slGet+psStart){
								showDocGiaUI(30,couter++,arrDocGia[i]);
							} else {
								break;
							}
						}
						ShowCur(true);
						couter = 68;
						
					}
					break;
				case ESC:
					return ESC;
				case DOWN:
					return DOWN;
				case UP:
					return UP;
			}
			
		}
	}
}
void showInforInDeleteDocGia(DocGia docGia){
	gotoxy(50,41);cout<<docGia.ho;
	gotoxy(50,44);cout<<docGia.ten;
	gotoxy(50,47);cout<<docGia.phai;
	gotoxy(50,50);cout<<docGia.trangThaiThe;
	
	NodeMuonTra firstNode = docGia.firstMuonTra;
	
	int sl = soLuongNodeMuonTra(firstNode);
	if (sl==0) return;				
	MuonTra arrMuonTra[sl];
	int i=0;
						
	for (NodeMuonTra p= firstNode ;p!=NULL; p = p->nextNode){
		arrMuonTra[i] = p->muonTra;
		i++;
	}
	//handle sort later
	int y =44;
	MuonTra mt;
	for (int j=0;j<i;j++){
		mt = arrMuonTra[j];
		if (mt.trangThai==DANG_MUON ||mt.trangThai==MAT_SACH){
			gotoxy(97,y); cout<<mt.maSach;
			gotoxy(112,y); cout<<mt.dateMuon.Day<<"/"<<mt.dateMuon.Month<<"/"<<mt.dateMuon.Year;
			gotoxy(127,y); cout<<mt.trangThai;
			y++;
		}
	}
	
}
void deleteDocGiaUI(DocGiaTree &dsDocGia,int chooseFromMenu1, int chooseFromMenu2){
	drawDeleteDocGiaUI();

	EditText edtMa;
	edtMa.x = 80;
	edtMa.y = 36;
	edtMa.length = 3;
	edtMa.value = new string("");
	edtMa.isError= new bool(true);
	edtMa.type = NUMBER_TYPE;
	
	ShowCur(true);
	
	DocGiaTree dgTree;
	int id;
	string idString;
	
	char event;
	bool isExit= false;
	
	int slShowDocGia = SO_LUONG_DOC_GIA_UI;
	showNDocGiaDau(slShowDocGia,dsDocGia);
	
	while (!isExit){
			event = nhapSo(edtMa);
			switch(event){
				case DOWN:
					if (*edtMa.isError == false){
						event = onConfirm(103,53,"Xoa Doc Gia                  -") ;
							if (event == CONFIRM){
								
								clearScreen(97,44,40,3);
								clearScreen(50,41,7,10);
								
								drawDeleteDocGiaUI();
								*edtMa.value = "";
								
								string ho=dgTree->docGia.ho;
								string ten = dgTree->docGia.ten;
								
								clearState();
								showState("Da xoa Doc Gia: "+ho+" "+ten);
								deleteDocGia(dsDocGia,id);
								SaveFileDocGia(dsDocGia,"DocGiaData.txt");
								recreateIdRandomDocGia(id);
								showNDocGiaDau(slShowDocGia,dsDocGia);
								break;
							}
							
							if (event == EXIT){
								isExit = true;
								break;
							}
							break;
					}
					event = showDanhSachDocGiaUI(dsDocGia,slShowDocGia);
					if (event == ESC ){
						isExit = true;
						break;
					}
					
					break;
				case ESC:
					isExit = true;
					break;
				case ENTER:
					//handle error/complete with each edittext
					clearScreen(97,44,40,3);
					clearScreen(50,41,7,10);
					drawDeleteDocGiaUI();
					
					if (edtMa.value->size()==0){
						//error with input
						*edtMa.isError = true;
						showError(90,edtMa.y,"Vui long nhap ma Doc Gia!");
					} else {	
						idString = *edtMa.value;
						id = atoi(idString.c_str());
						dgTree = searchDocGia(dsDocGia,id);
						
						if (dgTree == NULL){	
							showError(90,edtMa.y,"Doc gia khong ton tai!   ");
							*edtMa.isError = true;
						} else {
							*edtMa.isError = false;
							showCorrect(90,edtMa.y,"                         ");	
							showInforInDeleteDocGia(dgTree->docGia);
						}
		
					}		
					break;
				}
			}

	delete edtMa.value;
	delete edtMa.isError;
	clearState();
	clearScreen(30,30,105,31);
	clearScreen(30,64,112,slShowDocGia+4);
	ShowCur(false);
	menuDocGia(chooseFromMenu1,chooseFromMenu2);
}

void drawEditDocGiaUI(){
	Normal();
	gotoxy(65,30);
	cout<<"*********** CHINH SUA DOC GIA ***********";	
	gotoxy(65,33);
	cout<<"      NHAP MA DOC GIA CAN CHINH SUA     ";
	drawRectangleInput(75,35,10,2);
	
	SetColor(0);
	drawVertical(81,38,12);
	
	Normal();
	gotoxy(40,39);
	cout<<"Thong Tin Doc Gia";
	
	SetColor(1);
	gotoxy(30,41);
	cout<<"Ho:"; drawRectangleInput(47,40,15,2);
	gotoxy(30,44);
	cout<<"Ten:"; drawRectangleInput(47,43,15,2);
	gotoxy(30,47);
	cout<<"Phai:"; drawRectangleInput(47,46,7,2);
	gotoxy(30,50);
	cout<<"Trang thai the:"; drawRectangleInput(47,49,5,2);
	
	SetColor(8);
	
	gotoxy(30,53);
	cout<<"(Ghi chu:";
	gotoxy(33,55);
	cout<<"Phai: Nam hoac Nu";
	gotoxy(33,56);
	cout<<"Trang thai the:";
	gotoxy(53,56);
	cout<<"0:Bi khoa";
	gotoxy(53,57);
	cout<<"1:Dang hoat dong";
	gotoxy(33,58);
	cout<<"Trang thai sach: ";
	gotoxy(53,58);
	cout<<"0:Sach dang muon ";
	gotoxy(53,59);
	cout<<"1:Da tra";
	gotoxy(53,60);
	cout<<"2:Lam mat sach)";
	
	SetColor(0);
	gotoxy(110,39);
	cout<<"Danh Sach Muon/Mat: ";
	gotoxy(95,41);
	cout<<"Ma Sach ";
	gotoxy(110,41);
	cout<<"Ngay Muon ";
	gotoxy(125,41);
	cout<<"Trang Thai ";
	
	gotoxy(95,53);cout<<"Chinh sua Doc Gia            #";
	gotoxy(95,55);cout<<"Thoat                       <-";
}
void insertDataToEdittext(EditText edtArr[],DocGia dg){
	*edtArr[0].value = dg.ho;
	*edtArr[1].value = dg.ten;
	*edtArr[2].value = dg.phai;
	if (dg.trangThaiThe==THE_BI_KHOA){
		*edtArr[3].value = "0";
		return;
	}
	//THE_HOAT_DONG
	*edtArr[3].value = "1";
}
void editDocGiaUI(DocGiaTree &dsDocGia,int chooseFromMenu1, int chooseFromMenu2){
	drawEditDocGiaUI();
	
	EditText edtMa;
	edtMa.x = 80;
	edtMa.y = 36;
	edtMa.length = 3;
	edtMa.value = new string("");
	edtMa.isError = new bool (true);
	edtMa.type = ALPHABET_TYPE;
	
	EditText edtHo;
	edtHo.x = 50;
	edtHo.y = 41;
	edtHo.length = 6;
	edtHo.value = new string("");
	edtHo.isError = new bool (true);
	edtHo.type = ALPHABET_TYPE;
	
	EditText edtTen;
	edtTen.x = 50;
	edtTen.y = 44;
	edtTen.length = 6;
	edtTen.value = new string("");
	edtTen.isError = new bool (true);
	edtTen.type = ALPHABET_TYPE;

	
	EditText edtPhai;
	edtPhai.x = 50;
	edtPhai.y = 47;
	edtPhai.length = 3;
	edtPhai.value = new string("");
	edtPhai.isError = new bool (true);
	edtPhai.type = ALPHABET_TYPE;
	
	
	EditText edtThe;
	edtThe.x = 50;
	edtThe.y = 50;
	edtThe.length = 1;
	edtThe.value = new string("");
	edtThe.isError = new bool (true);
	edtThe.type = NUMBER_TYPE;
	
	int inputItem = 4;
	EditText edtArr[inputItem];
	edtArr[0]= edtHo;
	edtArr[1]= edtTen;
	edtArr[2]= edtPhai;
	edtArr[3]= edtThe;
	
	int slShowDocGia = SO_LUONG_DOC_GIA_UI;
	showNDocGiaDau(slShowDocGia,dsDocGia);
	
	DocGiaTree dgTree;
	int id;
	string idString;
	
	int xConfirm = 95,yConfirm= 53;
	string confirmName="Chinh sua Doc Gia            #";
	
	int inputCurrent = 0;
	int chooseFromConfirm;
	EditText edtCurrent;
	char event;
	ShowCur(true);	
	bool isExit= false;
	bool isExitChange = false;
	bool isEdit= false;
	int yy=30;
	while (!isExit){
			event = nhapSo(edtMa);
//			if (event == DOWN) {
//				gotoxy(0,yy++);cout<<"down";
//			}
			if (event == DOWN){
					if (*edtMa.isError == false){
						inputCurrent = 0;
						isExitChange = false;
						while (!isExitChange){
							edtCurrent = edtArr[inputCurrent];
							//choose type input for edittext
							switch(edtCurrent.type){
								case NUMBER_TYPE:
									event = nhapSo(edtCurrent);
									break;
								case ALPHABET_TYPE:
									event = nhapChu(edtCurrent);
									break;
							}
							//handle error/complete with each edittext
							if (edtCurrent.value->size()==0){
								//error with input
								*edtCurrent.isError = true;
								showError(65,edtCurrent.y,"Khong de trong!");
							} else {
								if (edtCurrent.isError){
									*edtCurrent.isError = false;
									dimissErrorInput(65,edtCurrent.y,15);
								}
								//cac truong hop dac biet
								string v = *edtCurrent.value;
								switch(inputCurrent){
									case 2:
										if (!v.compare("Nam") || !v.compare("Nu") ){
											showCorrect(65,edtCurrent.y,"Hoan thanh");
										}else {	
											*edtCurrent.isError = true;
											showError(65,edtCurrent.y,  "Nhap sai! ");
										}
										break;
									case 3:
										if (!v.compare("0")||!v.compare("1")){
											showCorrect(65,edtCurrent.y,"Hoan thanh");
										} else {
											*edtCurrent.isError = true;
											showError(65,edtCurrent.y,  "Nhap sai! ");
										}
										break;
									default:
										showCorrect(65,edtCurrent.y,    "Hoan thanh");
										break;
								}
								
							}
							//hanlde event down |up |right |esc key
					  		switch (event) {
					  			case DOWN :
					  				if  (inputCurrent<inputItem-1){
										inputCurrent++;
									} else {
										inputCurrent = 0 ;
									}
					  			  	break;
					  			case RIGHT_ARROW:
					  					//move to confirm menu on right
										chooseFromConfirm = onHanldeConfirmThemDocGiaUI(inputCurrent,inputItem,xConfirm,yConfirm,confirmName);
										if (chooseFromConfirm == CONFIRM){
											isEdit=true;
												for (int i=0;i<inputItem; i++){
													if (*edtArr[i].isError == true){
														inputCurrent = i;
														isEdit = false;
														break;
													}
												}
												if (isEdit){
													// all are fine to insert to Doc Gia Tree
													int r = editDocGia(dgTree,createDocGia(edtArr,id));
													SaveFileDocGia(dsDocGia,"DocGiaData.txt");
													if(r==1){
														clearState();
														showState("Da chinh sua Doc gia: "+*edtArr[0].value+" "+*edtArr[1].value);
													} else {
														showState("Co loi xay ra. Vui long thu lai sau!");
													}
													inputCurrent = 0;
												}
										} else {
											if (chooseFromConfirm == ESC || chooseFromConfirm == EXIT){
												isExitChange = true;
											}
										}
				
					  				break;
								case UP :
									if  (inputCurrent>0){
										inputCurrent--;
									} else {
										inputCurrent = inputItem-1;
									}
					  			  	break;
					  			  	
					  			case ESC:
					  				isExitChange = true;
					  				break;
					  			case ENTER :
									if (inputCurrent<inputItem-1){
						  				inputCurrent++;
									}
					  				break;
					  		}  // end switch
					
						}
					
					} else {
						event = showDanhSachDocGiaUI(dsDocGia,slShowDocGia);
						if (event == ESC ){
							isExit = true;
							break;
						}
					}
		
				}else
				if (event == ESC){
					isExit = true;
				} else
				if (event == ENTER){
					//handle error/complete with each edittext
					clearScreen(97,44,40,3);
					clearScreen(50,41,30,10);
					drawEditDocGiaUI();
					if (edtMa.value->size()==0){
						//error with input
						*edtMa.isError = true;
						showError(90,edtMa.y,"Vui long nhap ma Doc Gia!");
					} else {	
						idString = *edtMa.value;
						id = atoi(idString.c_str());
						dgTree = searchDocGia(dsDocGia,id);
						
						if (dgTree == NULL){	
							showError(90,edtMa.y,"Doc gia khong ton tai!   ");
							*edtMa.isError = true;
						} else {
							*edtMa.isError = false;
							showCorrect(90,edtMa.y,"                         ");	
							showInforInDeleteDocGia(dgTree->docGia);
							insertDataToEdittext(edtArr,dgTree->docGia);
						}
		
					}
				}
	}
	clearState();
	clearScreen(30,30,105,31);
	clearScreen(30,64,112,slShowDocGia+4);
	ShowCur(false);
	deleteEditTexts(edtArr,inputItem);
	menuDocGia(chooseFromMenu1,chooseFromMenu2);
}

//void createDemoData(DocGiaTree &dsDocGia){
//	DocGia dg1;
//	strcpy(dg1.ho,"Ho");
//	strcpy(dg1.ten,"Hien");
//	dg1.maDocGia=12;
//	strcpy(dg1.phai,"Nam");
//	dg1.trangThaiThe =1;
//	initNodeMuonTra(dg1.firstMuonTra);
//	
//	MuonTra mt1;
//	mt1.dateMuon.Day=1;
//	mt1.dateMuon.Month=4;
//	mt1.dateMuon.Year=2018;
//	mt1.dateTra.Day=20;
//	mt1.dateTra.Month=4;
//	mt1.dateTra.Year=2018;
//	mt1.maSach = 12;
//	mt1.trangThai = 0;
//	
//	MuonTra mt2;
//	mt2.dateMuon.Day=2;
//	mt2.dateMuon.Month=4;
//	mt2.dateMuon.Year=2018;
//	mt2.dateTra.Day=20;
//	mt2.dateTra.Month=4;
//	mt2.dateTra.Year=2018;
//	mt2.maSach = 12;
//	mt2.trangThai = 0;
//	
//		MuonTra mt3;
//	mt3.dateMuon.Day=3;
//	mt3.dateMuon.Month=4;
//	mt3.dateMuon.Year=2018;
//	mt3.dateTra.Day=20;
//	mt3.dateTra.Month=4;
//	mt3.dateTra.Year=2018;
//	mt3.maSach = 12;
//	mt3.trangThai = 1;
//
//	
//	insertNodeMuonTra(dg1.firstMuonTra,createNodeMuonTra(mt1));
//	insertNodeMuonTra(dg1.firstMuonTra,createNodeMuonTra(mt2));
//		insertNodeMuonTra(dg1.firstMuonTra,createNodeMuonTra(mt3));
//	
//	DocGia dg2;
//	strcpy(dg2.ho,"Nguyen");
//	strcpy(dg2.ten,"Thuan");
//	dg2.maDocGia=13;
//	strcpy(dg2.phai,"Nam");
//	dg2.trangThaiThe =1;
//	initNodeMuonTra(dg2.firstMuonTra);
//	
//	DocGia dg3;
//	strcpy(dg3.ho,"Gia");
//	strcpy(dg3.ten,"Huy");
//	dg3.maDocGia=11;
//	strcpy(dg3.phai,"Nu");
//	dg3.trangThaiThe =2;
//	initNodeMuonTra(dg3.firstMuonTra);
//	
//	insertDocGia(dsDocGia,dg1);
//	insertDocGia(dsDocGia,dg2);
//	insertDocGia(dsDocGia,dg3);
//}





