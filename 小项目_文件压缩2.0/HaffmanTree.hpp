#pragma once
#include<queue>

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
struct Less{
	typedef HaffManTreeNode<W>* pHFNode;
	bool operator()(const pHFNode& pLeft, const pHFNode& pRight){
		return pLeft->_weight > pRight->_weight;
	}
};

template<class W>
class HaffManTree{
public:
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

	


	void CreateHaffmanTree(const vector<W>& v,const W& invalid)
	{
		if (v.empty())
			return;
			//统计的字符的信息为空
		priority_queue<pHFNode, vector<pHFNode>, Less<W>> q;
		
		//将char_info中的元素建立小堆----优先级队列建立小堆
		size_t i = 0;
		for (i = 0; i < v.size(); ++i){
			if (v[i] != invalid){
				q.push(new HFNode(v[i]));
			}
			
		}

		while (q.size()>1){
			pHFNode pLeft = q.top();
			q.pop();
			pHFNode pRight = q.top();
			q.pop();
			//取较小的两个子树，做为一个新节点的左右子树
			pHFNode pParent = new HFNode(pLeft->_weight + pRight->_weight);

			pParent->_pLeft = pLeft;
			pParent->_pRight = pRight;

			pLeft->_pParent = pParent;
			pRight->_pParent = pParent;

			//将新的结点插入小堆中
			q.push(pParent);
		}
		_pRoot = q.top();
	}

	pHFNode Get_pRoot(){
		return _pRoot;
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