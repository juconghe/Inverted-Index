#include <string>
#include <queue>
#include <map>
#include <set>
#include <fstream>

#include "inverter.h"

using namespace std;

int fileCounter = -1;
map<string, set<int> > invertedIndex;

void addToMap(string word) {
	// count(key) return number of element inside give key
	// check if given is exist
	if (invertedIndex.count(word) == 0) {
		// std::cout << "inserting "<<word << '\n';
		// std::cout << "Not found in the map inserting" << '\n';
		// Create a value for the given key in the map
		set<int> tempSet;
		tempSet.insert(fileCounter);
		invertedIndex.insert(pair<string, set<int> >(word,tempSet));
	} else {
		// since the key is already exist, just update the value
		invertedIndex[word].insert(fileCounter);
	}
}

string build_inverted_index(string filename){
	string inputName,info,result,word;
	ifstream infile,subFile;
	//open the input file
	infile.open(filename, std::ifstream::in);
	// check if the file is openable
	if (infile.is_open()) {
		//give each filename line by line
		while (getline(infile,inputName)) {
			//open each file in the input file
			subFile.open(inputName, std::ifstream::in);
			//check if file is openable
			if (subFile.is_open()) {
				// increase the doc number
				fileCounter += 1;
				// cout << "I am reading " << inputName << '\n';
				// read line by line of the file
				while (getline(subFile,info)) {
					// std::cout << info << '\n';
					// read each character of the line and sperate them if there is a
					// no alphabet letter
					for (unsigned i = 0; i < info.length(); i++) {
						if (isalpha(info[i])) {
							word += info[i];
						} else if (!word.empty()){
							addToMap(word);
							word.clear();
						}
					}
					// this is a special condition when line end with no special character
					if (!word.empty()) {
						addToMap(word);
						word.clear();
					}
				}
			}
			// close the file
			subFile.close();
		}
	}
	// close the file
	infile.close();

	// iterate throught the map and its given value
	for (std::map<string, set<int>>::iterator itr = invertedIndex.begin();
			itr!=invertedIndex.end();++itr) {
				// std::cout << itr->first << ": ";
				result += itr->first + ":";
				for (set<int>::iterator setItr = (itr->second).begin();
						setItr!= (itr->second).end();++setItr) {
							// std::cout << *setItr << " ";
							result += " "+to_string(*setItr);
						}
				// std::cout << "adding next line to result" << '\n';
				result += "\n";
			}
	return result;
}
