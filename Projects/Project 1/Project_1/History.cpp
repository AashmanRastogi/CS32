//
//  History.cpp
//  Project_1
//
//  Created by Aashman Rastogi on 4/10/23.
//

#include "History.h"
#include <iostream>
using namespace std;

History::History(int nRows, int nCols)
{
    m_row = nRows;
    m_col = nCols;
    
    for(int r = 0; r < m_row; r++)
        for(int c = 0; c < m_col; c++)
            m_recordgrid[r][c] = 0;
}

bool History::record(int r, int c)
{
    if (r < 1 || r > m_row || c < 1 || c > m_col)
    {
        return false;
    }
    
    m_recordgrid[r-1][c-1]++;
    return true;
}

void History::display() const
{
    clearScreen();
    
    char New_recordgrid[MAXROWS][MAXCOLS];
    
    for(int r = 0; r < m_row; r++)
    {
        for(int c = 0; c < m_col; c++)
        {
            if (m_recordgrid[r][c] == 0)
            {
                New_recordgrid[r][c] = '.';
            }
            else if (m_recordgrid[r][c] >= 26)
            {
                New_recordgrid[r][c] = 'Z';
            }
            else
            {
                New_recordgrid[r][c] = char(int('A') + m_recordgrid[r][c] - 1);
            }
        }
    }
    
    clearScreen();
    for(int r = 0; r < m_row; r++)
    {
        for(int c = 0; c < m_col; c++)
        {
            cout << New_recordgrid[r][c];
        }
        cout << endl;
    }
    cout << endl;

}

