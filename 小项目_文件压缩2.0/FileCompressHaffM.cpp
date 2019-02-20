#define _CRT_SECURE_NO_WARNINGS
#include"FileCrompressHaffM.h"
#include"HaffmanTree.hpp"

void FileCrompress::CompressFile(const string& strFilePath){
	//��ȡ��ǰ�ļ����ַ��ĳ��ִ���

	FILE* fIn = fopen(strFilePath.c_str(), "rb");	//��C�ַ����ķ�ʽ�������Ƶķ�ʽ���ļ�
	if (nullptr == fIn){
		cout << "���ļ�ʧ��:";
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
			char_info[pReadBuff[i]]._ch = pReadBuff[i];		//��¼��ǰ�ַ�
			char_info[pReadBuff[i]]._char_count++;			//ͳ�Ƶ�ǰ�ַ����ĵ��г��ֵĴ���
		}
	}

	HaffManTree<Char_info> ht;
	ht.CreadHaffmanTree(char_info);

}