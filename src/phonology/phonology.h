#include <iostream>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <cstddef>
#include <vector>
#include <iomanip>
#include <map>
using namespace std;

// Syllabic decomposition rules used: 
// http://www.wheelockslatin.com/chapters/introduction/introduction_syllables.html

bool isDiphtong(string str) {
    vector<string> diphtongs;
    string diphtong;
    ifstream file1("phonology/IPA_files/IPA_latin_diphtongs.txt");
    while (getline (file1, diphtong)) {
        diphtongs.push_back(diphtong);
    }
    file1.close();
    for (int i = 0; i < diphtongs.size(); i++) {
        if (diphtongs.at(i) == str) {
            return true;
        }
    }
    return false;
}

bool isStop(string str) {
    vector<string> stopLetters;
    string stopLetter;
    ifstream file2("phonology/IPA_files/IPA_latin_stop_letters.txt");
    while (getline (file2, stopLetter)) {
        stopLetters.push_back(stopLetter);
    }
    file2.close();
    for (int i = 0; i < stopLetters.size(); i++) {
        if (stopLetters.at(i) == str) {
            return true;
        }
    }
    return false;
}

bool isLiquid(string str) {
    vector<string> liquidLetters;
    string liquidLetter;
    ifstream file3("phonology/IPA_files/IPA_latin_liquid_letters.txt");
    while (getline (file3, liquidLetter)) {
        liquidLetters.push_back(liquidLetter);
    }
    file3.close();
    for (int i = 0; i < liquidLetters.size(); i++) {
        if (liquidLetters.at(i) == str) {
            return true;
        }
    }
    return false;
}

bool isAspirate(string str) {
    vector<string> aspirates;
    string aspirate;
    ifstream file4("phonology/IPA_files/IPA_latin_aspirates.txt");
    while (getline (file4, aspirate)) {
        aspirates.push_back(aspirate);
    }
    file4.close();
    for (int i = 0; i < aspirates.size(); i++) {
        if (aspirates.at(i) == str) {
            return true;
        }
    }
    return false;
}

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

    Word x = <Phone1, Phone2, ..., Phone n> 
    Phone x = its own properties + left neighbourPhone + right neighbourPhone to allow quick peeking at neighbours.                            

*/

// Accompanies a phone to the left and right in all words wiht more than one phone.

class neighbourPhone {
    public:
        string val;
        map<string, bool> features;
        bool isVowel;
};

// The smallest unit used for this phonology, an IPA char.

class Phone {
    public:
        string val;
        map<string, bool> features;
        neighbourPhone left;
        neighbourPhone right;
        bool isVowel;
};

// A syllable is a vector of phones with an Onset, Nucleus and Coda.
// O-N-C (Nucleus is a vowel, Onset and Coda are optional groups of consonants).

class Syllable {
    public:
        vector<Phone> onset;
        vector<Phone> nucleus;
        vector<Phone> coda;
};

// A word is a vector of syllables.

class Word {
    public:
        vector<Phone> phones;
        vector<Syllable> syllables;
};

class PhoneticCorpus {
    public:
        vector<Word> words;
        void loadWords(vector<Phone>);
};

class Alphabet {
    public:
        Alphabet();
        void show();
        map<string, string> pairs;
        vector<string> vowels;
};

// @description: Helper function to print items in a map. 
void printPhoneFeatureMap(map<string, bool> m, Phone phone) {
    cout << phone.val << endl;
    cout << "---------------" << endl;
    std::cout << "isDiphtong : " << m["isDiphtong"] << '\n';
    std::cout << "isStop : " << m["isStop"] << '\n';
    std::cout << "isLiquid : " << m["isLiquid"] << '\n';
    std::cout << "isAspirate : " << m["isAspirate"] << '\n';
    cout << endl;
}

/*
* @description: adds a vector of whitespace/comma/full stop delimited 'Word' to the Phonetic Corpus
*               abstraction. Each 'Word' is a vector of 'Phones'
* @input: NA.
* @output: updated PhoneticCorpus.
*/
void PhoneticCorpus::loadWords(vector<Phone> phones) {
    int i = 0;
    int size = phones.size();
    while (i < (phones.size() - 1)) {
        Word currentWord;
        while (phones.at(i).val != "NULL") {
            if (i == (phones.size() - 1)) {
                break;
            }
            Phone currentPhone = phones.at(i);
            if (currentPhone.val == "NULL") {
                i++;
            }
            if (currentPhone.val != " " || currentPhone.val != "." || currentPhone.val != ",") {
                currentWord.phones.push_back(currentPhone);
                i++;
            }
        }
        words.push_back(currentWord);
        currentWord.phones.clear();
        if (i == (phones.size() - 1)) {
            break;
        }
        i++;
    }
}

