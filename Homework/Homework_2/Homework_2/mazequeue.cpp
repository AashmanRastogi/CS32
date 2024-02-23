//
//  mazequeue.cpp
//  Homework_2
//
//  Created by Aashman Rastogi on 5/1/23.
//

#include <string>
#include <queue>
#include <iostream>
using namespace std;

class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};

bool pathExists(char maze[][10], int sr, int sc, int er, int ec)
{
    queue<Coord> q_maze;
    Coord start_point(sr,sc);
    Coord end_point(er,ec);
    q_maze.push(start_point);
    maze[sr][sc] = '@';

    while(!q_maze.empty())
    {
        Coord curr = q_maze.front();
        cout << curr.r() << " " << curr.c() << endl;
        q_maze.pop();
        if (curr.r() == end_point.r() && curr.c() == end_point.c())
        {
            return true;
        }
        if(maze[curr.r() + 1][curr.c()] == '.') // south
        {
            Coord newpos(curr.r() + 1,curr.c());
            q_maze.push(newpos);
            maze[curr.r() + 1][curr.c()] = '@';

        if(maze[curr.r()][curr.c() + 1] == '.') // east
        {
            Coord newpos(curr.r(),curr.c() +1);
            q_maze.push(newpos);
            maze[curr.r()][curr.c() +1] = '@';

        }

        if(maze[curr.r() - 1][curr.c()] == '.') // north
        {
            Coord newpos(curr.r() - 1,curr.c());
            q_maze.push(newpos);
            maze[curr.r() - 1][curr.c()] = '@';
        }

        }
        if(maze[curr.r()][curr.c() - 1] == '.') // west
        {
            Coord newpos(curr.r(),curr.c() - 1);
            q_maze.push(newpos);
            maze[curr.r()][curr.c() -1] = '@';

        }
    }

    return false;
}


