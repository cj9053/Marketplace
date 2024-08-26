#include <iostream>
#include <vector>
#include <string>
#include <map>

int hashFunction(const std::string& str) {
    int hash = 0;
    for (char ch : str) {
        hash += static_cast<int>(ch);
    }
    return hash;
}

class BloomFilter {
private:
    std::vector<bool> filter;
    int size;
    int numHashes;
    std::vector<std::string> usernames;
    std::map<std::string, std::string> credentials;

public:
    BloomFilter(int size, int numHashes) : size(size), numHashes(numHashes), filter(size, false) {}

    void add(const std::string& username, const std::string& password) {
        for (int i = 0; i < numHashes; i++) {
            int hash = (hashFunction(username) + i) % size;
            filter[hash] = true;
        }
        credentials[username] = password;
    }

    bool mightContain(const std::string& str) {
        for (int i = 0; i < numHashes; i++) {
            int hash = (hashFunction(str) + i) % size;
            if (!filter[hash]) {
                return false;
            }
        }
        return true;
    }

    bool checkUsername(const std::string& username) {
        if (username == "q") {
            
        }
        if (mightContain(username)) {
            bool found = false;
            for (auto itr = credentials.begin(); itr != credentials.end(); itr++) {
                if (itr->first == username) {
                    return true;
                }
            }
            if (!found) {
                return false;
            }
        }
        return false;    
    }

    bool checkPassword(const std::string& username, const std::string& password) {
        if (credentials[username] == password) {
            return true;
        } else {
            return false;
        }
    }
};

int main() {
    BloomFilter filter(100, 3); // Example size and number of hash functions

    // Add existing usernames to the filter
    filter.add("username1", "1");
    filter.add("username2", "2");

    // Check if a new username is possibly taken
    std::cout << "Is username3 taken? " << (filter.mightContain("username3") ? "true" : "false") << std::endl;
    std::cout << "Is username1 taken? " << (filter.mightContain("username1") ? "true" : "false") << std::endl;

    std::string enteredUsername = "username1";
    if (filter.checkUsername(enteredUsername)) {
        std::cout << "Welcome " << enteredUsername << std::endl;
    } else {
        std::cout << "Account not found please try again" << std::endl;
    }

    return 0;
}

