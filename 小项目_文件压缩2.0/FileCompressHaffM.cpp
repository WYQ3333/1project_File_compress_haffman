#define _CRT_SECURE_NO_WARNINGS
#include"FileCrompressHaffM.h"

FileCrompress::FileCrompress(){
	//��¼��ǰ�ַ�
	_char_info.resize(256);
	size_t i = 0;
	for (i = 0; i < 256; ++i){
		_char_info[i]._ch = i;
	}
}

void FileCrompress::CompressFile(const string& strFilePath){
	//��ȡ��ǰ�ļ����ַ��ĳ��ִ���

	FILE* fIn = fopen(strFilePath.c_str(), "rb");	//��C�ַ����ķ�ʽ�������Ƶķ�ʽ���ļ�
	if (nullptr == fIn){
		cout << "���ļ�ʧ��:";
		return;
	}
	UCH * pReadBuff = new UCH[1024];
	
	while (true){
		size_t readsize = fread(pReadBuff, 1, 1024, fIn);
		if (readsize == 0){
			break;
		}
		for (size_t i = 0; i < readsize; ++i){
			_char_info[pReadBuff[i]]._char_count++;			//ͳ�Ƶ�ǰ�ַ����ĵ��г��ֵĴ���
		}
	}
	
	//��ÿ���ַ����ֵĴ���ΪȨֵ����haffman��
	HaffManTree<Char_info> ht;
	ht.CreateHaffmanTree(_char_info,_char_info[0]);

	////����haffman��ȡÿ��Ҷ�ӽڵ�ı���
	GetHaffmanCode(ht.Get_pRoot());

	//����ÿ���ַ��ı�����дԴ�ļ�
	FILE* fOut = fopen("1.hzp","wb");
	assert(fOut);
	WriteHead(fOut, strFilePath);
	char ch = '0';
	int bitcount = 0;
	fseek(fIn, 0, SEEK_SET);//���ļ�ָ�����õ��ļ���ʼλ��
	while (true){
		size_t rdSize = fread(pReadBuff, 1,1024, fIn);
		if (rdSize == 0){
			break;
		}
		for (size_t i = 0; i < rdSize; ++i){
			string& strCode = _char_info[pReadBuff[i]]._ch_code;
			for (size_t j = 0; j < strCode.size(); ++j){
				ch <<= 1;
				if ('1' == strCode[j])
					ch |= 1;
				bitcount++;
				if (8 == bitcount){
					fputc(ch,fOut);
					bitcount = 0;
				}
			}
		}
	}
	if (bitcount < 8&&bitcount>0){
		ch <<= (8 - bitcount);
		fputc(ch, fOut);
	}

	delete[] pReadBuff;
	fclose(fIn);
	fclose(fOut);
}

//�ݹ�����ַ��ı���
void FileCrompress::GetHaffmanCode(HaffManTreeNode<Char_info>* pRoot){
	if (nullptr==pRoot){
		return;
	}

	GetHaffmanCode(pRoot->_pLeft);
	GetHaffmanCode(pRoot->_pRight);

	if (nullptr == pRoot->_pLeft&&nullptr == pRoot->_pRight){
		HaffManTreeNode<Char_info>* pCur = pRoot;
		HaffManTreeNode<Char_info>* pParent = pCur->_pParent;

		string& StrCode = _char_info[pCur->_weight._ch]._ch_code;
		while (pParent){
			if (pCur = pParent->_pLeft){
				StrCode += '0';
			}
			else{
				StrCode += '1';
			}
			pCur = pParent;
			pParent = pCur->_pParent;
		}
		reverse(StrCode.begin(),StrCode.end());
	}
}

void FileCrompress::WriteHead(FILE* fOut, const string& strFilePath){
	string strHeadInfo;
	strHeadInfo += '\n';
	strHeadInfo = strHeadInfo.substr(strFilePath.rfind('.'));
	string strCharInfo;
	char szCount[32];
	size_t lineCount = 0;
	for (size_t i = 0; i < 256; ++i){
		if (_char_info[i]._char_count){
			strCharInfo += _char_info[i]._ch;
			strCharInfo += ',';
			_itoa(_char_info[i]._char_count, szCount, 10);
			strCharInfo += szCount;
			strCharInfo += '\n';
			lineCount++;
		}
	}
	_itoa(lineCount, szCount, 10);
	strHeadInfo += szCount;
	strHeadInfo += '\n';
	strHeadInfo += strCharInfo;
	fwrite(strHeadInfo.c_str(), 1, strHeadInfo.size(), fOut);
}

void FileCrompress::GetLine(FILE* fIn, string& strContent){
	//feof������������ļ�ָ���Ƿ� �����ļ�ĩβ
	while (!feof(fIn)){
		char ch = fgetc(fIn);
		if ('\n' == ch){
			return;
		}
		strContent += ch;
	}
}

void FileCrompress::UNCompressFile(const string& strFilePath){
	//���ѹ���ļ��ĺ�׺��ʽ
	string strPostFix = strFilePath.substr(strFilePath.rfind('.'));
	if (".hzp" != strPostFix){
		cout << "ѹ���ļ��ĸ�ʽ������" << endl;
		return;
	}
	FILE* fIn = fopen(strFilePath.c_str(), "rb");
	if (fIn == nullptr){
		cout << "���ļ�ʧ��" << endl;
		return;
	}
	//��ȡԴ�ļ��ĺ�׺

	strPostFix = "";
	GetLine(fIn, strPostFix);
	string strContent;
	GetLine(fIn, strContent);

	size_t lineCount = atoi(strContent.c_str());
	for (size_t i = 0; i < lineCount; ++i){
		strContent = "";
		GetLine(fIn, strContent);
		if (strContent.empty()){
			strContent += '\n';
			GetLine(fIn, strContent);
		}
		_char_info[(UCH)strContent[0]]._char_count = atoi(strContent.c_str() + 2);
	}
	//����haffman��

	HaffManTree<Char_info> ht;
	ht.CreateHaffmanTree(_char_info, _char_info[0]);

	//��ѹ��

	string strUNComFile = "2";
	strUNComFile += strPostFix;
	FILE* fOut = fopen(strUNComFile.c_str(), "wb");
	assert(fOut);
	char* pReadBuff = new char[1024];
	HaffManTreeNode<Char_info>* pCur = ht.Get_pRoot();
	char pos = 7;
	size_t fileSize = pCur->_weight._char_count;

	while (true){
		size_t rdSize = fread(pReadBuff, 1, 1024, fIn);
		if (rdSize == 0){
			break;
		}
		for (size_t i = 0; i < rdSize; ++i){
			pos = 7;
			for (size_t j = 0; j < 8; ++j){
				
				if (pReadBuff[i] & (1 << pos)){
					pCur = pCur->_pRight;
				}
				else{
					pCur = pCur->_pLeft;
				}

				if (pCur->_pLeft == nullptr&&nullptr == pCur->_pRight){
					fputc(pCur->_weight._ch, fOut);
					pCur = ht.Get_pRoot();
					fileSize--;
					if (0 == fileSize){
						break;
					}
				}
				pos--;
			}
		}
	}
	delete[] pReadBuff;
	fclose(fIn);
	fclose(fOut);
}