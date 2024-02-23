//
//  main.cpp
//  Project_2
//
//  Created by Aashman Rastogi on 4/20/23.
//

#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;

void test()
{
    Sequence m;
    assert(m.insert(0, "lavash") == 0);                       // Test the insert function
    assert(m.insert(1, "tortilla") == 1);
    assert(m.insert(2, "bread") == 2);

    ItemType value;
    assert(m.get(0,value) == 1);                              // Test get function
    assert(m.get(3,value) == 0);

    assert(m.insert("laddoo") == 0);                          // testing inseert(value) function
    assert(m.size() == 4);

    assert(m.find("laddoo") == 0);
    assert(m.remove("laddoo") == 1);

    assert(m.erase(0) == 1);
    assert(m.size() == 2);

    Sequence m1;
    assert(m.insert(0, "butter") == 0);                       // Test the insert function
    assert(m.insert(1, "paneer") == 1);
    assert(m.insert(2, "naan") == 2);
    m.swap(m1);
    m.dump();
    m1.dump();

    Sequence seq1;
    seq1.insert(0, "apple");
    seq1.insert(1, "banana");
    seq1.insert(2, "orange");
    seq1.insert(3, "pear");
    seq1.insert(4, "kiwi");

    Sequence seq2;
    seq2.insert(0, "orange");
    seq2.insert(1, "pear");

    assert(subsequence(seq1, seq2) == 2);
    
    Sequence seq3;
    assert(seq3.insert(0, "one") == 0);
    assert(seq3.insert(1, "two") == 1);
    assert(seq3.insert(2, "three") == 2);

    Sequence seq4;
    assert(seq4.insert(0, "hello") == 0);
    assert(seq4.insert(1, "world") == 1);
    
    seq3.dump();

    seq4.dump();

    Sequence result;
    concatReverse(seq4, seq3, result);

    result.dump();

    assert(result.size() == 5);
    assert(result.find("world") == 0);
    assert(result.find("hello") == 1);
    assert(result.find("three") == 2);
    assert(result.find("two") == 3);
    assert(result.find("one") == 4);


}

int main()
{
    test();
    cout << "Passed all tests" << endl;
    }
