#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <cmath>
#include <set>

using namespace std;

vector<unsigned long> xorSum(const vector<unsigned long> &vec1, const vector<unsigned long> &vec2) {
    vector<unsigned long> vecRes(0);
    for (auto it1 = vec1.begin(), it2 = vec2.begin(); it1 != vec1.end(), it2 != vec2.end(); ++it1, ++it2) {
        unsigned long tmpXor = *it1 ^*it2;
        vecRes.push_back(tmpXor);
    }
    return vecRes;
}

int weight(const vector<unsigned long> &vec){
    int res = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        unsigned long tmpXor = *it;
        for (int i = 0; i < sizeof(unsigned long) * 8; ++i) {
            res += tmpXor & 0b1;
            tmpXor = tmpXor >> 1;
        }
    }
    return res;
}

int main() {
    string str;
    ifstream inputFile("input.txt");
    vector<vector<unsigned long>> startVec;
    set<vector<unsigned long>> endSet;
    unsigned long bitLen = 0;
    unsigned long longLen = 0;
    map<int, unsigned long> diagram;
    while (getline(inputFile, str)) {
        bitLen = str.size();
        longLen = (unsigned long) ceil((double) bitLen / (sizeof(unsigned long) * 8));
        vector<unsigned long> oneStr(longLen, 0);
        auto itStr = str.begin();
        for (int i = 0; i < longLen; ++i) {
            int bitCount = 0;
            while ((bitCount < sizeof(unsigned long) * 8) && itStr != str.end()) {
                oneStr[i] = (oneStr[i] << 1) | (*itStr == '1' ? 0b1 : 0b0);
                bitCount++;
                itStr++;
            }
        }
        startVec.push_back(oneStr);
    }
    inputFile.close();

    for (auto itVec1 = startVec.begin(); itVec1 != startVec.end(); ++itVec1) {
        for (auto itVec2 = itVec1+1; itVec2 != startVec.end(); ++itVec2) {
            endSet.insert(xorSum(*itVec1,*itVec2)); //TODO MultiThread
        }
    }
    for (auto itSet = endSet.begin(); itSet != endSet.end(); ++itSet) {
        diagram[weight(*itSet)]+=1; //TODO MultiThread
    }
    ofstream outputFile("output.txt");
    for (auto itMap = diagram.begin(); itMap != diagram.end() ; ++itMap) {
        outputFile << (*itMap).first << "\t" << (*itMap).second << endl;
    }
    outputFile.close();
    return 0;
}