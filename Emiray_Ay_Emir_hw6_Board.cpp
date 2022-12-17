/* Emir Ay
 date created: 18/05/2022
 date finished: 25/05/2022
 I used both xCode and Visual Studio for coding homework6.
 As far as I know, it runs properly on VS2012. */

#include <iostream>
#include "Emiray_Ay_Emir_hw6_Board.h"
using namespace std;

template <class Type> // Destructor
Board<Type>::~Board()
{
    for (int i=0; i < rows; i++)
        delete[] matrix[i];
}

template <> // Parametric constructor for int type
Board<char>::Board (int row, int col)
    :rows(row), cols(col)
{
    matrix = new char* [rows];
    
    for (int i=0; i<rows; i++)
        matrix[i] = new char[cols*2];
        
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j < cols*2; j++)
        {
            if (j%2 == 0)
                matrix[i][j] = '0';
            else
                matrix[i][j] = '-';
        }
    }
}

template <> // Parametric constructor for char type
Board<int>::Board (int row, int col)
    :rows(row), cols(col)
{
    matrix = new int* [rows];
    
    for (int i=0; i<rows; i++)
        matrix[i] = new int[cols*2];
        
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j < cols*2; j++)
        {
            if (j%2 == 0)
                matrix[i][j] = 0;
            else
                matrix[i][j] = -1;
        }
    }
}

template <class Type> // Copy Constructor
Board<Type>::Board(const Board & copy)
{
    matrix = copy.createClone();
    rows = copy.rows;
    cols = copy.cols;
}

template <class Type> // creates clone for copy const.
Type** Board<Type>::createClone() const
{
    Type** clone;
    clone = new Type* [rows];
    
    for (int i=0; i<rows; i++)
        clone[i] = new Type[cols*2];
    
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols*2; j++)
        {
            clone[i][j] = matrix[i][j];
        }
    }
    return clone;
}

template <class Type> // Displays board as 2D matrix shape
void Board<Type>::displayBoard()
{
    cout << "Displaying the board: Each cell is shown as tuple (CURRENT OWNER ID, VALUE):" << endl;
    cout << "        ";
    for (int i=0; i < cols; i++)
    {
        cout << i << "       ";
        if (matrix[0][1] == -1)
            cout << " "; // to prevent position change (-1 and -)
    }
    cout << endl;
    
    for (int i=0; i<rows; i++)
    {
        cout << i << "       ";
        for (int j=0; j<cols*2; j++)
        {
            if (j%2 == 0)
                cout << "(" << matrix[i][j] << ",";
            else
                cout << matrix[i][j] << ")   ";
        }
        cout << endl;
    }
}

template <class Type> // Gives "value" for every cells that owned by that player
void Board<Type>::updateBoardCells(int playerId, Type value)
{
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols*2; j++)
        {
            if (matrix[i][j] == playerId || matrix[i][j] == playerId+48)
                matrix[i][j+1] = value;
            j++;
        }
    }
}

template <class Type> // Calculates how many cells that "player" owns
int Board<Type>::getPlayerCellsCount(int playerId)
{
    int count = 0;
    for (int i=0; i<rows; i++)
    {
        for (int j=0; j<cols*2; j++)
        {
            if (matrix[i][j] == playerId || matrix[i][j] == playerId+48)
                count++;
            j++;
        }
    }
    return count;
}

template <class Type> // Returns the player that owns the cell at given indices
Type Board<Type>::knowTheOwner(int i, int j)
{
    return matrix[i][j*2];
}

template <class Type> // used in updateCell to change the id and value of given cell
void Board<Type>::update(int i, int j, Type value, int no, bool& isChange)
{
    if (matrix[i][2*j] == 0)
    {
        isChange = true;
        matrix[i][2*j] = no;
        matrix[i][2*j+1] = value;
    }
    else if (matrix[i][2*j] == '0')
    {
        isChange = true;
        matrix[i][2*j] = no+48;
        matrix[i][2*j+1] = value;
    }
}

template<class Type> // used in updateMyCells to change the value of all cells that player owns
void Board<Type>::updateAll(int playerId, Type value)
{
    for (int i=0; i < rows; i++)
    {
        for (int j=0; j < cols*2; j++)
        {
            if (matrix[i][j] == playerId || matrix[i][j] == playerId+48)
                matrix[i][j+1] = value;
            j++;
        }
    }
}

template<class Type> // used in unclaimOwnership to change id of given cell to zero
void Board<Type>::unclaim(int i, int j, int playerId, bool& isUnc)
{
    if (matrix[i][j*2] == playerId)
        matrix[i][j*2] = 0;
    else if (matrix[i][j*2] == playerId+48)
        matrix[i][j*2] = '0';
    else
        isUnc = false;
}

template<class Type> // used in unclaimOwnerships to make 0 all id's of cells (given player owns)
void Board<Type>::unclaimAll(int playerId)
{
    for (int i=0; i < rows; i++)
    {
        for (int j=0; j < cols*2; j++)
        {
            if (matrix[i][j] == playerId)
                matrix[i][j] = 0;
            else if (matrix[i][j] == playerId+48)
                matrix[i][j] = '0';
            j++;
        }
    }
}
