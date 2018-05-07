#include<iostream>
struct Sach{
	int maSach;
	int trangThai;
	int viTri;
};
struct NODESACH{
	Sach sach;
	NODESACH *nextSach;
};

typedef struct NODESACH * NodeSach;

//tao NodeSach voi nextSach = Null
NodeSach createNodeSach(Sach sach){
	NodeSach node= new NODESACH();
	if (node == NULL){
		//het bo nho 
		return NULL;
	}
	node->nextSach =NULL;
	node->sach = sach;
	return node;
}

void initNodeSach(NodeSach &node){
	node = NULL;
}

int nodeSachEmpty(NodeSach firstNode){
	return firstNode == NULL;
}
//them 1 node vao dau danh sach
int insertNodeSach(NodeSach &firstNode, NodeSach node){
	if (firstNode == NULL){
		//danh sach rong
		firstNode = node;
		return 1;
	}
	if (node == NULL){
		//node chua khoi tao
		return 0;
	}
	for (NodeSach n = firstNode ; n !=NULL; n = n->nextSach){
		if (n->nextSach==NULL){
			n->nextSach = node;
			break;
		}
	}
	return 1;
}
//xoa phan tu dau tien
//int deleteNodeSach(NodeSach firstnode){
//	if (nodeSachEmpty(firstnode)){
//		return 0;
//	}
//	NodeSach n = firstnode;
//	firstnode  = firstnode->nextSach;
//	delete n;
//	return 1;
//}

int soLuongNodeSach(NodeSach first){
	int sl=0;
	for (NodeSach x = first; x!=NULL ; x = x->nextSach){
		sl++;
	}
	return sl;
}
int deleteAllNodeSach(NodeSach &first){
	int sl = 0;
	NodeSach n;
	while (first!=NULL){
		n = first;
		first = first->nextSach;
		delete n;
		sl++;
	}
	return sl;
}

