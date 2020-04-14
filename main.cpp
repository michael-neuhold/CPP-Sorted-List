#include <iostream>
#include "sorted_list.h"
#include <list>

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
    sorted_list<int> sorted_list{4, 0, 1, 7, 7, 20, 9};
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
    sorted_list<int> sorted_list{4, 0, 1, 7, 7, 20, 9};
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

void test_7() {
    std::cout << "#---------- TEST 7 ----------#\n";
    sorted_list<int> sorted_list;
    sorted_list.front();
    //sorted_list.back();
    //sorted_list.pop_back();
    //sorted_list.pop_front();
}

void test_8() {
    std::cout << "#---------- TEST 8 ----------#\n";
    sorted_list<int> sorted_list{4, 1, 3, 20, 9, 7, 11, 5};
    sorted_list.print_list();
    auto iter = sorted_list.begin();
    iter += 3;
    std::cout << "inserted: " << *(sorted_list.insert(iter, 8)) << "\n";
    std::cout << "inserted: " << *(sorted_list.insert(iter, 0)) << "\n";
    iter += 3;
    std::cout << "inserted: " << *(sorted_list.insert(iter, 100)) << "\n";
    sorted_list.print_list();
}

void test_9() {
    std::cout << "#---------- TEST 9 ----------#\n";
    sorted_list<int> sorted_list{4, 1, 3, 20, 9, 7, 11, 5};
    sorted_list.print_list();
    auto iter_1 = sorted_list.begin();
    iter_1 += 3;
    auto iter_2 = sorted_list.end();
    sorted_list.erase(iter_1,iter_2);
    std::cout << "front: " << sorted_list.front() << "\n";
    std::cout << "back: " << sorted_list.back() << "\n";
    sorted_list.print_list();
}

void test_10() {
    std::cout << "#---------- TEST 10 ---------#\n";
    sorted_list<int> sorted_list{4, 1, 3, 20, 9, 7, 11, 5};
    sorted_list.print_list();
    auto r_iter = sorted_list.rbegin();
    std::cout << "rever. list: ";
    for(auto i = r_iter; i != sorted_list.rend(); i++) {
        std::cout << *i << " ";
    }
    std::cout << "\n";
}

void test_11() {
    std::cout << "#---------- TEST 11 ---------#\n";
    sorted_list<int> sorted_list{4, 1, 3, 20, 9, 7, 11, 5};
    sorted_list.print_list();
    std::cout << "std::reverse:\n";
    std::reverse(sorted_list.begin(),sorted_list.end());
    sorted_list.print_list();
}

void test_12() {
    std::cout << "#---------- TEST 12 ---------#\n";
    sorted_list<int> sorted_list{4, 1, 3, 20, 9, 7, 11, 5};
    sorted_list.print_list();
    sorted_list.erase(std::remove_if(sorted_list.begin(),sorted_list.end(),
            [](unsigned int x){ return x < 10; }),sorted_list.end());
    sorted_list.print_list();
}

void test_13() {
    std::cout << "#---------- TEST 13 ---------#\n";
    sorted_list<int> sorted_list{4, 1, 3, 20, 9, 7, 11, 5};
    sorted_list.print_list();
    std::transform(sorted_list.begin(), sorted_list.end(), sorted_list.begin(),
            [](int x) -> int { return x * 2; });
    sorted_list.print_list();
}

void test_14() {
    std::cout << "#---------- TEST 14 ---------#\n";
    sorted_list<int> sorted_list{4, 1, 3, 20, 9, 7, 11, 5, 21};
    sorted_list.print_list();
    UnaryPredicate is_odd;
    sorted_list.erase_if(is_odd);
    sorted_list.print_list();
}

void test(int test_number = 0) {
    switch(test_number) {
        case 0: test_1(); test_2(); test_3();
                test_4(); test_5(); test_6();
                test_8(); test_9(); test_10();
                test_11(); test_12(); test_13();
                test_14();
            break;
        case 1: test_1(); break;
        case 2: test_2(); break;
        case 3: test_3(); break;
        case 4: test_4(); break;
        case 5: test_5(); break;
        case 6: test_6(); break;
        case 7: test_7(); break;
        case 8: test_8(); break;
        case 9: test_9(); break;
        case 10: test_10(); break;
        case 11: test_11(); break;
        case 12: test_12(); break;
        case 13: test_13(); break;
        case 14: test_14(); break;
    }
}

int main() {

    test();

}