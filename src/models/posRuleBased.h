#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstddef>
#include <vector>
#include <map>
using namespace std;

    /* TODO
        for sentence in txt
           for token in sentence
               if the verb ending is known (match ending in radix-trie)
                    add the verb tag
    */

void getVerbEndings() {
    string line;
    ifstream file("models/latin_verb_endings.txt");
    while (getline (file, line)) {
        // If the line isn't commented out. 
        if (line.at(0) != '/') {
            // lineVerbs will have all the raw verbal parts in compressed format
            // E.g ... *a,*e,*i,s --> vector<string> lineVerbs = {*a,*e,*i,s}
            vector<string> lineVerbs;
            stringstream s_stream(line);
            // Push all the uncompressed verbal parts after splitting on commas
            while(s_stream.good()) {
                string substr;
                getline(s_stream, substr, ',');
                lineVerbs.push_back(substr);
            }
            /*
            for each item in lineVerbs = {*a,*e,*i,s}:
                if chatAt(0) == '*': getPrefix
                    for all the other items: if charAt(0) != '*':
                        suffix = curr
                        possibleEnding = getPrefix + suffix
            */
            for (int i = 0; i < lineVerbs.size(); i++) {
                if (lineVerbs.at(i).at(0) == '*') {
                    for (int j = (i + 1); j < lineVerbs.size(); j++) {
                        if (lineVerbs.at(j).at(0) != '*') {
                            string temp = lineVerbs.at(i).substr(1,1);
                            string verbalPart =  temp + lineVerbs.at(j);
                            cout << verbalPart << endl;
                        }
                    }
                }
            }
            lineVerbs.clear();
        }
    }
    file.close();
}

// TODO: Noun N, Verb V, Adjective ADJ, Adverb ADV, Preposition P, Conjunction CON, Pronoun PRO, Interjection INT ...