/* Emir Ay
 date created: 18/05/2022
 date finished: 25/05/2022
 I used both xCode and Visual Studio for coding homework6.
 As far as I know, it runs properly on VS2012. */

#include <iostream>
#include "Emiray_Ay_Emir_hw6_Player.h"
using namespace std;

template <class Type> // Parametric Constructor
Player<Type>::Player (Board<Type>& b)
    :myBoard(b)
{
    playerId = 0;
    playerId = next_id;
    next_id++;
        // static data member provides to get id of the player every time it called
}

template <class Type> // changes the value of given cell as "value"
bool Player<Type>::updateCell(int i, int j, Type value)
{
    bool isChange = false;
    myBoard.update(i, j, value, playerId, isChange);
    
    return isChange;
}

template <class Type> // Changes all values of the cells the player owns as "value"
void Player<Type>::updateMyCells(Type value)
{
    myBoard.updateAll(playerId, value);
}

template <class Type> // Changes the id of given cell as 0
bool Player<Type>::unclaimOwnership(int i, int j)
{
    bool isUnc = true;
    myBoard.unclaim(i, j, playerId, isUnc);
    
    return isUnc;
}

template <class Type> // Changes the id of all cells the player owns as 0
void Player<Type>::unclaimOwnerships()
{
    myBoard.unclaimAll(playerId);
}
