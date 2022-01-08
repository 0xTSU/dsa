/// @brief Assignment 7
/// Hashmaps

#include "hashMap.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

//------------------------------
// word bank and hashmaps
//------------------------------
std::vector<std::string> words;
std::vector<hashMap<char, bool>> lettersUsed;

bool isAnagram(int index, int wordindex);

int getNextBegin(std::vector<std::vector<std::__cxx11::string>>& anagrams,
                 int current);

void countGroups (std::vector<std::vector<std::__cxx11::string>>& anagrams);

int main()
{
    //------------------------------
    // setup
    //------------------------------
    //get filename, and open
    std::ifstream infile;
    bool valid_file = false;
    std::string str;

    while (!valid_file) {

        std::cout << "Filename: ";
        std::cin >> str;
        infile.open(str);
        
        if (infile.is_open()) { // check if valid file
            valid_file = true; // awesome
        }else {
            infile.clear();
        }
            
    }
    std::cout << '\n';


    while (!infile.eof()) {
        std::getline(infile, str, '\n');
        if (!str.empty())
            words.push_back(str);
    }
    infile.close();
    
    //------------------------------
    // lets roll.
    //------------------------------
    std::vector<std::vector<std::string>> anagrams;
    for (int i = 0; i < words.size(); i++) {
        if (words[i].size() > 0) {

            hashMap<char,bool> hm;
            for (auto letter : words[i]) {
                hm[letter] = true;
            }
            lettersUsed.push_back(hm);
            anagrams.push_back(std::vector<std::string>());
            anagrams[i].push_back(words[i]);
        }     
    }
    for (int u = 0; u < words.size(); u++) {
        std::vector<std::__cxx11::string> vec(anagrams[u]);
        auto word = vec[0];

        int counter = 0;
        for (int i = 0; i < words.size(); i++) {

            if ((i != u) && (anagrams[i].size() == 1) && !anagrams[i][0].empty()) {
                
                auto nextword = anagrams[i][0];
                bool ispermutation = isAnagram(u, i);
                
                if (ispermutation) {
                    counter++;
                    vec.push_back(nextword);
                    anagrams[i][0].clear();
                }
            }
    
        }

        if (counter > 0) {
            anagrams[u] = vec;
            vec.clear();
        }

    }

    countGroups(anagrams);

    return 0;
}

bool isAnagram(int index, int wordindex)
{
    bool valid = true;
    auto protoword = words[index];
    auto hmap = lettersUsed[wordindex];

    for (int i = 0; i < protoword.size(); i++) {
        if (hmap[protoword[i]] == false) {
            valid = false;
            break;
        }
    }
    return valid;
}

void getNextBegin(
                std::vector<std::vector<std::__cxx11::string>>& anagrams,
                std::vector<std::vector<std::__cxx11::string>>::iterator& current,
                std::vector<std::vector<std::__cxx11::string>>::iterator end, 
                int& begin_index)
{
    while (current != end) {
        current++;
        begin_index++;
        if ((*current).size() == 1) {
            break;
        }
    }

}

int getNextBegin(std::vector<std::vector<std::__cxx11::string>>& anagrams,
                 int current)
{
    for (current = current + 1; current < anagrams.size(); current++) {
        if (anagrams[current].size() == 1 && !anagrams[current][0].empty()) {
            break;
        }
    }
    return current;
}

void countGroups(std::vector<std::vector<std::__cxx11::string>>& anagrams) 
{
    
    std::vector<int> sizes;
    for (auto anagram : anagrams) {
        if (!anagram.empty() && !anagram[0].empty()) {
            sizes.push_back(anagram.size());
        }
    }
    std::sort(sizes.begin(), sizes.end());
    std::cout << "Amount of groups: " << sizes.size() << "\n";
    int groups = 1;
    for (int i = sizes.size() - 1; i >= 0; i--) {
        std::cout << "Group " << groups++ << " contains " << sizes[i] <<" words\n";
    }

}
