//
//  Sequence.cpp
//  Project_2
//
//  Created by Aashman Rastogi on 4/20/23.
//

#include "Sequence.h"

Sequence::Sequence()
{
    head = nullptr;
    tail = nullptr;
    l_size = 0;
}

bool Sequence::empty() const
{
    if (l_size == 0)
    {
        return true;
    }
    return false;
}

int Sequence::size() const
{
    return l_size;
}

Sequence::~Sequence()
{
    if (head == nullptr)          // head == nullptr implies it is empty
    {
        return;
    }
    node* temp = head;            // initialize temp to head
    
    while(temp != nullptr)        // loops till temp is not a nullptr
    {
        node* p = temp->next;     // initializes p to point to the next node in temp
        delete temp;              // deletes temp
        temp = p;                 // sets temp back to p
    }
    
    head = nullptr;
    tail = nullptr;
}

// copy constructor
Sequence::Sequence(const Sequence& other)
{
    if (other.l_size == 0)   // if size is 0 then we create an empty node
    {
        head = nullptr;
        tail = nullptr;
        return;
    }
    
    l_size = other.l_size;   // setting size equal to other size
   
    head = new node;            // creates a new head
    head->prev = nullptr;       // setting new node prev to nullptr
    
    node* copynode = head;      // creating a pointer pointing to head
    
    for (node* temp = other.head; temp->next != nullptr; temp = temp->next)  // looping thru the entire "other" sequence to                                                                           get its values
    {
        node* p = new node;                     // creating pointer "p" pointing to a new node
        copynode->value = temp->value;          // entering first value of other in firt node of copynode
        copynode->next = p;                     // links copynode next to p
        p->prev = copynode;                     // links prev of p to copynode
        copynode = p;                           // points copynode to new p node (changes pointer from head to head->next )
    }
                                                // once we hit nullptr we breka out of loop, temp is at the last node
    copynode->value = other.tail->value;        // sets value of last node
    copynode->next = nullptr;                   // sets next of last node to nullptr
    tail = copynode;                            // links tail to the last node
}

Sequence& Sequence::operator= (const Sequence& other)
{
    // if the two nodes are not equal, use the swap function
    if (this != &other)
    {
        Sequence temp(other);               // we create a sequence object and pass other thru it which calls the copy c                                         constructor
        swap(temp);                         // We swap the temp sequence with the current sequence and then return
    }

    return *this;
}


int Sequence::insert(int pos, const ItemType& value)
{
    // Check if pos is a valid index
    if (pos < 0 || pos > size())
    {
        return -1;
    }
    
    // Create a new node to hold the value
    node* p = new node;
    
    // Insert the new node at the beginning of the sequence
    if (pos == 0)
    {
        p->prev = nullptr;
        p->next = head;
        p->value = value;
        head = p;
        
        // Update the tail if the sequence was empty
        if (l_size == 0)
        {
            tail = p;
            p->next = nullptr;
        }
        
        l_size++;
        return pos;
    }
    
    // Insert the new node at the end of the sequence
    else if (pos == size())
    {
        p->prev = tail;
        p->next = nullptr;
        p->value = value;
        tail->next = p;
        tail = p;
        l_size++;
        return pos;
    }
    
    // Insert the new node in the middle of the sequence
    else
    {
        // Find the node at position pos - 1
        node* temp = head;                                          // if pos is between o and size
        for (int i = 0; i < pos - 1; i++)                           // start from 0 till pos -1
        {
            temp = temp->next;                                      // takes temp to node at pos - 1
        }
        
        // Insert the new node after the node at position pos - 1
        p->prev = temp;                                             // sets prev of new node to temp
        p->next = temp->next;                                       // sets next of new node to node after temp
        p->value = value;                                           // sets value in new node
        temp->next->prev = p;                                       // sets the value of prev of node after temp to new node
        temp->next = p;                                             // sets next of temp to new node
        l_size++;
        return pos;
    }
}

int Sequence::insert(const ItemType& value)
{
    node* p = head;
    for(int i = 0; i < size(); i++)     // Iterate over the sequence using a for loop with a loop counter i.
    {
        if(value <= p->value)           // If the value to be inserted is less than or equal to the value at p
        {
            insert(i,value);            // Insert the value at position i
            return i;                   // return i
            break;                      // break out of loop
        }
        p = p->next;                    // if not then move onto the next node
    }
    insert(size(),value);               // if no value is greater than all node values then insert at the very end
    return size();                      // returning size
}

