#include <iostream>
#include <string> 
#include <fstream> 
#include <filesystem>
#include <sstream>

using namespace std; 


int getRandFish(int from, int to, bool need_init = false){
			if(need_init) srand((unsigned)time(0));
			int result = rand() % (to - from + 1);
			return result;
		}


class TextFile {
	protected:
	string Name, Path, filename;
	ifstream *File;
	public:
		TextFile(string name) {
			cout << "TextFile Constructing...\n";
			Name = name;
			filesystem::path cwd = filesystem::current_path();
			Path = cwd.string();
			std::filesystem::path cwd_full = cwd / Name;
			filename = cwd_full.string();
			File = new ifstream( filename );
		}
	
		~TextFile() {
			cout << "TextFile Destructing...\n";
			File->close();
			delete File;
		}
		void AllStringsPrint() {
		
			string s;
			while(getline(*File, s)){ 
       		 	cout << s << endl; 
   			}
		}
		string getRFish(){
			string s, fish; 
			cout << Path <<" " << filename << "\n";
			ifstream FishType(filename);
			int random_fish, j = 0;
			string r_fish;
			if(FishType.is_open()) {
		
				random_fish = getRandFish(0, 10, true);
				
				while(!FishType.eof()) {
					FishType >> fish;
					if(j == random_fish) {
						return fish;
					}
					j++;
				}

				FishType.close();
			}
			else cout << "NO DATA\n";

			return fish;
		}	
}; 


class GreppedFile : public TextFile {
	public:
		GreppedFile(string name) : TextFile(name) {	
			cout << "GreppedFile Constructing...\n";		
		}
		
		void fishing( string src, string fish ){
			ofstream Basket( "basket.txt", ios::app );
			while(getline(*File, src)){
				if( src == fish ) {
					Basket << fish << '\n';
					cout << src << " == " << fish << "\n";
				}
			}
		}
};


int main(int argc, char *argv[]){
	
	TextFile *CurFile;
	GreppedFile *grep;
	int random_fish;
	cout << "Our args: \n";
	for(int i = 0; i < argc; i++) {
		string CurArg = argv[i];
//		cout << i << '\n'; // << CurArg
		CurFile = new TextFile("river.txt");
		grep = new GreppedFile("river.txt");

		grep->fishing(CurArg, grep->getRFish());
//		CurFile->AllStringsPrint();
//		grep->AllStringsPrint();
		delete CurFile;
		delete grep;
	}
	


    return 0;
}
