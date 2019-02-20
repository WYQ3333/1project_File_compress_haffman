#define _CRT_SECURE_NO_WARNINGS
#include"FileCrompressHaffM.h"

FileCrompress::FileCrompress(){
	//记录当前字符
	_char_info.resize(256);
	size_t i = 0;
	for (i = 0; i < 256; ++i){
		_char_info[i]._ch = i;
	}
}

void FileCrompress::CompressFile(const string& strFilePath){
	//获取当前文件中字符的出现次数

	FILE* fIn = fopen(strFilePath.c_str(), "rb");	//以C字符串的方式，二进制的方式打开文件
	if (nullptr == fIn){
		cout << "打开文件失败:";
		return;
	}
	char * pReadBuff = new char[1024];
	
	while (true){
		size_t readsize = fread(pReadBuff, 1, 1024, fIn);
		if (readsize == 0){
			break;
		}
		for (size_t i = 0; i < readsize; ++i){
			_char_info[pReadBuff[i]]._char_count++;			//统计当前字符在文档中出现的次数
		}
	}
	
	//以每个字符出现的次数为权值创建haffman树
	HaffManTree<Char_info> ht;
	ht.CreateHaffmanTree(_char_info,_char_info[0]);

	////根据haffman获取每个叶子节点的编码
	GetHaffmanCode(ht.Get_pRoot());

	//根据每个字符的编码重写源文件
	FILE* fOut = fopen("1.hzp","w");
	assert(fOut);
	char ch = '0';
	int bitcount = 0;
	fseek(fIn, 0, SEEK_SET);//将文件指针重置到文件起始位置
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

//递归求解字符的编码
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