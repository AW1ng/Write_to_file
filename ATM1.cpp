#include <iostream>
#include <fstream>
#include <time.h>
#include <string>
#include <map>
#include <vector>
#include <algorithm>


using namespace std;

int GetRandomInt(int From, int To, bool NeedInit = false) {
	int result;
	if(NeedInit) srand(time(0));
	result = rand() % (To - From  + 1) + From; 
	return result;
}


class Storage {
	
	protected:
		map<string, int> Items;
	public:
		
		map<string, int> GetItems() {
			return Items;
		}
		
		Storage() {
			
			cout << "Constructing empty storage...\n";
			Items.clear();
		}
		
		
		void Print() {
			for( const auto n : Items ) {
				string Name = n.first;
				int Amount = n.second;
				cout << Name << "\t" << Amount << "\n";
			}
		}
		
		void Add(string Name, int HowMuch) {
			cout << "Adding some stuff...\n";
			if( !Check(Name) ) Items[Name] = HowMuch;
			else Items[Name] += HowMuch;
		}
		
		int GetAmount(string Name) {
			if( !Check(Name) ) return 0;
			else return Items[Name];
		}
		
		bool Check(string Name) {
			if( Items.count(Name) == 0 ) return false;
			else return true;
		}
		
		int Take(string Name, int HowMuch) {
			if( !Check(Name) ) return 0;
			else if(Items[Name] >= HowMuch) {
				Items[Name] -= HowMuch;
				return HowMuch;
			}
			else {
				int result = Items[Name];
				Items[Name] = 0;
				return result;
			}
		}
		
		string GetAnyWithValue(int value) {
			for ( const auto n : Items ) {
				string Name = n.first;
				int Amount = n.second;
				if(Amount == value) return Name;
			}
			return "";
		}
};


class ValuedStorage {
	string Path;
	public:
		Storage Items, Prices;
	
		ValuedStorage(string path) {
			cout << "Constructing valued storage...\n";
			Path = path;
//			Prices.clear();
		}
		void Add(string Name, int Amount, int Price) {
			Items.Add(Name, Amount);
			Prices.Add(Name, Price);
		}
		int GetPrice(string Name) {
			if(Items.GetAmount(Name) ) return Prices.GetAmount(Name);
			else return 0;
		}
		void Print() {
				ofstream Money(Path + "\\atm.bin", ios::binary);
			for (const auto n : Items.GetItems()) {
				string Name = n.first;
				int Amount = n.second;
				int Price = GetPrice(Name);
				Money << Name << "\t" << Amount << "\t" << Price << "\n";
				cout << Name << "\t" << Amount << "\t" << Price << "\n";
			}
		}
		
		
	bool canGreed(int Need ) {
		vector<int> AllowedNow;
		while( Need > 0 ) {
			AllowedNow.clear();
			for (const auto n : Items.GetItems()) {
				string Name = n.first;
				int Amount = n.second;
				if( Amount ) AllowedNow.push_back( GetPrice(Name) );
				int Price = GetPrice(Name);
				cout << Name << "\t" << Amount << "\t" << Price << "\n";
			}
			sort( AllowedNow.begin(), AllowedNow.end(), [](int a, int b) {return a > b;} );
//			for(int i = 0; i < AllowedNow.size(); i++) {
//				cout << AllowedNow[i];
//			}
			cout << "\n";
			int i = 0;
			while( i < AllowedNow.size() && AllowedNow[i] > Need ) i++; // can do it binary...
			if( AllowedNow[i] < Need ) return false;
			else {
				cout << i << " " << "Al " << AllowedNow.size() <<"\n"; 
				ifstream MoneySeeker(Path + "\\atm.bin", ios::binary);
				if(MoneySeeker.is_open()) {
				cout << "We can take " << AllowedNow[i] << endl;
				string Name = Prices.GetAnyWithValue( AllowedNow[i] );
				cout << "NAME " << Name << "\n";
				MoneySeeker >> Name;
				Items.Take(Name, 1);
				Need -= AllowedNow[i];
				cout << "TOTAL " << Need <<"\n";
				}
			}
		}
	}

};




int main() {
	
	string path = "C:\\Users\\Alex_dev\\Desktop\\Prog\\skill\\WriteToFile\\files";
	ValuedStorage *Sklad = new ValuedStorage(path);
	string Nominals[] = {"1", "2", "3", "5", "10", "15", "25", "50", "100"};
	int Prices[] = {1, 2, 3, 5, 10, 15, 25, 50, 100};
	int rAmount;
	GetRandomInt(0, 10, true);
	for( int i = 0; i < sizeof(Nominals) / sizeof(string); i++ ) {
		cout << Nominals[i] <<'\n';
	 	rAmount = GetRandomInt(0, 5);
		Sklad->Add(Nominals[i], rAmount, Prices[i]);
	}

	Sklad->Print();
	Sklad->canGreed(39);
	cout << "\n";


}


