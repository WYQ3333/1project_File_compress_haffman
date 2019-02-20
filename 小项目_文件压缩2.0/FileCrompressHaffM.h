#pragma once
#include"HaffmanTree.hpp"
#include<iostream>
#include<string>
#include<vector>
#include<assert.h>
using namespace std;

typedef unsigned UCH;

struct Char_info{
	UCH _ch;			//��¼��ǰ�ַ�
	long long _char_count;		//��ǰ�ַ����ֵĴ���
	string _ch_code;			//��ǰ�ַ��Ĺ���������
	Char_info(long long char_count = 0)
		:_char_count(char_count)
	{}

	Char_info operator+(const Char_info& temp){
		return Char_info(temp._char_count + _char_count);
	}

	bool operator>(const Char_info& temp)const{
		return temp._char_count<_char_count;
	}
	
	bool operator<(const Char_info& temp)const{
		return temp._char_count>_char_count;
	}
	//�Ƚ�ʱ��tempΪconst��,invalidҲΪconst��
	
	bool operator!=(const Char_info& temp)const{
		return temp._char_count!=_char_count;
	}

	bool operator==(const Char_info& temp)const{
		return temp._char_count == _char_count;
	}

};

class FileCrompress{
public:
	FileCrompress();
	void CompressFile(const string& strFilePath);

	void UNCompressFile(const string& strFilePath);
	void WriteHead(FILE* fOt, const string& strFilePath);

private:
	void GetLine(FILE* fIn, string& strContent);
	void GetHaffmanCode(HaffManTreeNode<Char_info>* pRoot);
	vector<Char_info> _char_info;
};