bool Sequence::erase(int pos)
{
    if (pos < 0 || pos > size())
    {
        return false;
    }
    
    if (pos == 0)
    {
        node* p = head;             // set a new pointer to head
        if (p->next != nullptr)     // condition to check if the first node is not the last node, if it is then just delete
        {                           // the node
            head = p->next;             // points head to the second node
            head->prev = nullptr;       // sets the prev of this node to nullptr
        }
        delete p;                   // deletes the new pointer which deletes the first node since it points to it
        l_size--;                   // reduced size by 1
        return true;
    }
    
    else if (pos == size())
    {
        node* p = tail;             // set a new pointer to the tail
        if (p->prev != nullptr)     // condition to check if last node is not the first node, if it is then just delete the                              node
        {
            tail = p->prev;         // points head to the second last node
            tail->next = nullptr;   // sets the next of this node to nullptr
        }
        delete p;                   // deletes the new pointer which deletes the last node since it points to it
        l_size--;
        return true;
    }
    
    else
    {
        node* p = head;
        for (int i = 0; i < size() ; i++)    // loop thru the entire node
        {
            if (i == pos)                    // if we reach the intended position
            {
                p->prev->next = p->next;     // setting the 'next' of the node before the deletion node to the node after the                             deletion node
                p->next->prev = p->prev;     // setting the 'prev' of the node after the deletion node to the node before the                             deletion node
                delete p;                    // deleting the the node
                l_size--;
                return true;
            }
            p = p->next;                     // moving to the next node on each iteration 
        }
        return false;
    }
}

int Sequence::remove(const ItemType& value)
{
    int count = 0;
    while(find(value) != -1)           // loops runs till no value is found
    {
        erase(find(value));            // we remove the value using the erase function and get its position using the                                       find function
        count++;                       // keeps a track on the number of values removed
    }
    return count;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (pos < 0 || pos > size())
    {
        return false;
    }
    int i = 0;
    for (node* p = head; p != nullptr; p = p->next)       // looping over the linked list till we find pos
    {
        if (i == pos)
        {
            value = p->value;
            return true;
        }
        i++;
    }
    return false;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos < 0 || pos > size())
    {
        return false;
    }
    
    node* p = head;                     // Initializing a node p pointing at head
    
    for (int i = 0; i < pos; i++)       // looping over the linked list till we find pos
    {
        p = p->next;                    // if not then move to the next node
    }
    p->value = value;                   // set pos value to value
    return true;                        // finally return true
}

int Sequence::find(const ItemType& value) const
{
    int i = 0;
    for (node* p = head; p!= nullptr; p = p->next)
    {
        if (p->value == value)
        {
            return i;
        }
        i++;
    }
    return -1;
}

void Sequence::swap(Sequence& other)
{
    int temp_size = l_size;         // swithcing sequence sizes using temp
    l_size = other.l_size;
    other.l_size = temp_size;
    
    node* temp_head = head;         // switching heads using temp
    head = other.head;
    other.head = temp_head;
    
    node* temp_tail = tail;         // switching tails using temp
    tail = other.tail;
    other.tail = temp_tail;
}

int subsequence(const Sequence& seq1, const Sequence& seq2)
{
    if (seq2.size() == 0 || seq1.size() < seq2.size())
        {
            return -1;
        };
    
    ItemType seq2_first;                // initializing a variable of type ItemType for seq2
    seq2.get(0, seq2_first);            // putting value of 1st node in seq2 in seq2_first
    
    for (int i = 0; i <= seq1.size() - seq2.size(); i++)   // looping till the size of seq1 - size of seq2
        {
            ItemType seq1_present;                         // initializing a variable of type ItemType for seq1
            seq1.get(i, seq1_present);                     // putting value of i in variable to store the current value at                                                  that position

            if (seq1_present == seq2_first)                // checking if there is a match between the 1st element of seq2                                                  and any element of seq1
            {
                bool match = true;                         // setting match = true

                for (int j = 1; j < seq2.size(); j++)      // looping thru t sixe of the smaller sequence
                {
                    ItemType seq1_next;                    // creating a new variable to store the next consecutive value of                                        seq1 continuing till the size of seq1
                    seq1.get(i+j, seq1_next);

                    ItemType seq2_next;                    // creating a new variable to store the next consecutive value of                                        seq2 continuing till the size of seq2
                    seq2.get(j, seq2_next);

                    if (seq1_next != seq2_next)            // now if no match
                    {
                        match = false;                     //  setting match to false
                        break;                             // breaking out of the loop
                    }
                }

                if (match)                                 // if match is true for the entire seq then return the i value
                {
                    return i;
                }
            }
        }

    return -1;                                            // else return -1;
}

void concatReverse(const Sequence& seq1, const Sequence& seq2, Sequence& result)
{
    Sequence temp;                                  // create a temp variable of type sequence

    for (int i = seq2.size() - 1; i >= 0; i--)      // iterates from the last element to the first
    {
        ItemType value;                             // variable to store value
        seq2.get(i, value);
        temp.insert(temp.size(), value);            // inserts last value of seq2 as the first in temp
    }

    for (int i = seq1.size() - 1; i >= 0; i--)      // iterates from the last element to the first in seq1
    {
        ItemType value;                             // variable to store value
        seq1.get(i, value);
        result.insert(result.size(), value);        // inserts last value of seq1 as the first directly in result
    }

    for (int i = 0; i < temp.size(); i++)           // loops thru the entire temp sequence
    {
        ItemType val;
        temp.get(i, val);
        result.insert(result.size(), val);          // inserts value of temp one by one into result which leads to direct                                                complilation of both sequences together in reverse order
    }
}

//void Sequence::dump() const            //print all the elements of the linked list
//{
//    for (node* temp = head; temp != nullptr; temp = temp->next) {
//        std::cerr << temp->value << std::endl;
//    }
//}




