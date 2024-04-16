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
bool validPermutation(const std::string& in, string current, size_t wordLength, size_t index = 0);
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
        } //Yorp

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
        if(validPermutation(in, temp, in.length())){
            permutations.insert(temp);
        }
        
        return;
    }

    for(int i = start; i < end; i++){
        swap(temp[start], temp[i]);

        generatePermutations(in, permutations, temp, start + 1, end);

        //swap(temp[start], temp[i]);
    }
}

//Helper function for checking if the permutation is valid
bool validPermutation(const std::string& in, string current, size_t wordLength, size_t index){
    
		//Returns true if in chars are in the right place
		if(index == wordLength){
        return true;
    }

		//Returns false if in chars are in the right place
    else if(in[index] != '-' && current[index] != in[index]){
        return false;
    }

    return validPermutation(in, current, wordLength, index + 1);
}

void generateWords(const std::set<std::string>& dict, set<string>& actualWords, string current, int start, int end){
    if (start == end) {
        
				//Best Version but requires find
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