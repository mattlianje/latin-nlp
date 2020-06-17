#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <vector>
using namespace std;

class contextualToken {
    int index;
    string val;
    string tag;
    vector<int> tailIndices;
    public:
        void set_values (int, string, string, vector<int>);
};

void contextualToken::set_values (int x, string y, string z, vector<int> a) {
  index = x;
  val = y;
  tag = z;
  tailIndices = a;
}

class sentence {
    vector<contextualToken> tokens;
    public:
        void add_token (contextualToken);
};

void sentence::add_token (contextualToken token) {
    tokens.push_back(token);
}

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
        if(temp.back() == '.' || temp.back() == '?' || temp.back() == '!') {
            temp.pop_back();
            tokens.push_back(temp);
        }
        else {
            tokens.push_back(temp);
        }
    }
    // logging ...
    for(int i = 0; i < tokens.size(); i++) {
        cout << tokens[i] << endl;
    }
    return tokens;
}