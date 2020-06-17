#include <iostream>
#include <vector>
#include "tokenize.h"
using namespace std;

int main() {
    cout << "Input latin phrase: " << endl;
    string test = "Ignorantia non est argumentum. Alea jacta est.";
    vector<string> token = getTokens(test);
    getSentences(test);
    return 0;
}