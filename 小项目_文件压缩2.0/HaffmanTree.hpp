#include"FileCrompressHaffM.h"
#include<queue>

template<class W>
struct HaffManTreeNode{
public:
	HaffManTreeNode(const W& weight)
		:_pLeft(nullptr)
		, _pRight(nullptr)
		, _pParent(nullptr)
		, _weight(weight){}

	
	typedef HaffManTreeNode<W> HFNode;
	bool operator>(const HFNode*& temp){
		return _weight > temp->_weight;
	}

	HaffManTreeNode<W>* _pLeft;
	HaffManTreeNode<W>* _pRight;
	HaffManTreeNode<W>* _pParent;
	W _weight;
};

template<class W>
struct Less{
	bool operator()(const W& pLeft, const W& pRight){
		return pLeft > pRight;
	}
};

template<class W>
class HaffManTree{
	typedef HaffManTreeNode<W> HFNode;
	typedef HFNode* pHFNode;
public:
	//构造函数
	HaffManTree()
		:_pRoot(nullptr)
	{}
	~HaffManTree(){
		_destory(_pRoot);
	}

	//建立haffman树

	void CreadHaffmanTree(const vector<Char_info>& char_info, W invalid){
		//if (Char_info.empty()){
		//	//统计的字符信息为空
		//	return;
		//}
		
		priority_queue<pHFNode, vector<pHFNode>, Less<pHFNode>> q;
		

	}

private:
	HFNode* _pRoot;

	//递归方式后序遍历销毁haffman树
	void _destory(pHFNode pRoot){
		if (nullptr == pRoot){
			return;
		}
		_destory(pRoot->_pLeft);
		_destory(pRoot->_pRight);

		delete pRoot;
	}
};