#include <iostream>
#include <vector>
#include "tokenization/tokenize.h"
using namespace std;

int main() {
    cout << " Latin NLP pos tagger and phonetic transcription ..." << endl;
    string test = "Quo usque tandem abutere, Catilina, patientia nostra? quam diu etiam furor iste tuus nos eludet? quem ad finem sese effrenata iactabit audacia?";
    text catilina_ptI = tokenizeText(test);
    catilina_ptI.printSentences();
    catilina_ptI.printTokens();
    return 0;
}