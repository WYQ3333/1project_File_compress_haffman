#pragma once

#include<iostream>
#include<string>
#include<vector>
using namespace std;

struct Char_info{
	char _ch;			//��¼��ǰ�ַ�
	long long _char_count;		//��ǰ�ַ����ֵĴ���
	string _ch_code;			//��ǰ�ַ��Ĺ���������
	Char_info()
		:_ch(0)
		, _char_count(0)
		, _ch_code("")
	{}
};

class FileCrompress{
public:
	void CompressFile(const string& strFilePath);

	void UNCompressFile(const string& strFilePath);
};