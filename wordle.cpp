#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
int numDashes(string str, int index);
void wordsPsbl(const set<string>& dict, set<string>& words, string grn, string ylw, int index);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> posWords;
    wordsPsbl(dict, posWords, in, floating, 0);
    return posWords;
}

// Define any helper functions here

// finds the number of dashes
int numDashes(string str, int index){ 
    int count=0;
    for(size_t i=index; i<str.length(); i++){
        if(str[i]=='-'){
            count++;
        }
    }
    return count;
}
// finds all possible word combos from the green and yellow letters given
void wordsPsbl(const set<string>& dict, set<string>& words, string grn, string ylw, int index){
    size_t dashNum = numDashes(grn, index);

// if there are more yellow letters than dashes, no words are possible
    if(ylw.length()>dashNum)
    return;

// if the word is completely filled out and part of the dictionary, add it to the words set
    if(dashNum==0){
        if(dict.find(grn)!=dict.end() && ylw.length()==0){
            words.insert(grn);
        }
        return;
    }
/* if the correct letter hasn't been found -> it's a dash, find all the words made using the yellow, "floating", letters recursively 
*/ 
    if(grn[index]=='-'){
        for(size_t i=0; i<ylw.length(); i++){
            char l=ylw[i];
            string newG=grn;
            string newY=ylw;
            newG[index]=l;
            newY.erase(i,1);
            wordsPsbl(dict, words, newG, newY, index+1);
        }
        if(ylw.length()< dashNum){
            for(char letter='a'; letter<='z'; letter++){
                string newG=grn;
                newG[index]=letter;
                wordsPsbl(dict, words, newG, ylw, index+1);
            }
        }
    }
    //if all letters are spots are filled in
    else{
        wordsPsbl(dict, words, grn, ylw, index+1);
    }
}