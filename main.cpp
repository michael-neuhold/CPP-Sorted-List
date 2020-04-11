#include <iostream>
#include "sorted_list.h"


void test_1() {
    std::cout << "#---------- TEST 1 ----------#\n";
    sorted_list<int> sorted_list;
    sorted_list.insert(4);
    sorted_list.insert(0);
    sorted_list.insert(1);
    sorted_list.insert(7);
    sorted_list.insert(7);
    sorted_list.insert(20);
    sorted_list.insert(9);
    sorted_list.print_list();
}

void test_2() {
    std::cout << "#---------- TEST 2 ----------#\n";
    sorted_list<int> sorted_list;
    for(int i = 0; i < 10; i++) sorted_list.insert(rand() % 10);
    std::cout << "list size: " << sorted_list.size() << "\n";
}

void test_3() {
    std::cout << "#---------- TEST 3 ----------#\n";
    sorted_list<int> sorted_list;
    sorted_list.insert(4);
    sorted_list.insert(0);
    sorted_list.insert(1);
    sorted_list.insert(7);
    sorted_list.insert(7);
    sorted_list.insert(20);
    sorted_list.insert(9);
    sorted_list.print_list();
    std::cout << std::boolalpha;
    std::cout << "find 4: " << sorted_list.find(4) << "\n";
    std::cout << "find 11: " << sorted_list.find(11) << "\n";
    std::cout << "find 20: " << sorted_list.find(20) << "\n";
    std::cout << "find 8: " << sorted_list.find(8) << "\n";
    std::cout << std::noboolalpha;
}

void test_4() {
    std::cout << "#---------- TEST 4 ----------#\n";
    sorted_list<int> sorted_list;
    sorted_list.insert(4);
    sorted_list.insert(0);
    sorted_list.insert(1);
    sorted_list.insert(7);
    sorted_list.insert(7);
    sorted_list.insert(20);
    sorted_list.insert(9);
    sorted_list.print_list();
    std::cout << std::boolalpha;
    std::cout << "erase 7: " << sorted_list.erase(7) << "\n";
    std::cout << "erase 1: " << sorted_list.erase(1) << "\n";
    std::cout << "erase 21: " << sorted_list.erase(21) << "\n";
    std::cout << "erase 8: " << sorted_list.erase(8) << "\n";
    std::cout << std::noboolalpha;
    sorted_list.print_list();
}

void test_5() {
    std::cout << "#---------- TEST 5 ----------#\n";
    sorted_list<int> sorted_list;
    for(int i = 0; i < 10; i++) sorted_list.insert(rand() % 10);
    sorted_list.print_list();
    std::cout << "front: " << sorted_list.front() << "\n";
    std::cout << "back: " << sorted_list.back() << "\n";
}

void test_6() {
    std::cout << "#---------- TEST 6 ----------#\n";
    sorted_list<int> sorted_list;
    for(int i = 0; i < 10; i++) sorted_list.insert(rand() % 10);
    sorted_list.print_list();
    sorted_list.pop_front();
    sorted_list.pop_back();
    sorted_list.print_list();
}

void test(int test_number = 0) {
    switch(test_number) {
        case 0: test_1(); test_2(); test_3();
                test_4(); test_5(); test_6();
            break;
        case 1: test_1(); break;
        case 2: test_2(); break;
        case 3: test_3(); break;
        case 4: test_4(); break;
        case 5: test_5(); break;
        case 6: test_6(); break;
    }
}

int main() {

   test();

}