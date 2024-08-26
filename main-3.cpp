#include <iostream>
#include <vector>
#include <limits>
#include "bloomfilter.cpp"
#include "shellsort.cpp"

bool loggedIn = false;
BloomFilter bloomFilter(100, 3);

void openMarket() {
    // Ask the user if they want to buy or post an item
    std::cout << "Would you like to buy or post an item for sale? (buy/post): ";
    std::string userBuySell;
    std::cin >> userBuySell;

    //populate marketplace
    std::vector<Item> itemDatas = {Item("bike",10,20,"misc"),Item("kite",5,10,"misc"),Item("shoes", 30, 25,"apparell"),Item("hat", 15, 18,"apparell"),Item("watch", 50, 30,"accessory")};
    ShellSort shell(itemDatas);

    if (userBuySell == "buy" || userBuySell == "Buy") {
        std::cout << "Great! What criteria would you like to sort the items by?" <<std::endl; 
        std::string sortCriteria;
        while(std::cin >> sortCriteria){
            if(sortCriteria != "1" && sortCriteria != "2" && sortCriteria != "3"){
                std::cerr << "Invalid input, try again. Usage: " <<std::endl;
                std::cout << "\"1\" for price " <<std::endl<<std::endl;
                std::cout << "\"2\" for category " <<std::endl;
                std::cout << "\"3\" for distance from seller " <<std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                break;
            }
        }

        std::cout << "How would you like that sorted? Press \"1\" to sort Low to High or \"2\" for High to Low: "<<std::endl;
        std::string sortOrder;
        while(std::cin >> sortOrder){
            if(sortOrder != "1" && sortOrder != "2"){
                std::cerr << "Invalid input, try again. Usage: " <<std::endl;
                std::cout << "\"1\" for ascending " <<std::endl<<std::endl;
                std::cout << "\"2\" for descending " <<std::endl;
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            } else {
                break;
            }
        }

        if (sortCriteria == "1") {
            if(sortOrder == "1") {
                shell.sortPriceAscend();
            } else if(sortOrder == "2") {
                shell.sortPriceDescend();
            }
        } else if (sortCriteria == "2") {
            // Shell sort for category
            if(sortOrder == "1") {
                shell.sortCategoryAscend();
            } else if(sortOrder == "2") {
                shell.sortCategoryDescend();
            }
        } else if(sortCriteria == "3") {
            if(sortOrder == "1") {
                shell.sortDistanceAscend();
            } else if(sortOrder == "2") {
                shell.sortDistanceDescend();
            }
        }
    } else if (userBuySell == "post" || userBuySell == "Post") {
        std::cout << "Sure! Let's start by asking some questions about the item you want to post...\n";
        std::cout << "What is the name of the item?: ";
        std::string newItemName;
        std::cin >> newItemName;

        std::cout << "Enter your selling price: ";
        float sellingPrice;
        std::cin >> sellingPrice;

        // Insert item using treap

        std::cout << "Thank you for posting the item!" << std::endl;
    }

    std::cout << "Would you like to stay logged in? (yes/no): ";
    std::string stayLoggedIn;
    std::cin >> stayLoggedIn;

    if (stayLoggedIn == "no") {
        loggedIn = false;
    }
}

int main() {
    std::cout << "Welcome to our marketplace simulation UI!\n";

    // Log in / Create an account
    std::cout << "Do you have an account? (yes/no): ";
    std::string userAccount;
    std::cin >> userAccount;

    if (userAccount == "yes") {
        loggedIn = true;

        std::cout << "Please enter username: " << std::endl;
        std::string username;
        std::cin >> username;

        if (bloomFilter.checkUsername(username)) {
            loggedIn = true;
        }
    } else {
        std::cout << "Please make an account" << std::endl;
        bool usernameTaken = true;
        std::string username;
        do {
            std::cout << "Enter a username: ";
            std::cin >> username;

            if (bloomFilter.mightContain(username)) {
                std::cout << "Username already exists. Please choose another username. " << std::endl;
            } else {
                usernameTaken = false;
            }
        } while (usernameTaken);
      
        std::cout << "Enter a password: ";
        std::string userPassword;
        std::cin >> userPassword;
        bloomFilter.add(username);
        
        loggedIn = true;
    }
    
    while (loggedIn) {
        openMarket();
    }
    
    return 0;
}
