//
//  Player.h
//  Project_3
//
//  Created by Aashman Rastogi on 5/24/23.
//

#ifndef Player_h
#define Player_h
#include "Side.h"
#include <string>

//========================================================================
// Timer t;                 // create and start a timer
// t.start();               // restart the timer
// double d = t.elapsed();  // milliseconds since timer was last started
//========================================================================

#include <chrono>

class Board;

class Timer
{
  public:
    Timer()
    {
        start();
    }
    void start()
    {
        m_time = std::chrono::high_resolution_clock::now();
    }
    double elapsed() const
    {
        std::chrono::duration<double, std::milli> diff = std::chrono::high_resolution_clock::now() - m_time;
        return diff.count();
    }
  private:
    std::chrono::high_resolution_clock::time_point m_time;
};

class JumpyTimer
{
  public:
    JumpyTimer(int jumpInterval)
     : m_jumpInterval(jumpInterval), m_callsMade(0)
    {
        actualElapsed();
    }
    double elapsed()
    {
        m_callsMade++;
        if (m_callsMade == m_jumpInterval)
        {
            m_lastElapsed = m_timer.elapsed();
            m_callsMade = 0;
        }
        return m_lastElapsed;
    }
    double actualElapsed()
    {
        m_lastElapsed = m_timer.elapsed();
        return m_lastElapsed;
    }
  private:
    Timer m_timer;
    int m_jumpInterval;
    int m_callsMade;
    int m_lastElapsed;
};

unsigned long f_helper(int n);
unsigned long f(int n);




class Player
{
public:
    Player(std::string name);
//Create a Player with the indicated name.
    std::string name() const;
//Return the name of the player.
    virtual bool isInteractive() const;
//Return false if the player is a computer player. Return true if the player is human. Most kinds of players will be computer players.
    virtual int chooseMove(const Board& b, Side s) const = 0;
//Every concrete class derived from this class must implement this function so that if the player were to be playing side s and had to make a move given board b, the function returns the move the player would choose. If no move is possible, return −1.
    virtual ~Player();
//Since this class is designed as a base class, it should have a virtual destructor.
private:
    std::string m_name;
};


class HumanPlayer : public Player
{
public:
    HumanPlayer(std::string name);
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~HumanPlayer();
};

class BadPlayer : public Player
{
public:
    BadPlayer(std::string name);
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~BadPlayer();
};

class SmartPlayer : public Player
{
public:
    SmartPlayer(std::string name);
    virtual bool isInteractive() const;
    virtual int chooseMove(const Board& b, Side s) const;
    virtual ~SmartPlayer();
private:
    int eval(const Board& board, Side side) const;
    // always evaluate w.r.t. to max player
    bool soworcapture(Board& board, int move, Side side) const;
    //return true if make another move
    int minmax(const Board& board, Side side, bool isMax ,int depth, JumpyTimer& timer) const ;
    // return value for a certain move
    int m_depth = 8;
};


#endif /* Player_h */
