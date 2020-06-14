#include <iostream>
#include <vector>
#include "tokenize.h"
using namespace std;

int main() {
    cout << "Input latin phrase: " << endl;
    string test = "Ignorantia non est argumentum";
    vector<string> token = getTokens(test);
    return 0;
}