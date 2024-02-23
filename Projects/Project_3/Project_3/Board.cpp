//
//  Board.cpp
//  Project_3
//
//  Created by Aashman Rastogi on 5/24/23.
//

#include "Board.h"
using namespace std;


Board::Board(int nHoles, int nInitialBeansPerHole)
{
    if (nHoles <= 0)
    {
        m_nHoles = 1;
    }
    else
    {
        m_nHoles = nHoles;
    }
    if (nInitialBeansPerHole < 0)
    {
        m_nInitialBeansPerHole = 0;
    }
    else
    {
        m_nInitialBeansPerHole = nInitialBeansPerHole;
    }
    
    for (int i = 0; i < m_nHoles; i++)
    {
        v_south.push_back(m_nInitialBeansPerHole);    // setting the number of holes with their init bean val
        v_north.push_back(m_nInitialBeansPerHole);    // setting the number of holes with their init bean val
    }
    
    n_pot = POT;
    s_pot = POT;
}

int Board::holes() const
{
    return m_nHoles;
}


int Board::beans(Side s, int hole) const
{
    
    if (hole < 0 || hole > m_nHoles)
    {
        return -1;
    }
    
    if (s == NORTH)
    {
        if (hole == POT)
        {
            return n_pot;
        }
        else
        {
            return v_north[hole - 1]; // account for indexing eg hole = 2 implies index 1
        }
    }
    if (s == SOUTH)
    {
        if (hole == POT)
        {
            return s_pot;
        }
        else
        {
            return v_south[hole - 1]; // account for indexing eg hole = 2 implies index 1
        }
    }
    return -1;
}

int Board::beansInPlay(Side s) const
{
    int sum = 0;
    
    if (s == NORTH)
    {
        for (int i = 0; i < m_nHoles; i++)
        {
            sum += v_north[i];
        }
        return sum;
    }
    
    if(s == SOUTH)
    {
        for (int i = 0; i < m_nHoles; i++)
        {
            sum += v_south[i];
        }
        return sum;
    }
    
    return -1;
}

int Board::totalBeans() const
{
    int sum = 0;
    
    for (int i = 0; i < m_nHoles; i++)
    {
        sum += v_north[i] + v_south[i];
    }
    
    return sum + n_pot + s_pot;

}

bool Board::sow(Side s, int hole, Side& endSide, int& endHole)
//If the hole indicated by (s,hole) is empty or invalid or a pot, this function returns false without changing anything. Otherwise, it will return true after sowing the beans: the beans are removed from hole (s,hole) and sown counterclockwise, including s's pot if encountered, but skipping s's opponent's pot. The function sets the parameters endSide and endHole to the side and hole where the last bean was placed. (This function does not make captures or multiple turns; different Kalah variants have different rules about these issues, so dealing with them should not be the responsibility of the Board class.)
{
    if (s != NORTH && s != SOUTH)
    {
        return false;
    }
    if (hole <= 0 || hole > m_nHoles || hole == POT)
    {
        return false;
    }
    if (s == NORTH)                                         // starting with NORTH side
    {
        int beans = v_north[hole - 1];

        if (beans == 0)
        {
            return false;
        }
        v_north[hole - 1] = 0;

        for (int i = hole - 2; i >= 0 ; i--)            // when selecting hole need to start adding from the hole before
        {
            v_north[i]++;
            beans--;
            if (beans == 0)
            {
                endSide = NORTH;
                endHole = i + 1;
                return true;
            }
        }
        while (beans > 0)
        {
            if (beans > 0)
            {
                n_pot++;
                beans--;
                if (beans == 0)
                {
                    endSide = NORTH;
                    endHole = POT;
                    return true;
                }
            }

            if (beans > 0)
            {
                beans = sowSide(SOUTH, beans, 0 , endHole);
                if (beans == 0)
                {
                    endSide = SOUTH;
                    endHole = endHole;
                    return true;
                }
                else if (beans > 0)
                {
                    beans = sowSide(NORTH, beans, m_nHoles, endHole);
                    if (beans == 0)
                    {
                        endSide = NORTH;
                        endHole = endHole;
                        return true;
                    }
                }
            }
        }
        return false;
    }
    if (s == SOUTH)
    {
        int beans = v_south[hole - 1];

        if (beans == 0)
        {
            return false;
        }
        else
        {
            v_south[hole - 1] = 0;
        }
            
        for (int i = hole; i <= m_nHoles - 1; i++)
        {
            v_south[i]++;
            beans--;
            if (beans == 0)
            {
                endSide = SOUTH;
                endHole = i + 1;
                return true;
            }
        }
        
        while(beans > 0)
        {
            if (beans > 0)
            {
                s_pot++;
                beans--;
                if (beans == 0)
                {
                    endSide = SOUTH;
                    endHole = POT;
                    return true;
                }
            }

            if (beans > 0)
            {
                beans = sowSide(NORTH, beans, m_nHoles , endHole);
                if (beans == 0)
                {
                    endSide = NORTH;
                    endHole = endHole ;
                    return true;
                }
                else if(beans > 0)
                {
                    beans = sowSide(SOUTH, beans, 0 , endHole);
                    if (beans == 0)
                    {
                        endSide = SOUTH;
                        endHole = endHole ;
                        return true;
                    }
                }
            }
        }
        return false;
    }
    return true;
}

int Board::sowSide(Side s, int beans, int startHole, int& endHole)
{
    if (s == NORTH)
    {
        for (int i = startHole - 1; i >= 0 && beans > 0; i--)
        {
            v_north[i]++;
            beans--;
            endHole = i + 1; // adjust hole number based on index
        }
    }

    if (s == SOUTH)
    {
        for (int i = startHole; i <= m_nHoles - 1 && beans > 0; i++)
        {
            v_south[i]++;
            beans--;
            endHole = i + 1; // adjust hole number based on index
        }
    }
    return beans;
}


bool Board::moveToPot(Side s, int hole, Side potOwner)
{
    if (s != NORTH && s != SOUTH)
        {
            return false;
        }
    if (hole < 0 || hole > m_nHoles || hole == POT)
        {
            return false;
        }
    if (s == NORTH)
    {
        if (potOwner == NORTH)
        {
            n_pot += v_north[hole -1];
            v_north[hole -1] = 0;
        }
        if (potOwner == SOUTH)
        {
            s_pot += v_north[hole -1];
            v_north[hole -1] = 0;
        }
        
    }
    if (s == SOUTH)
    {
        if (potOwner == NORTH)
        {
            n_pot += v_south[hole -1];
            v_south[hole -1] = 0;
        }
        if (potOwner == SOUTH)
        {
            s_pot += v_south[hole -1];
            v_south[hole -1] = 0;
        }
    }
    return true;
}

bool Board::setBeans(Side s, int hole, int beans)
{
    if (s != NORTH && s != SOUTH)
        {
            return false;
        }
    if (hole < 0 || hole > m_nHoles)
        {
            return false;
        }
    if (beans < 0)
    {
        return false;
    }
    if (s == NORTH)
    {
        if (hole == POT)
        {
            n_pot = beans;
        }
        else
        {
            v_north[hole - 1] = beans;
        }
        
    }
    if (s == SOUTH)
    {
        if (hole == POT)
        {
            s_pot = beans;
        }
        else
        {
            v_south[hole - 1] = beans;
        }
    }
    return true;
}

