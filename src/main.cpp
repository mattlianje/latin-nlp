#include <iostream>
#include <vector>
#include "tokenization/tokenize.h"
#include "phonology/phonology.h"
#include "models/posRuleBased.h"
using namespace std;

int main() {
    cout << " Latin NLP ..." << endl;
    string test = "Quo usque tandem abutere, Catilina, patientia nostra? quam diu etiam furor iste tuus nos eludet? quem ad finem sese effrenata iactabit audacia?";
    text catilina_ptI = tokenizeText(test);
    catilina_ptI.printSentences();
    catilina_ptI.printTokens();
    // string testString;
    // cout << "Input latin string for phonological analysis: ";
    // getline (cin, testString);
    string test_2 = "quo usque tandem abutere, catilina, patientia nostra?";
    getIPA(test_2);
    getVerbEndings();
    return 0;
}