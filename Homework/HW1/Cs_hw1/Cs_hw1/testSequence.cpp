//
//  testSequence.cpp
//  Cs_hw1
//
//  Created by Aashman Rastogi on 4/17/23.
//


#include "Sequence.h"
#include <iostream>
#include <cassert>
using namespace std;


int main()
{
//    Sequence s;
//    assert(s.empty());
//    assert(s.find("laobing") == -1);
//    assert(s.insert("laobing") == 0);
//    assert(s.size() == 1  &&  s.find("laobing") == 0);
//    cout << "Passed all tests" << endl;
    
    Sequence s;
    assert(s.empty());
    assert(s.find(42) == -1);
    assert(s.insert(42) == 0);
    assert(s.insert(54) == 1);
    assert(s.insert(50) == 1);
    assert(s.size() == 3 && s.find(42) == 0);
    
    Sequence a;
    ItemType x;
    assert(a.empty() == 1);
    assert(a.size() == 0);
    assert(a.insert(100, 800) == -1);
    assert(a.insert(0,30) == 0);
    assert(a.insert(1,50) == 1);
    assert(a.insert(2,77) == 2);
    assert(a.insert(3,55) == 3);
    assert(a.insert(4,22) == 4);
    assert(a.size() == 5);

    assert(a.insert(5,30) == 5);
    assert(a.remove(30) == 2);
    assert(a.remove(203230283028) == 0);
    assert(a.size() == 4);

    assert(a.erase(5) == 0);
    assert(a.erase(0) == 1);
    assert(a.size() == 3);
    
    a.erase(0);
    a.erase(0);
    a.erase(0);
    assert(a.empty() == 1);

    a.insert(0,122);
    a.insert(1,10223);
    a.insert(2,10);
    a.insert(3,1053);
    a.insert(4,1033);
    assert(a.erase(5) == 0);

    a.get(2, x);
    assert(x == 10);

    assert(a.get(232, x) == 0);
    assert(x == 10);

    Sequence b;
    assert(b.empty() == 1);
    b.insert(1);//0
    b.insert(2);//1
    b.insert(3);//2
    b.insert(4);//3
    b.insert(5);//4

    Sequence c;
    assert(c.empty() == 1);
    c.insert(5);//0
    c.insert(10);//1
    c.insert(15);//2
    c.insert(20);//3
    c.insert(25);//4
    c.insert(30);//5
    

    c.swap(b);
    assert( c.find(5) == 4);
    assert( c.find(1) == 0);
        
    cerr << "all tests passed"<<endl;
    return 0;
    
}

