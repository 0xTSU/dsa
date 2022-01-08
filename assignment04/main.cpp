/// @brief Assignment 4 - Multiplication in Parallel using Threads
/// The task is to implement two numbers together.
#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>

///---------------vectors-----------------
std::vector<short> num1;
std::vector<short> num2;
std::vector<std::vector<short>> partialproduct;
std::vector<std::thread> threadPool;
///---------------------------------------
std::mutex door;
///---------------------------------------

///---------------------------------------
/// func: fillVector()
/// @param std::vector<short>&
/// @param std::string&
/// Fills vector with word && ensures its a valid number
/// @return true if valid number
///---------------------------------------
bool fillVector(std::vector<short>& vec, std::string& number);

///---------------------------------------
/// func: fillThreadPool()
/// @param int index of first number
/// @param int index of second number
/// Queues up threads to hardware concurrent
///---------------------------------------
void fillThreadPool(int num2_index);

///---------------------------------------
/// func: threadFunc()
/// @param int index of first number
/// @param int index of second number
/// pushes vector of results to partialprod vector
/// no better name lol
/// @return carry value
///---------------------------------------
void threadFunc(int num2_index);

///---------------------------------------
/// func: multiply()
/// @param int to multiply
/// @param int to multiply
/// @param int& carry_in
/// @param int& carry_out
/// multiplies the two ints
/// @return carry in value
/// @return carry out value
/// @return resultant to be pushed
///---------------------------------------
int multiply(int x, int y, int& carry_in, int& carry_out);

///---------------------------------------
/// func: addStacks()
/// adds digits in partial products across vectors
/// @return sum in reversed order
///---------------------------------------
std::string addStacks();

///---------------------------------------
/// main-entry point
///---------------------------------------
int main()
{
	std::string num;
	
    // take in a valid num1
    bool valid = false;
    while (!valid) {
        std::cout << "Enter number1: ";
        std::getline(std::cin, num);
        valid = fillVector(num1, num);
    }

    // take in a valid num2
    valid = false;    
    while (!valid) {
        std::cout << "Enter number2: ";
        std::getline(std::cin, num);
        valid = fillVector(num2, num);
    }

    // queue up threads
    auto maxthreads = std::thread::hardware_concurrency();
    for (int i = 0; i < num2.size(); i ++) {

        fillThreadPool(i);

        if (threadPool.size() >= maxthreads) {
            for (auto u = 0; u < threadPool.size(); u++) {
                threadPool[u].join();
            }
            threadPool.clear();
        }

    }

    for (int i = 0; i < threadPool.size(); i++) {
        threadPool[i].join();
    }
    threadPool.clear();
    /*
    short current_index = 0;
    while (current_index < num2.size()) {
        // size should match max threads on hardware
        if (threadPool.size() < std::thread::hardware_concurrency()) {

            fillThreadPool(current_index);
            current_index++;
            
        }else {
            for (auto i = 0; i < threadPool.size(); i++) {
                threadPool[i].join();
            }
            threadPool.clear();

        }

    }
    // join remaining threads
    // should match hw concurrency or less
    if (!threadPool.empty()) {
        for (auto thread = 0; thread < threadPool.size(); thread++) {
            threadPool[thread].join();
        }
        threadPool.clear();
    }
    */
    // get all vectors in partial products to equal size
    // this is to prep for addition
    for (int i = 0; i < partialproduct.size(); i++) {
        while (partialproduct[i].size() < partialproduct[partialproduct.size() - 1].size()){
            partialproduct[i].push_back(0);
        }
    }

    // add stacks
    std::string sum = addStacks();
    std::cout << "the product is: ";
    for (int i = sum.length() - 1; i >= 0; i--) {
        std::cout << sum[i];
    }
    std::cout << '\n';

    num1.clear();
    num2.clear();
    threadPool.clear();
    partialproduct.clear();

	return 0;
}

bool fillVector(std::vector<short>& vec, std::string& number)
{
    bool valid = true;

    // scan string for non number
    for (int i = number.length() - 1; i >= 0 ; i--) {

        if (!(number[i] >= '0' && number[i] <= '9')) {
            // if not a number then return false
            // user will have to enter a valid number
            valid = false;
            number.clear();
        }else {
            vec.push_back(number[i] - '0');
        }

    }

    return valid;
}

void fillThreadPool(int num2_index)
{
    threadPool.push_back(std::thread(threadFunc, num2_index));
}

void threadFunc(int num2_index)
{
    std::vector<short> result;


    // push zeroes for digit placement
    for (int i = 0; i < num2_index; i++) {
        result.push_back(0);
    }

    // maths
    int carry_in = 0;
    int carry_out = 0;
    for (int i = 0; i < num1.size(); i++) {
        // do i really have to document basic multiplication...?
        short part1 = multiply(num1[i], num2[num2_index], carry_in, carry_out);
        short to_push = part1 % 10;
        result.push_back(to_push);
        carry_in = carry_out;
    }
    // because of the control
    // i have to check for any non captured carry values
    if (carry_in > 0)
        result.push_back(carry_in);

    door.lock();
    partialproduct.push_back(result);
    door.unlock();
}

int multiply(int x, int y, int& carry_in, int& carry_out)
{
    // pass by references are used as return values
    // we get result, carry in, and carry out

    // calculate result
    short result = x * y;

    // add the carry value
    result += carry_in;

    // get the 10s digit
    carry_out = (result > 9) ? result / 10 : 0;
    return result;
}


std::string addStacks()
{
    std::string sum = "";

    // similar to multiply() except we add.
    int result = 0;
    int carry = 0;
    for (int i = 0; i < partialproduct[0].size() ; i++) {
        result = 0;
        result += carry;
        carry = 0;
        for (int u = 0; u < partialproduct.size(); u++) {

            result += partialproduct[u][i];
            if (result > 9) {
                carry++;
                result -= 10;
            }

        }

        std::string tostr = std::to_string(result);
        sum.append(tostr);

    }
    if (carry > 0) {
        std::string tostr = std::to_string(carry);
        sum.append(tostr);
    }
    return sum;
}
