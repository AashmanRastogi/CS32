//
//  Player.cpp
//  Project_3
//
//  Created by Aashman Rastogi on 5/24/23.
//

#include "Player.h"
#include "Board.h"
using namespace std;

Player::Player(std::string name)
{
    m_name = name;
}

std::string Player::name() const
{
    return m_name;
}

bool Player::isInteractive() const
{
    return false;
}

Player::~Player()
{
    
}


// HUMAN PLAYER
HumanPlayer::HumanPlayer(std::string name):Player(name)
{
    
}

bool HumanPlayer::isInteractive() const
{
    return true;
}

int HumanPlayer::chooseMove(const Board& b, Side s) const
{
    if (b.beansInPlay(s) == 0)
    {
        return false;
    }
    
    int hole = -1;
    while (true)
    {
        std::cout << "Select a hole, " << Player::name() << ": ";
        std::cin >> hole;
        
        if (hole > 0 && hole <= b.holes() && b.beans(s, hole) > 0)
        {
            break;
        }
        
        if(hole <= 0 || hole > b.holes())
        {
            cout << "The hole number must be from 1 to " << b.holes() << "." << endl;
        }
        else
        {
            cout << "Can't access Pot or no beans in the hole" << endl;
        }
    }
    return hole;
}

HumanPlayer::~HumanPlayer()
{
    
}


// BADPLAYER
BadPlayer::BadPlayer(std::string name):Player(name)
{
    
}

bool BadPlayer::isInteractive() const
{
    return false;
}

int BadPlayer::chooseMove(const Board& b, Side s) const
{
    if(b.beansInPlay(s) == 0)
    {
        return -1;
    }
        
    int move = -1;
    int holes = b.holes();
    
    for(int i = 1; i <= holes; i++)
    {
        //pick the first hole that has more than 0 beans
        if(b.beans(s, i) > 0)
        {
            move = i;
            break;
        }
    }
    std::cout << Player::name() << " chooses hole " << move << std::endl;
    return move;
}

BadPlayer::~BadPlayer()
{
    
}

// SMARTPLAYER

SmartPlayer::SmartPlayer(std::string name):Player(name)
{
    
}
bool SmartPlayer::isInteractive() const
{
    return false;
}

int SmartPlayer::chooseMove(const Board& b, Side s) const
{
//    double timeLimit = 4990;
    JumpyTimer timer(1000);
//    m_timer.start();
   
    if (b.beansInPlay(s) == 0)
    {
        return -1;
    }
    
    int move = 0;          // init hole number
    int bestval = -10000;  // init best value to lowest
    int newbestval = 0;    // init new val which we get after sowing
    int m_depth = 9;
    for(int i = 1; i <= b.holes(); i++)
    {
        if(b.beans(s,i) > 0)                           // for all holes in the side
        {
            Board tempB(b);                         // creates a temp board of same values in b
            bool canSowCap = soworcapture(tempB, i, s);   // checks to see if we can make another move
            bool isMax;
                                //sow at that position on a temp board if you can make another turn
            if(canSowCap)
            {
                isMax = true; // tries to maximize again and is same side
                newbestval = minmax(tempB, s, isMax, m_depth, timer);  // get the evaluation value of our new move to compare with the previous move
            }
            else  //if you cannot make another turn
            {
                isMax = false;
                newbestval = minmax(tempB, s, isMax, m_depth, timer); //  will now evaluate the game tree from the perspective of minimizing the score, which simulates the opponent's turn.
            }
            if(newbestval >= bestval)// if our new move is better or equally evaluated set move to i
            {
                bestval = newbestval;
                move = i;
            }
        }
    }
    cout << Player::name() << " chooses hole " << move << endl;
    return move;
}

// heuristic evaluation
int SmartPlayer::eval(const Board &board, Side s) const
{
    // If the game is over, the outcome can be determined exactly.
    if (board.beansInPlay(s) == 0 || board.beansInPlay(opponent(s)) == 0)
    {
        int myBeans = board.beans(s, POT) + board.beansInPlay(s);
        int opponentBeans = board.beans(opponent(s), POT) + board.beansInPlay(opponent(s));

        if (myBeans > opponentBeans)
            return 10000;  // A winning state
        else if (myBeans < opponentBeans)
            return -10000; // A losing state
        else
            return 0; // A tie
    }

    // If one player has captured more than half of the total beans, they are likely to win.
    if (board.beans(s, POT) > board.totalBeans()/2)
        return 10000;
    else if (board.beans(opponent(s), POT) > board.totalBeans()/2)
        return -10000;

    // Evaluate based on the number of possible moves each player has.
    int myPossibleMoves = 0;
    int opponentPossibleMoves = 0;
    for (int i = 1; i <= board.holes(); i++)
    {
        if (board.beans(s, i) > 0)
            myPossibleMoves++;
        if (board.beans(opponent(s), i) > 0)
            opponentPossibleMoves++;
    }

    // If one player has significantly more possible moves, they have an advantage.
    if (myPossibleMoves > opponentPossibleMoves + 2)
        return 5000;
    else if (opponentPossibleMoves > myPossibleMoves + 2)
        return -5000;

    // Evaluate based on the difference in captured beans and possible moves.
    int score = 100 * (board.beans(s, POT) - board.beans(opponent(s), POT))
              + 10 * (myPossibleMoves - opponentPossibleMoves);

    return score;
}

