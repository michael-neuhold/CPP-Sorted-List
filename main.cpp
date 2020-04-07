#include <iostream>
#include "sorted_list.h"


int main() {

    sorted_list<int> mylist;

    mylist.insert(4);
    mylist.insert(0);
    mylist.insert(1);
    mylist.insert(7);
    mylist.insert(7);
    mylist.insert(20);
    mylist.insert(9);

    // print testing
    //mylist.print_list();

/*
    // list size
    std::cout << "========= size =========\n";
    std::cout << "list size: " << mylist.size() << "\n";

    // find testing
    std::cout << "========= find =========\n";
    std::cout << "find 4: " << mylist.find(4) << "\n";
    std::cout << "find 11: " << mylist.find(11) << "\n";
    std::cout << "find 20: " << mylist.find(20) << "\n";
    std::cout << "find 8: " << mylist.find(8) << "\n";

    // erase testing
    std::cout << "========= erase =========\n";
    std::cout << "erase 7: " << mylist.erase(7) << "\n";
    std::cout << "erase 1: " << mylist.erase(1) << "\n";
    std::cout << "erase 21: " << mylist.erase(21) << "\n";
    std::cout << "erase 8: " << mylist.erase(8) << "\n";

    // front & back testing
    std::cout << "===== front & back ======\n";
    std::cout << "front: " << mylist.front() << "\n";
    std::cout << "back: " << mylist.back() << "\n";

    // pop front & pop back testing
    std::cout << "== pop front & back ======\n";
    mylist.pop_front();
    mylist.pop_back();
*/


   /* for(auto &p : mylist) {
        std::cout << "value_iterator: " << p << std::endl;
    }*/

    //auto iter = mylist.end();

   // iter -= 2;

    //std::cout << *iter <<std::endl;
    //std::cout << "value: " << *(iter++) << std::endl;
    //std::cout << "value: " << *iter << std::endl;


    mylist.print_list();

    auto iter = mylist.begin();
    ++iter;
    ++iter;
    auto test = mylist.insert(iter,100);
    mylist.print_list();



}