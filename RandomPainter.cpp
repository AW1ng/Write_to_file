#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;




int getRandomInt(int from, int to, bool NeedInit = false) {
		int result;
		if(NeedInit) srand((unsigned)time(0));
		result = rand() % (to - from + 1);
		return result;
	}
	

void Paint(string path, int sizeH, int sizeV) {
	
	ofstream Picture(path + "pic.txt");
	if(Picture.is_open()){
		for(int i = 0; i < sizeH; i++) {
			for(int j = 0; j < sizeV; j++) {
				Picture << getRandomInt(0, 1);
			}
			Picture << "\n";
		}
		Picture.close();
	}
	else cout << "Could not open path\n";
}


int main() {
	getRandomInt(0, 1, true);
	string path = "";
	Paint(path, 20, 32);
}

