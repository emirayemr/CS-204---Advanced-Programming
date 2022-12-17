/* Emir Ay
 date created: 18/05/2022
 date finished: 25/05/2022
 I used both xCode and Visual Studio for coding homework6.
 As far as I know, it runs properly on VS2012. */

#include "Emiray_Ay_Emir_hw6_Board.h"

#ifndef Emiray_Ay_Emir_hw6_Player_h
#define Emiray_Ay_Emir_hw6_Player_h

template <class Type>
class Player
{
private:
    Board<Type> & myBoard;
    int playerId;
    static int next_id;
    
public:
    Player(Board<Type>& b);
    bool updateCell(int i, int j, Type value);
    void updateMyCells(Type value);
    bool unclaimOwnership(int i, int j);
    void unclaimOwnerships();
};

template <class Type> // Static data member
int Player<Type>::next_id = 1;

#include "Emiray_Ay_Emir_hw6_Player.cpp"

#endif
