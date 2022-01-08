/// @brief Assignment 8
/// Priority Queue main.cpp

#include <bits/stdc++.h>
#include "priorityQ.hpp"

///---------------------------------------
/// main entry point
///---------------------------------------
int main()
{
    //get filename, and open
    std::ifstream infile;
    bool valid_file = false;
    std::string str;

    while (!valid_file) {

        std::cout << "Enter filename: ";
        std::cin >> str;
        infile.open(str);
        
        if (infile.is_open()) { // check if valid file
            valid_file = true; // awesome
        }else {
            infile.clear();
        }
            
    }

    priorityQ<int> q(10);

    // get k value
    std::stringstream ss;
    std::getline(infile, str, '\n');
    ss << str;
    int k;
    ss >> k;

    std::getline(infile, str); // skip blank line

    //list of numbers
    int original = 0;
    int num;
    int highest;
    while (!infile.eof()) {

        if (infile.eof()) {
            break;
        }

        // build PQ up to n == k
        if (q.getSize() < k) {

            ss.clear();
            std::getline(infile, str, '\n');

            // avoids empty lines
            if (!str.empty()) {
                ss << str;
                ss >> num;

                q.insert(num);
                if (q.getSize() == k - 1) {
                    std::cout << "Initial " << k << "-th largest number: " 
                            << q.getHighestPriority() << '\n';
                    highest = q.getHighestPriority();
                }
            }


        }else {

        // find new k-th largest
            ss.clear();
            std::getline(infile, str, '\n');
            if (!str.empty()) {
                ss << str;
                ss >> num;

                // insert (n + 1)th element
                q.insert(num);

                // go back to n
                q.deleteHighestPriority();

                // get k'th largest
                if (q.getHighestPriority() != highest) {
                    std::cout << "New " << k << "-th largest number: " 
                            << q.getHighestPriority() << '\n';
                    highest = q.getHighestPriority();
                }
            }  

        }
    }

    std::cout << "Final " << k << "-th largest number: " << highest << std::endl;
    
    return 0;
}
