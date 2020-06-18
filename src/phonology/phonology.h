#include <iostream>
#include <string>
#include <sstream>
#include <cstddef>
#include <vector>
#include <map>
using namespace std;

/* Phonology method used ... made it up ;)

e.g. abequito: I ride away - IPA  [aˈbɛ.kᶣɪ.t̪oː]
         abequito
            |            (step 1: map each latin letter to an IPA char)
            |
        aˈbɛkᶣɪt̪oː       (step 2: create word as vec of phones from step 1)
    ________|______
   |        |      | 
   aˈbɛ    kᶣɪ     t̪oː   (step 3: create Syllable objects from Phone objects in abequito 
                                  then update syllable vec in abequito Word obj)

*/

// The smallest unit used for this phonology, an IPA char.
class Phone {
    public:
        string val;
        map<string, bool> features;
        string leftPhone;
        string rightPhone;

};

// A word is a vector of syllables.
class Word {
    public:
        vector<Phone> phones;
        vector<Syllable> syllables;
};

// A syllable is a vector of phones with an Onset, Nucleus and Coda.
// O-N-C (Nucleus is a vowel, Onset and Coda are optional groups of consonants)

class Syllable {
    public:
        vector<Phone> phones;
        vector<Phone> onset;
        vector<Phone> nucleus;
        Phone coda;
};