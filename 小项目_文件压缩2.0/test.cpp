#include"FileCrompressHaffM.h"
#include"HaffmanTree.hpp"

void TestFunc(){
	FileCrompress f;
	f.CompressFile("1.txt");
}


//void TestFuncHaffMan(){
//	vector<int> array{1, 3, 5, 7};
//	HaffManTree<int> ht;
//	ht.CreadHaffmanTree(array);
//}

int main(){
	TestFunc();
	system("pause");
	return 0;
}