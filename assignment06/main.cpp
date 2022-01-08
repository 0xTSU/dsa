/// @brief Assignment 6
/// Store prices of items in a hashmap

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <unordered_map>

///---------------------------------------
/// struct: MenuItem
/// represents a dessert item in a binder
///---------------------------------------
struct MenuItem {

    std::string name;
    int price;

    MenuItem(std::string x, int y = 0) {

        name = x;
        price = y;

    }

};

///---------------------------------------
/// func: sortMenu()
/// @param vector completed menu
/// @return menu sorted by price
///---------------------------------------
std::vector<MenuItem> sortMenu(std::vector<MenuItem> menu) {

    for (int i = 0; i < menu.size(); i++) {
        auto smallest = menu[i];
        auto smallestind = i;

        for (int u = i; u < menu.size(); u++) {
            if (menu[u].price < smallest.price) {
                smallest = menu[u];
                smallestind = u;
            }
        }

        auto temp = menu[i];
        menu[i] = smallest;
        menu[smallestind] = temp;
    }

    return menu;
}

///---------------------------------------
/// func: capsSpam()
/// @param string
/// @return string in all capital letters
///---------------------------------------
void capsSpam(std::string& binder_title) {

    for (int i = 0; i < binder_title.length(); i++) {
        if (binder_title[i] >= 'a' && binder_title[i] <= 'z') {
            binder_title[i] = toupper(binder_title[i]);
        }
    }

}

///---------------------------------------
/// func: fixStr()
/// @param string
/// @return string with no spaces or extra characters like '_'
///---------------------------------------
void fixStr(std::string& string) {

    for (int i = 0; i < string.length(); i++) {
        if (!(string[i] >= 'a' && string[i] <= 'z')) {
            string.erase(i, 1);
        }
    }

}

int main()
{
    // get name of file
    // then open when correct filename is inputted
    std::ifstream infile;
    bool valid_file = false;
    std::string recipes_filename;
    while (!valid_file) {

        std::cout << "Enter binder name: ";
        std::cin >> recipes_filename;
        infile.open(recipes_filename);
        
        if (infile.is_open()) { // check if valid file
            valid_file = true; // awesome
        }else {
            infile.clear();
        }
            
    }
    std::cout << '\n';
	std::vector<std::unordered_map<std::string,int>> binders;
	std::vector<std::string> binder_titles;
    std::vector<std::vector<MenuItem>> desserts;
    
    std::stringstream ss; // getline and stringstream is how we advance lines
    std::string str;
    int num_of_binders, m, n ,b;

    std::getline(infile, str, '\n');
    ss << str;
    ss >> num_of_binders;
    ss.clear();

    for (int i = 0; i < num_of_binders; i++) {
        
        // get name of binder
        std::getline(infile, str, '\n');
        capsSpam(str);
        binder_titles.push_back(str);
        binders.push_back(std::unordered_map<std::string,int>());
        desserts.push_back(std::vector<MenuItem>()); // desserts[i].push_back(MenuItem(dessertname, price));

        // get m, n ,b
        std::getline(infile, str, '\n');
        ss << str;
        ss >> m; // entries for unordered map (ingredient, cost)
        ss >> n; // number of desserts in binder
        ss >> b; // budget

        // fill binder with ingredients and their prices
        auto binder = binders[i];
        for (int u = 0; u < m; u++) {
            ss.clear();
            std::getline(infile, str, '\n');
            ss << str; 
            std::string ingredient;
            int price;
            
            ss >> ingredient;
            ss >> price;

            fixStr(ingredient);
            binder[ingredient] = price;
        }

        // go through desserts in binder
        for (int u = 0; u < n; u++) {
            int ingredients;
            std::string part;
            int amt = 0;
            int total = 0;

            std::getline(infile, str, '\n');
            desserts[i].push_back(MenuItem(str)); // get dessert name

            std::getline(infile, str, '\n');
            ss.clear();
            ss << str;
            ss >> ingredients; // get # of ingredients req

            // get total price 
            for (int v = 0; v < ingredients; v++) {

                std::getline(infile, str, '\n');
                ss.clear();
                ss << str;
                ss >> part;
                ss >> amt;
                fixStr(part);
                total +=  binder[part] * amt;
                //std:: cout << total <<  " " << part << " " << amt << '\n';
            }
            // update price
            desserts[i][u].price = total;
        }

        // output everything
        std::cout << binder_titles[i] << '\n';
        std::cout << "-------------------------------------\n";
        desserts[i] = sortMenu(desserts[i]);
        bool posted = false;
        for (auto dessert : desserts[i]) {
            if (dessert.price < b) {
                std::cout << dessert.name << '\n';
                b -= dessert.price;
                posted = true;
            }
        }

        if (!posted) {
            std::cout << "No cakes can be made\n";

        }

        std::cout << '\n';
        ss.clear();

    }

    infile.close();
	return 0;
}
