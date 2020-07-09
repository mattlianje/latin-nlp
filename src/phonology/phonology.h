#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
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
   aˈbɛ    kᶣɪ     t̪oː   (step 3: create 'Syllable' objects from Phone objects in abequito 
                                  then update syllable vec in abequito Word obj)

*/

// The smallest unit used for this phonology, an IPA char
class Phone {
    public:
        string val;
        map<string, bool> features;
        string left;
        string right;

};

// A syllable is a vector of phones with an Onset, Nucleus and Coda
// O-N-C (Nucleus is a vowel, Onset and Coda are optional groups of consonants)

class Syllable {
    public:
        vector<Phone> phones;
        vector<Phone> onset;
        vector<Phone> nucleus;
        Phone coda;
};

// A word is a vector of syllables
class Word {
    public:
        vector<Phone> phones;
        vector<Syllable> syllables;
};

class Alphabet {
    public:
        Alphabet();
        void show();
        map<string, string> pairs;
};

Alphabet::Alphabet() {
    string line;
    ifstream file("phonology/IPA_latin_equivalencies.txt");
    while (getline (file, line)) {
        if (line.at(0) != '/') {
            int pos = line.find_first_of(':');
            std::string ipaString = line.substr(pos+1),
            latinString = line.substr(0, pos);
            // Insert into map iff tuple not already present
            if (!pairs.insert( std::make_pair(latinString, ipaString) ).second ) {
                pairs.insert(std::pair<string, string>(latinString, ipaString));
            }
        }
    }
    file.close();
}

void printMap(map<string, string> const &m) {
    for (auto const& pair: m) {
        cout << "{" << pair.first << ": " << pair.second << "}\n";
    }
}

void Alphabet::show() {
    printMap(pairs);
}

/*
* @input: vector of Phones without their features or neighbouring phones
* @output: vec<Phone> of Phones with all L/R contexts applied (but no grammar rule flags yet)
*/
vector<Phone> putIPAContext(vector<Phone> rawPhones) {
    for (int i = 0; i < rawPhones.size(); i++) {
        // Fencepost coditions where leftmost Phone cannot have a left phone, rightmost Phone cannot have a right phone
        if (i == 0) {
            rawPhones.at(i).left = "NULL";
            rawPhones.at(i).right = rawPhones.at(i + 1).val;
        }
        if (i != 0 && i != rawPhones.size() - 1) {
            // TODO: Refactor
            string leftPhone = rawPhones.at(i - 1).val;
            string rightPhone = rawPhones.at(i + 1).val;
            if (leftPhone == " " || leftPhone == "," || leftPhone == ".") {
                leftPhone = "NULL";
            }
            if (rightPhone == " " || rightPhone == "," || rightPhone == ".") {
                rightPhone = "NULL";
            }
            rawPhones.at(i).left = leftPhone;
            rawPhones.at(i).right = rightPhone;
        }
        if (i == rawPhones.size() - 1) {
            rawPhones.at(i).left = rawPhones.at(i - 1).val;
            rawPhones.at(i).right = "NULL";
        }
    }
    return rawPhones;
}

/*
* @input: any string of plain Latin e.g. "abequito".
* @output: vec<Phone> of Phones (IPA strings from map with rules applied), e.g. aˈbɛkᶣɪt̪oː
*/
vector<Phone> getIPA(string str) {
    cout << str << endl;
    vector<Phone> result_no_context;
    map<string, string>::iterator itr;
    Alphabet IPA_map;
    // Since the maxium num of latin chars = to 1 IPA char is 2 ...
    int i = 0;
    while (i < str.size()) {
        // If curr char and next char map to a latin IPA, e.g. qu -> kʷ
        char currentChar = str.at(i);
        string nextTwo = str.substr(i, 2);
        itr = IPA_map.pairs.find(nextTwo);
        if (itr != IPA_map.pairs.end()) {
            Phone doublePhone;
            string currDouble = IPA_map.pairs.at(nextTwo);
            cout << currDouble;
            doublePhone.val = currDouble;
            result_no_context.push_back(doublePhone);
            i+= 2;
        }
        else {
            Phone phone;
            string currentString;
            currentString.push_back(currentChar);
            string curr = IPA_map.pairs.at(currentString);
            phone.val = curr;
            result_no_context.push_back(phone);
            cout << curr;
            i++;
        }
    }
    cout << endl;
    vector<Phone> result = putIPAContext(result_no_context);
    return result;
}
