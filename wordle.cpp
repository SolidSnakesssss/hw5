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
void generateWords(const string& in, string floating, const set<string>& dict, set<string>& actualWords, size_t blankCount, string current = "");
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    set<string> actualWords;
    size_t blankCount = 0;

    for(size_t i = 0; i < in.size(); i++){
        if(in[i] == '-'){
            blankCount++;
        }
    }

    generateWords(in, floating, dict, actualWords, blankCount);

    return actualWords;
}

void generateWords(const string& in, string floating, const set<string>& dict, set<string>& actualWords, size_t blankCount, string current){
    //Are there less blank spaces than there are floating characters
		if(blankCount < floating.size()){
        return;
    }

		//Checks if the current words is of size n
    else if(current.size() == in.size()){
				//Checks if floating is empty and that the word is in the dictionary
        if(dict.find(current) != dict.end() && floating.empty()){
            //Adds the word to actualWords if found
						actualWords.insert(current);
        }
    }

		//Checks if there is a green letter at index[current.size()]
    else if(in[current.size()] != '-'){
        //Adds the green letter to current
				generateWords(in, floating, dict, actualWords, blankCount, current + in[current.size()]);
    }

		//Searches the whole alphabet if spot is blank
    else{
				//Subtract because blank space is being filled
        blankCount--;

				//Loops thorugh the whole alphabet
        for(char i = 'a'; i <= 'z'; i++){
            //Looks to see if the current char is in floating
						size_t floatingIndex = floating.find(i);
            
						//Removes the letter from floating if found. Only removes 1 in case of duplicates
            if(floatingIndex != string::npos){
                floating.erase(floatingIndex, 1);
                generateWords(in, floating, dict, actualWords, blankCount, current + i);
                //Adds the char back for future iterations of the loop
								floating += i;
            }

						//Does nothing to floating if char is not in floating
            else{
                generateWords(in, floating, dict, actualWords, blankCount, current + i);
            }
        }
    }
}
