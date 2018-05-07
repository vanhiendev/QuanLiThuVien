#include<iostream>
#include<fstream>
//#include <stdlib.h>     /* srand, rand */
//#include <time.h>       /* time */
#define MAX_MA_DOC_GIA 1000
using namespace std;

int getIdRandomDocGia(){
	fstream f("MaDocGiaRandomData.txt");
	if (f.fail()){
		return -2;
	}
	int sl=0;
	int result = -1;
	f>>sl;
	if (sl>0){
		f>>result;
	}
	f.close();
	//doc gia da full
	return result;
}
//delete first value in
int deleteFirstIdRandomDocGia(){
	fstream f("MaDocGiaRandomData.txt");
	ofstream fNew("MaDocGiaRandomDataCreate.txt");
	if (f.fail()){
		return -1;
	}
	int sl=0;
	f>>sl;
	if (sl==0){
		return 0;
	}
	
	sl--;
	
	int oldValue;
	f>>oldValue;
	
	fNew<<sl<<endl;
	
	for (int i=0 ; i<sl-1;i++){
		f>>oldValue;
		fNew<<oldValue<<endl;
	}
	f.close();
	fNew.close();
	remove("MaDocGiaRandomData.txt");
	rename("MaDocGiaRandomDataCreate.txt","MaDocGiaRandomData.txt");
	//doc gia da full
	return 1;	
}
int recreateIdRandomDocGia(int idRecycle){
	fstream f("MaDocGiaRandomData.txt");
	fstream fNew("MaDocGiaRandomDataCreate.txt",ios::app);
	if (f.fail()){
		return -1;
	}
	int sl;
	f>>sl;
	
	sl++;
	
	fNew<<sl<<endl;
	
	fNew<<idRecycle<<endl;
	
	int value;
	
	if (sl-1>0){
		while(!f.eof()){
		f>>value;
		fNew<<value<<endl;
		}
	}

	f.close();
	fNew.close();
	
	remove("MaDocGiaRandomData.txt");
	rename("MaDocGiaRandomDataCreate.txt","MaDocGiaRandomData.txt");
	//doc gia da full
	return 1;
}


//int main(){
//	int arr1[MAX_MA_DOC_GIA], arr2[MAX_MA_DOC_GIA];
//	int size1=MAX_MA_DOC_GIA,size2=0;
//	for (int i=0;i<MAX_MA_DOC_GIA;i++){
//		arr1[i] = i;
//	}
//	srand(time(NULL));
//	//random from 0-999 
//	//[a,b] int s=rand() % (b-a+1)+a 
//
//	for (int i=0;i<MAX_MA_DOC_GIA;i++){
//		int rd = rand()%size1;
//		int value = arr1[rd];
//		arr1[rd] = arr1[size1-1];
//		arr2[i] = value;
//		size1--;
//		size2++;
//	}	
//	ofstream f("MaDocGiaRandomData.txt");
//	f<<size2<<endl;
//	for (int i=0;i<size2;i++){
//		f<<arr2[i]<<endl;
//	}
//	cout<<size2;
//	f.close();

//-----------------
//	fstream f("DocGiaData.txt");
//
//	f<<1<<" "<<"Ho"<<" "<<"Hien"<<endl;
//	f<<2<<" "<<"Ho"<<" "<<"Thuan"<<endl;
//	f.close();
//
//	return 0;	
//}
