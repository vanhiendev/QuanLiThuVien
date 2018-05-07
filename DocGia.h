

#define THE_BI_KHOA 0
#define THE_HOAT_DONG 1

#define SO_LUONG_DOC_GIA_UI 2
struct DocGia{
	int maDocGia;
	string ho;
	string ten;
	string phai;
	int trangThaiThe;
	NodeMuonTra firstMuonTra;
};
struct DOCGIATREE{
	DocGia docGia;
	DOCGIATREE * pleft;
	DOCGIATREE * pright;
};

typedef struct DOCGIATREE DocGiaNode;
typedef struct DOCGIATREE * DocGiaTree;

void initDocGiaTree(DocGiaTree &tree);
DocGiaNode* createDocGiaNode(DocGia dg);
int insertDocGia(DocGiaTree &tree, DocGia dg);
DocGiaNode* searchDocGia(DocGiaTree tree, int maDocGia);
int editDocGia(DocGiaTree &tree,DocGia dg);
void swapDocGiaNode(DocGiaTree &a, DocGiaTree &b);
int deleteDocGia(DocGiaTree &tree, int maDocGia);
int slDocGia(DocGiaTree t);
void SaveFileDocGia (DocGiaTree dsDocGia,char *tenfile);
void LoadFileDocGia (DocGiaTree &dsDocGia,char *tenfile);
void deleteAllDocGia(DocGiaTree &dsDocGia);

void handelOutOfDocGia(int maDocGia);
int onHanldeConfirmThemDocGiaUI(int &inputCurrent,int inputItem, int xConfirm, int yConfirm, string confirmName);
void drawInsertDocGiaUI();
DocGia createDocGia(EditText arr[], int maDocGia);

void getDocGiaArr(DocGiaTree ds,DocGia arrDocGia[], int &couter);
void insertDocGiaUI(DocGiaTree &dsDocGia, int chooseFromMenu1,int chooseFromMenu2);

void drawDeleteDocGiaUI();
void deleteDocGiaUI(DocGiaTree &dsDocGia,int chooseFromMenu1, int chooseFromMenu2);

void drawEditDocGiaUI();
void editDocGiaUI(DocGiaTree &dsDocGia,int chooseFromMenu1, int chooseFromMenu2);

void showDataDocGia(DocGiaTree dsDocGia);
