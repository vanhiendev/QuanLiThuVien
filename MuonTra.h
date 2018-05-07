

#define DANG_MUON 0
#define DA_TRA 1
#define MAT_SACH 2

struct MuonTra{
	int maSach;
	int trangThai;
	DateTime dateMuon;
	DateTime dateTra;
	
};
struct NODEMUONTRA{
	MuonTra muonTra;
	NODEMUONTRA *nextNode;
};
typedef struct NODEMUONTRA * NodeMuonTra;


NodeMuonTra createNodeMuonTra(MuonTra m);
void initNodeMuonTra(NodeMuonTra &node);
int soLuongNodeMuonTra(NodeMuonTra first);
int insertNodeMuonTra(NodeMuonTra &node,NodeMuonTra nodeMuonTra);
int deleteAllNodeMuonTra(NodeMuonTra &first);
