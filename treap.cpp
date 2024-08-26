#include <iostream>
#include <cstdlib> 

struct Item {
    std::string name;
    float price;
    float distance; 
    std::string productType;

    Item(std::string name, float price, float distance,std::string productType) : name(name), price(price), distance(distance), productType(productType){}
};

template<typename T>
class TreapNode {
public:
    T data;
    int priority;
    TreapNode* left;
    TreapNode* right;

    TreapNode(T data) : data(data), priority(rand()), left(nullptr), right(nullptr) {}
};

template<typename T>
class Treap {
private:
    TreapNode<T>* root;

    // Helper functions
    void split(TreapNode<T>* current, std::string key, TreapNode<T>*& left, TreapNode<T>*& right) {
        if (current == nullptr) {
            left = nullptr;
            right = nullptr;
        } else if (key < current->data.name) {
            split(current->left, key, left, current->left);
            right = current;
        } else {
            split(current->right, key, current->right, right);
            left = current;
        }
    }

    TreapNode<T>* merge(TreapNode<T>* left, TreapNode<T>* right) {
        if (left == nullptr) return right;
        if (right == nullptr) return left;

        if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            return left;
        } else {
            right->left = merge(left, right->left);
            return right;
        }
    }

    void insert(TreapNode<T>*& current, TreapNode<T>* newNode) {
        if (current == nullptr) {
            current = newNode;
        } else if (newNode->priority > current->priority) {
            split(current, newNode->data.name, newNode->left, newNode->right);
            current = newNode;
        } else {
            insert(newNode->data.name < current->data.name ? current->left : current->right, newNode);
        }
    }

    void remove(TreapNode<T>*& current, std::string key) {
        if (current == nullptr) return;

        if (current->data.name == key) {
            TreapNode<T>* temp = current;
            current = merge(current->left, current->right);
            delete temp;
        } else {
            remove(key < current->data.name ? current->left : current->right, key);
        }
    }

    void inorderTraversal(TreapNode<T>* current) {
        if (current != nullptr) {
            inorderTraversal(current->left);
            std::cout << "Item: " << current->data.name << ", Price: " << current->data.price << ", Distance from seller: "<<current->data.distance << std::endl;
            inorderTraversal(current->right);
        }
    }

public:
    Treap() : root(nullptr) {}

    void insert(Item data) {
        TreapNode<T>* newNode = new TreapNode<T>(data);
        insert(root, newNode);
    }

    void remove(std::string key) {
        remove(root, key);
    }

    void inorderTraversal() {
        inorderTraversal(root);
    }
};


/*
 int main() {
     Treap<Item> treap;

     // Insert some items
     treap.insert(Item("Laptop", 1000.00,50));
     treap.insert(Item("Charger", 20.50,60));

     std::cout << "Items in the marketplace:" << std::endl;
     treap.inorderTraversal();

     treap.remove("Laptop");

     std::cout << "Updated items in marketplace:" << std::endl;
     treap.inorderTraversal();

     return 0;
 }
 */

