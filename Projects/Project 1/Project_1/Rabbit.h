//
//  Rabbit.h
//  Project_1
//
//  Created by Aashman Rastogi on 4/10/23.
//

#ifndef Rabbit_h
#define Rabbit_h
//#include "History.h"

class Arena;  // This is needed to let the compiler know that Arena is a
              // type name, since it's mentioned in the Rabbit declaration.

class Rabbit
{
  public:
      // Constructor
    Rabbit(Arena* ap, int r, int c);

      // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;

      // Mutators
    void move();

  private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int    m_health;
    int    m_idleTurnsRemaining;

};

#endif /* Rabbit_h */
