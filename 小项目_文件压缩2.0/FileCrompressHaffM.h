#pragma once

#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct Char_info{
	char _ch;			//记录当前字符
	long long _char_count;		//当前字符出现的次数
	string _ch_code;			//当前字符的哈夫曼编码
	Char_info(long long char_count = 0)
		:_char_count(char_count)
	{}

	Char_info operator+(const Char_info& temp){
		return Char_info(temp._char_count + _char_count);
	}

	bool operator>(const Char_info& temp){
		return temp._char_count>_char_count;
	}
	
	bool operator<(const Char_info& temp){
		return temp._char_count<_char_count;
	}
	
	bool operator!=(const Char_info& temp){
		return temp._char_count!=_char_count;
	}

	bool operator==(const Char_info& temp){
		return temp._char_count == _char_count;
	}

};

class FileCrompress{
public:
	void CompressFile(const string& strFilePath);

	void UNCompressFile(const string& strFilePath);
};