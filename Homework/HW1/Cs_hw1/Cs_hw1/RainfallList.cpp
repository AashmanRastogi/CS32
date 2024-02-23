//
//  RainfallList.cpp
//  Cs_hw1
//
//  Created by Aashman Rastogi on 4/17/23.
//

#include "RainfallList.h"


RainfallList::RainfallList()
:r_seq()
{
     
}

bool RainfallList::add(unsigned long rainfall)
{
    if (rainfall < 0 || rainfall > 400)
    {
        return false;
    }
    
    if (r_seq.insert(r_seq.size(),rainfall) == -1)
    {
        return false;
    }
    return true;
}

bool RainfallList::remove(unsigned long rainfall)
{
    if (r_seq.find(rainfall) == -1)
    {
        return false;
    }
    
    r_seq.erase(r_seq.find(rainfall));
    return true;
}

int RainfallList::size() const
{
    return r_seq.size();
}


unsigned long RainfallList::minimum() const
{
    if (r_seq.empty())
    {
        return NO_RAINFALLS;
    }
    
    unsigned long temp;
    
    unsigned long min;
    r_seq.get(0,min);
    
    for (int n = 0; n < r_seq.size(); n++)
    {
        r_seq.get(n,temp);
        
        if (temp < min)
        {
            min = temp;
        }
    }
    return min;
}

unsigned long RainfallList::maximum() const
{
    if (r_seq.empty())
    {
        return NO_RAINFALLS;
    }
    
    unsigned long temp;
    
    unsigned long max;
    r_seq.get(0,max);
    
    for (int n = 0; n < r_seq.size(); n++)
    {
        r_seq.get(n,temp);
        
        if (temp > max)
        {
            max = temp;
        }
    }
    return max;
}

