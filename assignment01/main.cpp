/// @brief Assignment 1 is a review of previous course's content
/// The task is to implement the class provided to create a 
/// functional doubly linked list, and code a selection sort algorithm.

#include "linkedlist.h"
#include <fstream>
#include <iostream>
#include <iomanip>

///---------------------------------------
/// int main(), main entry point
/// @param int cli argument count
/// @param char* text file to sort
///---------------------------------------
int main(int argc, char* argv[]) 
{
	LL<int> list;
	std::ifstream inFile;
	LL<int>::iterator nil = nullptr;
	int status = 0;

	// check if command line input is correct
	if (argc != 2 || !inFile) {
		status = 1;
	}else {
		// read ints from file
		inFile.open(argv[1]);
		while (!inFile.eof()) {

			int x;
			inFile >> x;
			// skip eof as its read twice
			if (inFile.eof()) {
				break;
			}

			list.tailInsert(x);

		}

		// selection sort
		// borrowed from my cs202 assignment w/ kevin mess at csn
		// pseudocode from wikipedia, and harvard CS50 video
		for (auto begin = list.begin(); begin != nil; begin++) {
			// get start of unsorted list
			auto smallest = begin;

			for (auto next = begin; next != nil; next++) {
				// find node with smallest value
				if (*next < *smallest) {
					smallest = next;
					
				}

			}
			// if the smallest # is in the beginning of iteration
			// it will be stuck in a loop
			// so skip it.
			if (smallest == begin) {
				continue;
			}
			// put smallest value at the beginning of the unsorted list
			list.swapNodes(begin, smallest);
			
			begin = list.begin();
		}

		auto word = list.begin();
		while (word != nil) {
			std::cout << *word << '\n';
			word++;
		}
	}

	return status;
}
