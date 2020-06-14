#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;

vector<string> getTokens(string str) {
    vector<string> tokens;
    stringstream seek(str);
    string temp;
    // latin tokenization from whitespace ' '.
    while(getline(seek, temp, ' ')) {
        tokens.push_back(temp);
    }
    // logging ...
    for(int i = 0; i < tokens.size(); i++) {
        cout << tokens[i] << endl;
    }
    return tokens;
}