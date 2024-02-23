//
//  testnewSequence.cpp
//  Cs_hw1
//
//  Created by Aashman Rastogi on 4/17/23.
//

#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    Sequence f;
    assert(f.empty() == 1);
    f.insert(10);
    f.insert(10);
    f.insert(10);
    f.insert(40);
    f.insert(50);
    f.insert(5);
    f.insert(20);

    assert(f.size() == 7);
    assert(f.remove(10) == 3);
    assert(f.size() == 4);
    assert(f.find(5) == 0);
    assert(f.find(20) == 1);
    assert(f.empty() == 0);

    f.erase(0);
    f.erase(0);
    assert(f.empty() == 0);

    Sequence h(2);
    assert(h.insert(50) == 0);
    assert(h.insert(90) == 1);
    assert(h.size() == 2);

    ItemType x;
    assert(h.get(0, x)  &&  x == 50);
    assert(h.get(1, x)  &&  x == 90);
    assert(h.insert(2) == -1);
    assert(h.erase(1) == 1);
    assert(h.remove(50) == 1);
    assert(h.empty() == 1);


    Sequence a(1000);   // a can hold at most 1000 items
    Sequence b(5);      // b can hold at most 5 items
    Sequence c;         // c can hold at most DEFAULT_MAX_ITEMS items
    ItemType v = 10;

    // No failures inserting 5 items into b
    for (int k = 0; k < 5; k++)
        assert(b.insert(v) != -1);

        // Failure if we try to insert a sixth item into b
        assert(b.insert(v) == -1);

        // When two Sequences' contents are swapped, their capacities are
        // swapped as well:
        a.swap(b);
        assert(a.insert(v) == -1  &&  b.insert(v) != -1);

    cerr << "all tests passed" << endl;

    return 0;
}
