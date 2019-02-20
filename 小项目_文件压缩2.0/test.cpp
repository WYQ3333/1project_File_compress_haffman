#include"FileCrompressHaffM.h"

void TestFunc(){
	FileCrompress f;
	f.CompressFile("1.txt");
	f.UNCompressFile("1.hzp");
}


void TestFuncHaffMan(){
	vector<int> array{1, 3, 5, 7};
	HaffManTree<int> ht;
	ht.CreateHaffmanTree(array,array[0]);
}

int main(){
	TestFuncHaffMan();
	system("pause");
	return 0;
}