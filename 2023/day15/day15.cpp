#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
using namespace std;

int getHash(string s) {
    int val = 0;
    for(char c : s) {
        val += c;
        val *= 17;
        val %= 256;
    }
    return val;
}

int main() {
    //read line from a file 
    ifstream file("input");
    string line;
    getline(file, line);
    vector<list<pair<string, int>>> hashmap(256);
    vector<string> steps;
    string step;
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ',') {
            steps.insert(steps.end(), step);
            step = "";
        } else {
            step += line[i];
        }
        if(i == line.size() - 1) {
            steps.insert(steps.end(), step);
        }
    }

    int totalHash = 0;
    for (string s : steps) {
        if(s.find('-' != string::npos)) {
            string label = s.substr(0, s.size() - 1);
            int boxNum = getHash(label);

            if(!hashmap[boxNum].empty()) {
                //remove the pair with the label 
                for (auto it = hashmap[boxNum].begin(); it != hashmap[boxNum].end(); it++) {
                    if(it->first == label) {
                        hashmap[boxNum].erase(it);
                        break;
                    }
                }
            }
        }
        if(s.find('=') != string::npos) {
            string label = s.substr(0, s.find('=') );
            int lens = stoi(s.substr(s.find('=') + 1, s.size()));

            int boxNum = getHash(label);
            bool found = false;
            for (auto it = hashmap[boxNum].begin(); it != hashmap[boxNum].end(); it++) {
                if(it->first == label) {
                    found = true;
                    it->second = lens;
                    break;
                }
            }
            if(!found){
                hashmap[boxNum].push_back(make_pair(label, lens));
            }
        }

        int hashValue = getHash(s);
        totalHash += hashValue;
        cout << s << " " << hashValue << endl;
    }

    int totalFocusingPower = 0;
    int boxIndex = 1;
    for (auto box : hashmap) {
        cout << "box " << boxIndex << " : ";
        int lensIndex = 1;
        for (auto it = box.begin(); it != box.end(); it++) {
            int focusingPower = boxIndex * lensIndex * it->second;
            cout << it->first << " " << it->second << " ";
            totalFocusingPower += focusingPower;
            lensIndex++;
        }
        cout << endl;
        boxIndex++;
    }

    cout << "part 1 :" << totalHash << endl;
    cout << "part 2 :" << totalFocusingPower << endl;
    return 0;
}