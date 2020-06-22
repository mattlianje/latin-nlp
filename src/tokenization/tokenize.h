#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <vector>
using namespace std;

class contextualToken {
    public:
        int index;
        string val;
        string tag;
        vector<int> tailIndices;
        void set_values (int, string, string, vector<int>);
};

void contextualToken::set_values (int x, string y, string z, vector<int> a) {
  index = x;
  val = y;
  tag = z;
  tailIndices = a;
}

class sentence {
    public:
        vector<contextualToken> tokens;
        void add_token (contextualToken);
};

void sentence::add_token (contextualToken token) {
    tokens.push_back(token);
}

class text {
    vector<sentence> sentences;
    public:
        void add_sentence (sentence);
        void printTokens(void);
        void printSentences(void);
};

void text::printTokens(void) {
    for (int i = 0; i < sentences.size(); i++) {
        sentence curr_sentence = sentences.at(i);
        for (int j = 0; j < curr_sentence.tokens.size(); j++) {
            contextualToken currToken = curr_sentence.tokens.at(j);
            cout << "(" << currToken.index << ") " << currToken.val << " -> tag: " << currToken.tag << endl;
        }
    }
    cout << endl;
}

void text::printSentences(void) {
    cout << endl;
    for (int i = 0; i < sentences.size(); i++) {
        sentence curr_sentence = sentences.at(i);
        for (int j = 0; j < curr_sentence.tokens.size(); j++) {
            contextualToken currToken = curr_sentence.tokens.at(j);
            cout << currToken.val << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void text::add_sentence(sentence stnc) {
    sentences.push_back(stnc);
}

vector<string> getSentences(string str) {
    vector<string> sentences;
    size_t found = str.find_first_of(".?!"), start = 0;
    while (found != std::string::npos) {
        // sentence end found add to vec.
        int tempLen = found + 1 - start;
        string sentence = str.substr(start, tempLen);
        sentences.push_back(sentence);
        // set start of next sentence.
        start = found + 2;
        found = str.find_first_of(".?!", found + 1);
    }
    return sentences;
}

/*
* @input: str e.g. "Ignorantia non est argumentum. Cave canem."
* @output: vec<string> of lating tokens, e.g. text res = <Igronatia, non, est, argumentum, Cave, canem>
*/
vector<string> getTokens(string str) {
    vector<string> tokens;
    stringstream seek(str);
    string temp;
    // latin tokenization just from whitespace ' '.
    while (getline(seek, temp, ' ')) {
        if (temp.back() == '.' || temp.back() == '?' || temp.back() == '!') {
            temp.pop_back();
            tokens.push_back(temp);
        }
        if (temp.back() == ',') {
            string comma;
            comma.push_back(',');
            // Remove last char from string
            temp.resize(temp.size() - 1);
            // Push token THEN comma to the sentence vec
            tokens.push_back(temp);
            tokens.push_back(comma);
        }
        else {
            tokens.push_back(temp);
        }
    }
    return tokens;
}
/*
* @input: str of text, e.g. "Ignorantia non est argumentum. Cave canem."
* @output: text obj, e.g. text res = <sentence1, sentence2>
*/
text tokenizeText(string str) {
    text txt;
    vector<string> sentences = getSentences(str);
    for (int i = 0; i < sentences.size(); i++) {
        sentence stnc;
        vector<string> plainTokens = getTokens(sentences.at(i));
        for (int j = 0; j < plainTokens.size(); j++) {
            string currToken = plainTokens.at(j);
            vector<int> tails;
            string tag = "na";
            contextualToken ctxtToken;
            ctxtToken.set_values(j, currToken, tag, tails);
            stnc.add_token(ctxtToken);
        }
        txt.add_sentence(stnc);
    }
    return txt;
}