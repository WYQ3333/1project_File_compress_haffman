#define _CRT_SECURE_NO_WARNINGS
#include"FileCrompressHaffM.h"
#include"HaffmanTree.hpp"

void FileCrompress::CompressFile(const string& strFilePath){
	//获取当前文件中字符的出现次数

	FILE* fIn = fopen(strFilePath.c_str(), "rb");	//以C字符串的方式，二进制的方式打开文件
	if (nullptr == fIn){
		cout << "打开文件失败:";
		return;
	}
	char * pReadBuff = new char[1024];
	vector<Char_info> char_info(256);
	while (true){
		size_t readsize = fread(pReadBuff, 1, 1024, fIn);
		if (readsize == 0){
			break;
		}
		for (size_t i = 0; i < readsize; ++i){
			char_info[pReadBuff[i]]._ch = pReadBuff[i];		//记录当前字符
			char_info[pReadBuff[i]]._char_count++;			//统计当前字符在文档中出现的次数
		}
	}

	HaffManTree<Char_info> ht;
	ht.CreadHaffmanTree(char_info);

}