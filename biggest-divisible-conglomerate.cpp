
#include <vector>  // use vectors
#include <iostream> // enable cin, cout
#include <string> // use strings
#include <algorithm>  // to use sort : source: https://www.digitalocean.com/community/tutorials/sort-in-c-plus-plus 
#include "bdc.h"  // include bdc header

using namespace std;

/*
 * Dynamic Programming solution to find the biggest divisible conglomerate
 * Previous recursive approach time complexity: O(2^n) worst case
 * Dynamic Programming approach time complexity: O(n^2)
 */

vector<int> biggest_divisible_conglomerate(vector<int> input){
    if (input.size() <= 1) { // return input for vectors less than or equal to 1
        return input;
    }

    sort(input.begin(), input.end()); // sort input in ascending order, needed for DP strategy

    vector<vector<int>> answers(input.size()); // create vector that contains vector<ints> called answers to hold solutions

    // Initialize answers: each element starts as its own subset
    for (size_t i = 0; i < input.size(); i++) {
        answers[i] = { input[i] };
    }

    // Dynamic Programming table-building
    for (size_t i = 0; i < input.size(); i++) {
        int cur_element = input[i]; // create current element variable to hold cur variable. 
        for (size_t j = i + 1; j < input.size(); j++) {
            //check if element at j in input is divisible by cur_element
            if (input[j] % cur_element == 0 && answers[i].size() >= answers[j].size()) { 
                // Start a new subset at j with the longer one from i
                answers[j] = { input[j] };
                // add all elements from the answers at i spot into the answers at j spot
                for (size_t k = 0; k < answers[i].size(); k++) {
                    answers[j].push_back(answers[i][k]);
                }
            }
        }
    }

    // Find the longest answer
    size_t max_idx = 0; //set max_idx to zero as place holder
    for (size_t i = 1; i < answers.size(); ++i) {
        if (answers[i].size() > answers[max_idx].size()) {
            max_idx = i;
        }
    }

    return answers[max_idx]; // return teh vector in answers that is the longest
}

string vec_to_string(vector<int> v){ // function for vector to string
    if (v.empty()) return "[]"; // if v is empty retun empty set

    string s = "["; // added open bracker
    for (size_t i = 0; i < v.size() - 1; i++) { // loop through v

        s += to_string(v[i]) + ", "; // add each element to the string followed by a comma and a space, do not include last element

    }
    s += to_string(v.back()) + "]"; // add last element followed by close bracket
    return s; // return string
}