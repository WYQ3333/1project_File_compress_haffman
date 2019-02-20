#include"FileCrompressHaffM.h"

template<class W>
struct HaffManTreeNode{
public:
	HaffManTreeNode(const W& weight)
		:_pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _weight(weight){}

	HaffManTreeNode<W>* _pLeft;
	HaffManTreeNode<W>* _pRight;
	HaffManTreeNode<W>* _pParent;
	W _weight;
};

template<class W>
class HaffManTree{
	typedef HaffManTreeNode<W> HFNode;
	typedef HFNode* pHFNode;
public:
	//���캯��
	HaffManTree()
		:_pRoot(nullptr)
	{}
	~HaffManTree(){
		_destory(_pRoot);
	}

	//����haffman��

	void CreadHaffmanTree(const vector<Char_info>& Char_info, W invalid){

	}

private:
	HFNode* _pRoot;

	//�ݹ鷽ʽ�����������haffman��
	void _destory(pHFNode pRoot){
		if (nullptr == pRoot){
			return;
		}
		_destory(pRoot->_pLeft);
		_destory(pRoot->_pRight);

		delete pRoot;
	}
};