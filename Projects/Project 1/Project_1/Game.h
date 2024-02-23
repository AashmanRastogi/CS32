//
//  Game.h
//  Project_1
//
//  Created by Aashman Rastogi on 4/10/23.
//

#ifndef Game_h
#define Game_h


#include "Player.h"
#include "globals.h"
class Arena;

class Game
{
  public:
      // Constructor/destructor
    Game(int rows, int cols, int nRabbits);
    ~Game();

      // Mutators
    void play();

  private:
    Arena* m_arena;

      // Helper functions
    std::string takePlayerTurn();
};

#endif /* Game_h */
