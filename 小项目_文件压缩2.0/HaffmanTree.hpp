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
	//���캯��
	HaffManTree()
		:_pRoot(nullptr)
	{}
	~HaffManTree(){
		_destory(_pRoot);
	}

	//����haffman��

	


	void CreateHaffmanTree(const vector<W>& v,const W& invalid)
	{
		if (v.empty())
			return;
			//ͳ�Ƶ��ַ�����ϢΪ��
		priority_queue<pHFNode, vector<pHFNode>, Less<W>> q;
		
		//��char_info�е�Ԫ�ؽ���С��----���ȼ����н���С��
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
			//ȡ��С��������������Ϊһ���½ڵ����������
			pHFNode pParent = new HFNode(pLeft->_weight + pRight->_weight);

			pParent->_pLeft = pLeft;
			pParent->_pRight = pRight;

			pLeft->_pParent = pParent;
			pRight->_pParent = pParent;

			//���µĽ�����С����
			q.push(pParent);
		}
		_pRoot = q.top();
	}

	pHFNode Get_pRoot(){
		return _pRoot;
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