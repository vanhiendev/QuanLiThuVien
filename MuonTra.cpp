#include<iostream>

using namespace std;

NodeMuonTra createNodeMuonTra(MuonTra m){
	NodeMuonTra node= new NODEMUONTRA();
	if (node == NULL){
		//het bo nho 
		return NULL;
	}
	node->nextNode = NULL;
	node->muonTra = m;
	return node;
}

void initNodeMuonTra(NodeMuonTra &node){
	node = NULL;
}

int soLuongNodeMuonTra(NodeMuonTra first){
	if (first!=NULL){
		int sl = 0;
		for (NodeMuonTra x = first ; x!=NULL ; x= x->nextNode){
			sl++;
		}
		return sl;
	} else 
	return 0;
	
}

int insertNodeMuonTra(NodeMuonTra &node,NodeMuonTra nodeMuonTra){
	
	if (nodeMuonTra==NULL){
		return 0;
	}
	if (node == NULL){
		node = nodeMuonTra;
	} else {
		for (NodeMuonTra i = node;i != NULL;i = i->nextNode){
			if(i->nextNode == NULL){
				i->nextNode = nodeMuonTra;
				break;
			}
		}
	}
	return 1;
}

int deleteAllNodeMuonTra(NodeMuonTra &first){
	int sl = 0;
	NodeMuonTra n;
	while (first!=NULL){
		n = first;
		first = first->nextNode;
		delete n;
		sl++;
	}
	return sl;
}


