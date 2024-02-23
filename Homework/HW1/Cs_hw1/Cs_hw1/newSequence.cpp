//
//  newSequence.cpp
//  Cs_hw1
//
//  Created by Aashman Rastogi on 4/17/23.
//

#include "newSequence.h"

Sequence::Sequence(int val)
{
    if (val < 0)
    {
        exit(0);
    }
    m_seq = new ItemType[val];
    m_size = 0;
    m_maxsize = val;
    
}

Sequence::Sequence(const Sequence& other)
{
    // copy contructor 
    m_maxsize = other.m_maxsize;
    m_size = other.m_size;
        
    m_seq = new ItemType[m_maxsize];
    for(int i = 0; i < other.m_size; i++)
    {
        m_seq[i] = other.m_seq[i];
    }
}

Sequence& Sequence::operator= (const Sequence& other)
{
    if (this == &other)
    {
        return *this;
    }
    
    delete [] m_seq;
    
    m_maxsize = other.m_maxsize;
    m_size = other.m_size;
    
    m_seq = new ItemType[other.m_maxsize];
    for(int i = 0; i < other.m_size; i++)
    {
        m_seq[i] = other.m_seq[i];
    }
    
    return *this;

}

Sequence::~Sequence()
{
    delete [] m_seq;
}

bool Sequence::empty() const
{
    if (m_size == 0)
    {
        return true;
    }
    return false;
}

int Sequence::size() const
{
    return m_size;
}

int Sequence::insert(int pos, const ItemType& value)
{
    if (pos < 0 || pos > this->size())
    {
        return -1;
    }
    
    for (int n = this->size(); n > pos; n--)
    {
        m_seq[n] = m_seq[n-1];
    }
    m_seq[pos] = value;
    m_size++;
    return pos;
}

int Sequence::insert(const ItemType& value)
{
    
    if (this->size() >= m_maxsize)
        {
            return -1;
        }
        
        int p = 0;
        for(int i = 0; i < this->size(); i++)
        {
            if(value <= m_seq[i])
            {
                break;
            }
            p++;
        }
        
        
        for(int i = this->size(); i > p; i--)
        {
            m_seq[i] = m_seq[i-1];
        }
        
        m_seq[p] = value;
        m_size++;
        
        return p;
}

bool Sequence::erase(int pos)
{
    if (pos <0 || pos >= this->size())
    {
        return false;
    }
    
    for (int n = pos; n < this->size(); n++)
    {
        m_seq[n] = m_seq[n+1];
    }
    
    m_size--;
    return true;
}

int Sequence::remove(const ItemType& value)
{
    int count = 0;
    while(this->find(value) != -1)
    {
        this->erase(this->find(value));
        count++;
    }
    return count;
}

bool Sequence::get(int pos, ItemType& value) const
{
    if (pos <0 || pos >= this->size())
    {
        return false;
    }
    
    value = m_seq[pos];
    return true;
}

bool Sequence::set(int pos, const ItemType& value)
{
    if (pos <0 || pos >= this->size())
    {
        return false;
    }
    
    m_seq[pos] = value;
    return true;
}

int Sequence::find(const ItemType& value) const
{
    for (int n = 0; n < this->size(); n++)
    {
        if (m_seq[n] == value)
        {
            return n;
        }
    }
    return -1;
}

void Sequence::swap(Sequence& other)
{
    int tempSize;
    tempSize = m_size;
    m_size = other.m_size;
    other.m_size = tempSize;
        
    int tempMaxSize;
    tempMaxSize = m_maxsize;
    m_maxsize = other.m_maxsize;
    other.m_maxsize = tempMaxSize;
        
    ItemType * tempPtr;
    tempPtr = m_seq;
    m_seq = other.m_seq;
    other.m_seq = tempPtr;
        
}
