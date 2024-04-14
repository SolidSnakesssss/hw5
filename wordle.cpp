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
void generatePermutations(const std::string& in, set<string>& permutations, string temp, int start, int end);
void generateWords(const std::set<std::string>& dict, set<string>& actualWords, string current, int start, int end);
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    set<string> permutations;
    set<string> actualWords;
    size_t wordLength = in.length(), floatTemp = 0;
    string temp = in;

    for(size_t i = 0; i < wordLength; i++){
        if(floatTemp == floating.length()){
            break;
        }

        else if(temp[i] == '-'){
            temp[i] = floating[floatTemp++];
        }
    }

    generatePermutations(in, permutations, temp, 0, wordLength);

    for(set<string>::iterator it = permutations.begin(); it != permutations.end(); ++it){
        generateWords(dict, actualWords, *it, 0, wordLength);
    }

    return actualWords;
}

void generatePermutations(const std::string& in, set<string>& permutations, string temp, int start, int end){
   if(start == end){
        for(size_t i = 0; i < in.length(); i++){
            if(in[i] != '-' && temp[i] != in[i]) return;
        }
        permutations.insert(temp);
        return;
    }

    for(int i = start; i < end; i++){
        swap(temp[start], temp[i]);

        generatePermutations(in, permutations, temp, start + 1, end);

        //swap(temp[start], temp[i]);
    }
}

void generateWords(const std::set<std::string>& dict, set<string>& actualWords, string current, int start, int end){
    if (start == end) {
        if (dict.find(current) != dict.end()) {
            actualWords.insert(current);
        }
        return;
    }

    string temp = current;

    if (temp[start] == '-') {
        for (char i = 'a'; i <= 'z'; i++) {
            temp[start] = i; // Replace dash with current character
            generateWords(dict, actualWords, temp, start + 1, end); // Pass modified temp to the recursive call
        }
    } 
    
    else {
        generateWords(dict, actualWords, temp, start + 1, end);
    }
}