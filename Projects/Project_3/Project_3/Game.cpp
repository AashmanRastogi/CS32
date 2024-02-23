//
//  Game.cpp
//  Project_3
//
//  Created by Aashman Rastogi on 5/28/23.
//


#include "Game.h"
#include "Player.h"
#include <iostream>
using namespace std;


Game::Game(const Board& b, Player* south, Player* north)
:m_board(b),m_south(south),m_north(north)
{
  
}

void Game::display() const
{
    int holes = m_board.holes(); // get number of holes
    cout << "  ";
    for (int i = 0; i < m_board.holes()/2; i++)
    {
        cout << "  ";
    }
    cout << m_north->name() <<endl;                     // NORTH's name
    cout << "   ";
    for (int i = 1; i <= holes; i++)
    {
        cout <<m_board.beans(NORTH, i)<< "  ";           // Display NORTH holes
    }
    
    cout << endl << m_board.beans(NORTH,POT);
    for(int i = 0; i < m_board.holes(); i++)
    {
        cout<< "   ";
        
    }
    cout << "  ";
    cout << m_board.beans(SOUTH,POT);  // Display NORTH/SOUTH pot
    cout << endl;
    cout << "   ";
    for (int i = 1; i <= holes; i++)
    {
        cout << m_board.beans(SOUTH, i)<< "  ";          // Display SOUTH holes
    }
    cout<< endl;
    cout << "   ";
    for (int i = 0; i < m_board.holes()/2; i++)
    {
        cout << "  ";
    }
    cout << m_south->name() << endl;                     // SOUTH's name
    cout<< "" << endl;
}

void Game::status(bool& over, bool& hasWinner, Side& winner) const
{
    
    if(m_board.beansInPlay(NORTH) > 0 && m_board.beansInPlay(SOUTH) > 0)
    {
        over = false;
        return;
    }
    
    if (m_board.beansInPlay(SOUTH) == 0 || m_board.beansInPlay(NORTH) == 0)
    {
        over = true;
    }
    
    if (m_board.beans(NORTH, 0) + m_board.beansInPlay(NORTH) > m_board.beans(SOUTH, 0) + m_board.beansInPlay(SOUTH))
    {
        hasWinner = true;
        over = true;
        winner = NORTH;
    }
    else if (m_board.beans(NORTH, 0) + m_board.beansInPlay(NORTH) < m_board.beans(SOUTH, 0) + m_board.beansInPlay(SOUTH))
    {
        hasWinner = true;
        over = true;
        winner = SOUTH;
    }
    else
    {
        over = true;
        hasWinner = false;
    }
}

bool Game::move(Side s)
{
    // initializing status arguments
    bool over = false;
    bool hasWinner = false;
    Side winner = NORTH;
    status(over, hasWinner, winner);
    if(over)        // if game is already over
    {
        if(m_board.beansInPlay(SOUTH) == 0 || m_board.beansInPlay(NORTH) == 0)  // if there is a winner then sweep
        {
            for(int i = 1; i <= m_board.holes(); i++)
            {
                m_board.moveToPot(NORTH, i, NORTH);
                m_board.moveToPot(SOUTH, i, SOUTH);
            }
        }
        return false;
    }
    
    while (true)
    {
        Side endside;
        int endhole;
        int hole;
        string name;

        if (s == SOUTH)
        {
            hole = m_south->chooseMove(m_board, s);
            name = m_south->name();
        }
        else
        {
            hole = m_north->chooseMove(m_board, s);
            name = m_north->name();
        }
        
        if (hole == -1)
        {
            for(int i = 1; i <= m_board.holes(); i++)
            {
                m_board.moveToPot(s, i, s);
                m_board.moveToPot(opponent(s), i, opponent(s));
            }
            break;
        }
        
        if (m_board.sow(s, hole, endside, endhole) == true)
        {
            display();                          // Display the board state after successful sow

            if (endside == s && endhole == POT) // replay
            {
                if (m_board.beansInPlay(s) != 0)
                {
                    cout << name << " gets another turn" << endl;
                    continue;
                }
                else
                {
                  break;
                }
            }
            
            // Capturing
            else if (s == endside && m_board.beans(s, endhole) == 1 && m_board.beans(opponent(s), endhole) > 0)
            {
                m_board.moveToPot(s, endhole, s);   // adding one because we are passing index value to movepot which expects the hole number instead
                m_board.moveToPot(opponent(s), endhole , s);
                cerr << name << " captured beans" << endl;
                break;
            }
            else
            {
                break;
            }
        }
        break;
    }
        
    if (m_board.beansInPlay(s) == 0)
    {
        display();
        std::string name;
        if(s == NORTH)
        {
            cout << m_north->name() << " has no beans left to sow" << endl;
            std::cout << "Sweeping remaining beans into " << m_south->name() << "'s pot."<< std::endl;
        }
        else
        {
            cout << m_south->name() << " has no beans left to sow" << endl;
            std::cout << "Sweeping remaining beans into " << m_north->name() << "'s pot."<< std::endl;
        }
        // Sweep beans into opponent's pot because s has no beans left to play
        for(int i = 1; i <= m_board.holes(); i++)
        {
            m_board.moveToPot(opponent(s), i, opponent(s));
        }
    }
//    s = opponent(s); // switching sides once turn is over
    return true;
}

void Game::play()
{
    bool over = false;
    bool hasWinner = false;
    Side winner;
    bool isSouthTurn = true; // Variable to keep track of the current player's side

    // If both players are computer players, prompt the viewer to press ENTER to continue
    bool pressEnter = !(m_north->isInteractive() || m_south->isInteractive());  // false || false = false, rest is true
    status(over,hasWinner,winner);
    while (!over)
    {
        // Display the board
        display();

        // Make a move for the current player
        if (isSouthTurn)
        {
            move(SOUTH);
        }
        else
        {
            move(NORTH);
        }

        // Check the game status
        status(over, hasWinner, winner);

        // If both players are computer players, prompt the viewer to press ENTER to continue
        if (pressEnter && !over)
        {
            std::cout << "Press ENTER to continue";
            std::cin.ignore();
        }

        // Toggle the turn to the other side
        isSouthTurn = !isSouthTurn;
    }

    // Announce the winner or a tie
    if (hasWinner)
    {
        std::string name;
        if(winner == NORTH)
        {
            name = m_north->name();
        }
        else
        {
            name = m_south->name();
        }
        std::cout << "The winner is "<< name <<"." << std::endl;
    }
    else if (!hasWinner)
    {
        std::cout << "The game resulted in a tie." << std::endl;
    }
}


int Game::beans(Side s, int hole) const
{
    return m_board.beans(s, hole);
}

