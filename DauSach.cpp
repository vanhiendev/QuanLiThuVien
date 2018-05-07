#include "DanhMucSach.cpp"
#include <string.h>

#define MAX_SACH 1000
#define FILE_DAU_SACH "DauSachData.txt"
using namespace std;
struct DauSach{
	int ISBN;
	char tenSach[31];
	int soTrang;
	char tacGia[31];
	int namXuatBan;
	char theLoai[31];
	NodeSach firstSach;
};
struct ListDauSach{
	int size=0;
	DauSach *list[MAX_SACH];
};

bool listDauSachFull(ListDauSach list){
	return list.size == MAX_SACH;
}

bool listDauSachEmpty(ListDauSach list){
	return list.size==0;
}

int insertDauSach(ListDauSach &list,DauSach ds,int position){
	if (listDauSachFull(list) || position<0 ||position>list.size){
		return 0;
	}
	for (int i=list.size-1;i>=position;i--){
		list.list[i+1] = list.list[i];
	}
	DauSach *s = new DauSach;
	*s = ds;
	list.list[position] = s;
	list.size++;
	return 1;	
}

int deleteAllDauSach(ListDauSach &list){
	for (int i=0;i<list.size;i++){
		deleteAllNodeSach(list.list[i]->firstSach);
		delete list.list[i];
	}
}

void SaveFileDauSach (ListDauSach list,char *tenfile){
  	FILE *f; 
	
	f= fopen(tenfile,"wb");
	if (f==NULL) {
  		return ; // null
  	}
  	if (!listDauSachEmpty(list)){
	  	int slDauSach = list.size;
	  	int slNodeSach;
  		fwrite(&slDauSach,sizeof(int),1,f);
  		DauSach *ds;
  		for (int i=0;i<list.size;i++){
  			
  			ds = list.list[i];
		  	fwrite(ds,sizeof(DauSach),1,f);
		  	
		  	slNodeSach = soLuongNodeSach(ds->firstSach);
		  	fwrite(&slNodeSach,sizeof(int),1,f);
		  	if (slNodeSach>0){
		  		for (NodeSach n = ds->firstSach;n!=NULL;n = n->nextSach){
		  			fwrite(&n->sach,sizeof(Sach),1,f);	
				}	
			}
		  	
		}
		
	}
	fclose(f);
}
void LoadFileDauSach (ListDauSach &list,char *tenfile){
	FILE *f; 
	int sl;
	f= fopen(tenfile,"rb");
	if (f==NULL) {
    	return ;
 	}
  	int slDauSach=0,i, j ; 
  	
  //get so luong Dau Sach
  	fread(&slDauSach,sizeof(int),1,f);
  
  //lay data cua tung Dau Sach
  	for (i=0 ; i < slDauSach ;i++) {
  		Sach sach;
  		DauSach dauSach;
  		NodeSach nodeSach;
  		
    	fread(&dauSach,sizeof(DauSach),1,f);
    
		dauSach.firstSach=NULL;
    
    	int slNodeSach = 0;
    
   		fread(&slNodeSach,sizeof(int),1,f);
   		
  		for ( j=0; j <slNodeSach; j++)
  		{ 
	  		fread(&sach,sizeof(Sach),1,f);
	  		
	  		nodeSach = createNodeSach(sach);
	  		
	  		if (nodeSach!=NULL){
	  			//van con bo nho
	  			insertNodeSach(dauSach.firstSach,nodeSach);
			}
	  		
  		}
  		
  		insertDauSach(list,dauSach,list.size);
  }
  fclose(f);
}
void createDauSachDataDemo(ListDauSach &list){
	DauSach ds1,ds2,ds3;
	Sach s1,s2;
	ds1.ISBN = 0;
	ds1.namXuatBan =2016;
	ds1.soTrang =1000;
	ds1.firstSach = NULL;
	strcpy(ds1.tacGia,"Ho Hien");
	strcpy(ds1.tenSach,"DoReMon");
	strcpy(ds1.theLoai,"Truyen Vui");
	
	s1.maSach = 123;
	s1.trangThai = 0;
	s1.viTri = 3;

	s2.maSach = 100;
	s2.trangThai = 1;
	s2.viTri = 4;
	insertNodeSach(ds1.firstSach,createNodeSach(s1));
	insertNodeSach(ds1.firstSach,createNodeSach(s2));
	
	
	ds2.ISBN = 1;
	ds2.namXuatBan =2017;
	ds2.soTrang =1020;
	ds2.firstSach = NULL;
	strcpy(ds2.tacGia,"Ho Thuan");
	strcpy(ds2.tenSach,"Conan");
	strcpy(ds2.theLoai,"Trinh Tham");
	
	ds3.ISBN = 2;
	ds3.namXuatBan =2018;
	ds3.soTrang =100;
	ds3.firstSach = NULL;
	strcpy(ds3.tacGia,"Ho Trung");
	strcpy(ds3.tenSach,"Shin cau be but chi");
	strcpy(ds3.theLoai,"Truyen Hai");
	
	insertDauSach(list,ds1,list.size);
	insertDauSach(list,ds2,list.size);
	insertDauSach(list,ds3,list.size);
}
void showDauSachDataDemo(ListDauSach list){
	for (int i=0;i<list.size;i++){
		cout<<list.list[i]->ISBN<<endl;
		cout<<list.list[i]->namXuatBan<<endl;
		cout<<list.list[i]->soTrang<<endl;
		cout<<list.list[i]->tacGia<<endl;
		cout<<list.list[i]->tenSach<<endl;
		cout<<list.list[i]->theLoai<<endl;
		cout<<"-----------------------"<<endl;
		for (NodeSach n = list.list[i]->firstSach;n!=NULL;n=n->nextSach){
			cout<<"ma sach"<<n->sach.maSach<<" trang thai "<<n->sach.trangThai<<" vi tri "<<n->sach.viTri<<endl; 
		}
		cout<<endl;
	}
	
	cout<<list.size;
}
int main() {
	ListDauSach listDauSach;
	//createDauSachDataDemo(listDauSach);
	//SaveFileDauSach(listDauSach,FILE_DAU_SACH);
	LoadFileDauSach(listDauSach,FILE_DAU_SACH);
	showDauSachDataDemo(listDauSach);
	deleteAllDauSach(listDauSach);
	return 0;
}
