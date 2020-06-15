#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <vector>
using namespace std;

vector<string> getSentences(string str) {
    vector<string> sentences;
    size_t found = str.find_first_of(".?!"), start = 0;
    while(found != std::string::npos) {
        // sentence end found add to vec.
        int tempLen = found + 1 - start;
        string sentence = str.substr(start, tempLen);
        sentences.push_back(sentence);
        cout << sentence << endl;
        // set start of next sentence.
        start = found + 2;
        found = str.find_first_of(".?!", found + 1);
    }
    return sentences;
}
vector<string> getTokens(string str) {
    vector<string> tokens;
    stringstream seek(str);
    string temp;
    // latin tokenization just from whitespace ' '.
    while(getline(seek, temp, ' ')) {
        tokens.push_back(temp);
    }
    // logging ...
    for(int i = 0; i < tokens.size(); i++) {
        cout << tokens[i] << endl;
    }
    return tokens;
}