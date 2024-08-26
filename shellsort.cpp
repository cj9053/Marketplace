#include "treap.cpp"
#include <iostream>
#include <vector>

class ShellSort {
private:
    std::vector<Item> sortData;
    Treap<Item> treap; 

public:
   // friend class Treap;
   ShellSort(std::vector<Item>& unsortedData);
   void sortDistanceAscend();
   void sortDistanceDescend();


   void sortPriceAscend();
   void sortPriceDescend();
   void display();
   void getData();
        
};
ShellSort::ShellSort(std::vector<Item>& unsortedData) : sortData(unsortedData) {}



void ShellSort::getData(){
   std::vector<TreapNode<Item> >* node;

}

void ShellSort::display() {
    std::cout << "Sorted items:" << std::endl;
    for (const auto& item : sortData) {
        std::cout << "Item: " << item.name << ", Price: " << item.price << ", Distance from seller: " << item.distance << std::endl;
    }
}

//distance sort high to low
void ShellSort::sortDistanceDescend() {
    int n = sortData.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Item temp = sortData[i];
            int j;
            for (int j = i; j >= gap && sortData[j - gap].distance < temp.distance; j -= gap) {
                sortData[j] = sortData[j - gap];
            }
            sortData[j] = temp;
        }
    }
}

void ShellSort::sortDistanceAscend() {
    int n = sortData.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Item temp = sortData[i];
            int j;
            for (j = i; j >= gap && sortData[j - gap].distance > temp.distance; j -= gap) {
                sortData[j] = sortData[j - gap];
            }
            sortData[j] = temp;
        }
    }
}


void ShellSort::sortPriceAscend() {
    int n = sortData.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Item temp = sortData[i];
            int j;
            for (j = i; j >= gap && sortData[j - gap].price > temp.price; j -= gap) {
                sortData[j] = sortData[j - gap];
            }
            sortData[j] = temp;
        }
    }
}

void ShellSort::sortPriceDescend() {
    int n = sortData.size();
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i++) {
            Item temp = sortData[i];
            int j;
            for (j = i; j >= gap && sortData[j - gap].price < temp.price; j -= gap) {
                sortData[j] = sortData[j - gap];
            }
            sortData[j] = temp;
        }
    }
}



// int main() {
   
//    std::vector<Item> itemDatas = {Item("bike",10,20,"misc")
//    ,Item("kite",5,10,"misc"),Item("shoes", 30, 25,"apparell"),Item("hat", 15, 18,"apparell"),Item("watch", 50, 30,"accessory")};
//    std::cout << "Original vector: "<<std::endl;
//    for(auto& Item:itemDatas){
//               std::cout << "Item: " << Item.name << ", Price: " << Item.price << ", Distance from seller: " << Item.distance << std::endl;

//    }
    
//    std::cout << std::endl;

//    // ShellSort shell(arr);

//    ShellSort shell(itemDatas);
//    shell.sortDistanceDescend();
//    shell.display();

//    return 0;
// }

