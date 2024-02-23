//
//  newSequence.h
//  Cs_hw1
//
//  Created by Aashman Rastogi on 4/17/23.
//

#ifndef newSequence_h
#define newSequence_h

#include <string>
#include <iostream>
using namespace std;

using ItemType = unsigned long;
const int DEFAULT_MAX_ITEMS = 250;

class Sequence
{
public:
    Sequence(int val = DEFAULT_MAX_ITEMS);
    // Create an empty sequence (i.e., one whose size() is 0).
    Sequence(const Sequence& other);
    // copy constructer
    Sequence& operator = (const Sequence& other);
    // operator
    ~Sequence();
    // deconstructer
    bool empty() const;  // Return true if the sequence is empty, otherwise false.
    int size() const;    // Return the number of items in the sequence.
    int insert(int pos, const ItemType& value);
    int insert(const ItemType& value);
    bool erase(int pos);
    int remove(const ItemType& value);
    bool get(int pos, ItemType& value) const;
    bool set(int pos, const ItemType& value);
    int find(const ItemType& value) const;
    void swap(Sequence& other);
    
private:
    ItemType* m_seq;
    int m_size;
    int m_maxsize;
};

#endif /* newSequence_h */