Alphabet::Alphabet() {
    string line;
    ifstream file("phonology/IPA_files/IPA_latin_equivalencies.txt");
    while (getline (file, line)) {
        if (line.at(0) != '/') {
            int pos = line.find_first_of(':');
            std::string ipaString = line.substr(pos+1),
            latinString = line.substr(0, pos);
            // Insert into map iff tuple not already present.
            if (!pairs.insert( std::make_pair(latinString, ipaString) ).second ) {
                pairs.insert(std::pair<string, string>(latinString, ipaString));
            }
        }
    }
    file.close();

    string currVowel;
    ifstream fileVowels("phonology/IPA_files/IPA_vowels.txt");
    while (getline (fileVowels, currVowel)) {
        vowels.push_back(currVowel);
    }
    fileVowels.close();
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
* @input: vector of Phones without their features or neighbouring phones.
* @output: vec<Phone> of Phones with all L/R contexts applied (but no grammar rule flags yet).
*/
vector<Phone> putIPAContext(vector<Phone> rawPhones) {
    for (int i = 0; i < rawPhones.size(); i++) {
        // Fencepost coditions where leftmost Phone cannot have a left phone, rightmost Phone cannot have a right phone.
        if (i == 0) {
            rawPhones.at(i).left.val = "NULL";
            rawPhones.at(i).right.val = rawPhones.at(i + 1).val, rawPhones.at(i).right.isVowel = rawPhones.at(i + 1).isVowel;
        }
        if (i != 0 && i != rawPhones.size() - 1) {

            string leftPhone = rawPhones.at(i - 1).val;
            string rightPhone = rawPhones.at(i + 1).val;
            bool leftVowel = rawPhones.at(i - 1).isVowel;
            bool rightVowel = rawPhones.at(i + 1).isVowel;

            if (leftPhone == " " || leftPhone == "," || leftPhone == ".") {
                leftPhone = "NULL";
            }
            if (rightPhone == " " || rightPhone == "," || rightPhone == ".") {
                rightPhone = "NULL";
            }
            // Set leftPhone, rightPhone string val and bool value.
            rawPhones.at(i).left.val = leftPhone, rawPhones.at(i).left.isVowel = leftVowel;
            rawPhones.at(i).right.val = rightPhone, rawPhones.at(i).right.isVowel = rightVowel;
        }
        if (i == rawPhones.size() - 1) {
            // Set leftPhone string val and bool value.
            rawPhones.at(i).left.val = rawPhones.at(i - 1).val, rawPhones.at(i).left.isVowel = rawPhones.at(i - 1).isVowel;
            rawPhones.at(i).right.val = "NULL";
        }
    }
    return rawPhones;
}

/*
* @input: vec<Phone> enriched phone objects.
* @output: vec<Word> words with syllable groups.
*/
vector<Word> getSyllables(vector<Phone> phones) {
    for (int i = 0; i < phones.size(); i++) {
        bool diphtong = isDiphtong(phones.at(i).val);
        bool stop = isStop(phones.at(i).val);
        bool liquid = isLiquid(phones.at(i).val);
        bool aspirate = isAspirate(phones.at(i).val);

        phones.at(i).features.insert(std::pair<string, bool>("isDiphtong", diphtong));
        phones.at(i).features.insert(std::pair<string, bool>("isStop", stop));
        phones.at(i).features.insert(std::pair<string, bool>("isLiquid", liquid));
        phones.at(i).features.insert(std::pair<string, bool>("isAspirate", aspirate));
    }

    PhoneticCorpus corp;
    corp.loadWords(phones);

    cout << "TEST: Word objects being created properly" << endl;
    for (int i = 0; i < corp.words.size(); i++) {
        Word currentWord = corp.words.at(i);
        for (int j = 0; j < currentWord.phones.size(); j++) {
            printPhoneFeatureMap(currentWord.phones.at(j).features, currentWord.phones.at(j));
        }
    }
    cout << endl;
    return corp.words;
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
    vector<string> v = IPA_map.vowels;
    // Since the maxium num of latin chars = to 1 IPA char is 2 ...
    int i = 0;
    while (i < str.size()) {
        // If curr char and next char map to a latin IPA, e.g. qu -> kʷ.
        char currentChar = str.at(i);
        string nextTwo = str.substr(i, 2);
        itr = IPA_map.pairs.find(nextTwo);
        if (itr != IPA_map.pairs.end()) {
            Phone doublePhone;
            string currDouble = IPA_map.pairs.at(nextTwo);
            doublePhone.isVowel = false;
            // Check if the doublPhone is in the vowel list.
            for (int i = 0; i < v.size(); i++) {
                if (v.at(i) == currDouble) {
                    doublePhone.isVowel = true;
                }
            }
            doublePhone.val = currDouble;
            cout << currDouble;
            result_no_context.push_back(doublePhone);
            i+= 2;
        }
        else {
            Phone phone;
            string currentString;
            currentString.push_back(currentChar);
            string curr = IPA_map.pairs.at(currentString);
            phone.isVowel = false;
            for (int i = 0; i < v.size(); i++) {
                if (v.at(i) == curr) {
                    phone.isVowel = true;
                }
            }
            phone.val = curr;
            result_no_context.push_back(phone);
            cout << curr;
            i++;
        }
    }
    cout << endl;
    vector<Phone> result = putIPAContext(result_no_context);
    getSyllables(result);
    return result;
}