bool SmartPlayer::soworcapture(Board &board, int move, Side s) const
{
    Side endside;
    int endhole;
    bool sowed = board.sow(s, move, endside, endhole);
    
    if (!sowed)   // if we cannot sow further return false
    {
        return false;
    }
    
    // checks if the move led to a capture and then turn ends therefore no more move
    if (endhole != POT && board.beans(s, endhole) == 1 && board.beans(opponent(s), endhole) > 0)
    {
        board.moveToPot(s, endhole, s);
        board.moveToPot(opponent(s), endhole, s);
        return false;
    }
    
    // if last bean in pot then can sow again therefore return true
    if (endside == s && endhole == POT)
    {
        return true;
    }
    // if nothing happens return false
    return false;
}

int SmartPlayer::minmax(const Board& board, Side s, bool isMax ,int depth, JumpyTimer& timer) const
{
    int bestvalHole;
    
    if(board.beansInPlay(s) == 0 || board.beansInPlay(opponent(s)) == 0 || depth <= 0)
    {
        int result = eval(board, s);
        return result;
    }
    
    cerr << timer.elapsed()<<endl;
    if(timer.actualElapsed() >=4900)
    {
        cerr << "timed out\n";
        return eval(board, s);
    }
    
    if(isMax)  // maximizing value
    {
        bestvalHole = -10000;
        for(int i = 1; i <= board.holes(); i++)// loop through possible moves
        {
            if(board.beans(s, i) > 0)
            {
                if(timer.actualElapsed() >=4900)
                {
                    cerr << "time\n";
                    return eval(board, s);
                }
                
                Board tempB(board);
                bool sow_Again = soworcapture(tempB, i, s);// make move
                bool IsMax;
                int n_maxhole;
                
                if(timer.actualElapsed() >=4900)
                {
                    cerr << "timed out\n";
                    return eval(board, s);
                }
                
                if(sow_Again) // can take another turn
                {
                    IsMax = true;
                    n_maxhole = minmax(tempB, s, IsMax, depth - 1, timer);
                }
                else // you cannot take another turn
                {
                    IsMax = false;
                    n_maxhole = minmax(tempB, opponent(s), IsMax, depth - 1, timer);
                }
                if(bestvalHole <= n_maxhole) // if new max val
                {
                    bestvalHole = n_maxhole;
                }
            }
        }
    }
    else  // minimizing value
    {
        bestvalHole = 10000;
        for(int i = 1; i <= board.holes(); i++)// loop through possible moves
        {
            if(timer.actualElapsed() >=4900)
            {
                cerr << "timed out\n";
                return eval(board, s);
            }
            
            if(board.beans(s, i) > 0)
            {
                Board tempB(board);
                bool sow_Again = soworcapture(tempB, i, s);// make move
                bool IsMax;
                int n_minhole;
                
                if(timer.actualElapsed() >=4900)
                {
                    cerr << "timed out\n";
                    return eval(board, s);
                }
                
                if(sow_Again) // can take another turn
                {
                    IsMax = false;
                    n_minhole = minmax(tempB, opponent(s), IsMax, depth - 1, timer);
                }
                else // you cannot take another turn
                {
                    IsMax = true;
                    n_minhole = minmax(tempB, opponent(s), IsMax, depth - 1, timer);
                }
                if(bestvalHole >= n_minhole) // if new min val
                {
                    bestvalHole = n_minhole;
                }
            }
        }
    }
    return bestvalHole;
}

SmartPlayer::~SmartPlayer()
{
    
}

//unsigned long f_helper(int n, double timeLimit, JumpyTimer& timer)
//{
//    unsigned long callCount = 1;
//    if (n == 0)
//    {
//        callCount += 0;  /// do a base case computation
//    }
//    else if (timeLimit <= 0)
//    {
//        callCount += 0;  //  do non-recursive heuristic computation
//    }
//    else
//    {
//        for (int branchesLeftToExplore = 10; branchesLeftToExplore > 0; branchesLeftToExplore--)
//        {
//            // Allocate remaining time limit equally among remaining braches to explore
//            double thisBranchTimeLimit = timeLimit / branchesLeftToExplore;
//
//            // Save branch start time so can compute the time the branch took
//            double startTime = timer.elapsed();
//            // Explore this branch
//            callCount += f_helper(n-1, thisBranchTimeLimit, timer);
//            // Adjust remaining time
//            timeLimit -= (timer.elapsed() - startTime);
//            if (timeLimit <= 0)
//            {
//                timeLimit = 0;
//            }
//        }
//    }
//    return callCount;
//}
//
//unsigned long f(int n)
//{
//    double timeLimit = 4990;  // 4.99 seconds; allow 10 ms for wrapping up
//    JumpyTimer timer(1000);
//    unsigned long result = f_helper(n, timeLimit, timer);
//    cout << timer.actualElapsed() << " ms" << endl;
//    return result;
//}



