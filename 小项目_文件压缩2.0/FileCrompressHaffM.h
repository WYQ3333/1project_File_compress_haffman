#pragma once
#include"HaffmanTree.hpp"
#include<iostream>
#include<string>
#include<vector>
#include<assert.h>
using namespace std;

typedef unsigned UCH;

struct Char_info{
	UCH _ch;			//记录当前字符
	long long _char_count;		//当前字符出现的次数
	string _ch_code;			//当前字符的哈夫曼编码
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
	//比较时，temp为const的,invalid也为const的
	
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