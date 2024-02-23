//
//  testrainfallList.cpp
//  Cs_hw1
//
//  Created by Aashman Rastogi on 4/17/23.
//


#include "RainfallList.h"
#include "newSequence.h"
#include <iostream>
#include <cassert>
using namespace std;

int main()
{
    RainfallList r;
    assert(r.maximum() == NO_RAINFALLS);
    assert(r.minimum() == NO_RAINFALLS);
    assert(!r.add(405));
    assert(r.add(60));
    
    r.add(100);
    r.add(200);
    r.add(40);
    r.add(60);
    r.add(350);
    
    assert(r.maximum() == 350);
    assert(r.minimum() == 40);
    assert(r.size() == 6);
    assert(r.remove(60) == 1);
    assert(r.remove(100) == 1);
    assert(r.size() == 4);
    assert(r.maximum() == 350);
    assert(r.remove(10) == 0);
    assert(!r.remove(200) == 0);

    cerr << "all tests passed" << endl;
    return 0;
}

