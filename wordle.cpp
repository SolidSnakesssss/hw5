#ifndef RECCHECK
#include <iostream>
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;

// Add prototypes of helper functions here
void allWords(size_t remainingSize, std::set<std::string>& possibleCombos, std::string word = "");

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    size_t targetSize = in.length();
    set<string> possibleCombos;
		set<string> realWords;

    allWords(targetSize, possibleCombos);

    set<string> result;

    for(set<std::string>::iterator it = possibleCombos.begin(); it != possibleCombos.end(); ++it){
        set<char> allLetters;
        string current = *it;
        bool requiredLetters = true, possibleLetters = true;

				if(dict.find(current) == dict.end()) continue;

        for(size_t i = 0; i < targetSize; i++){
            allLetters.insert(current[i]);

            if(in[i] == '-') continue;
            else{
                if(current[i] != in[i]){
                    requiredLetters = false;
                    break;
                }
            }
        }

        if(!requiredLetters) continue;

        for(size_t i = 0; i < floating.size(); i++){
            if(allLetters.find(floating[i]) == allLetters.end()){
                possibleLetters = false;
                break;
            }
        }

        if(possibleLetters){
            result.insert(current);
        }
    }

    return result;
}

// Define any helper functions here
void allWords(size_t remainingSize, std::set<std::string>& possibleCombos, std::string word){
    if(remainingSize == 0){
        possibleCombos.insert(word);
        return;
    }

    for(char i = 'a'; i <= 'z'; i++){
        allWords(remainingSize - 1, possibleCombos, word + i);
    }
}