/* Emir Ay
 date created: 18/05/2022
 date finished: 25/05/2022
 I used both xCode and Visual Studio for coding homework6.
 As far as I know, it runs properly on VS2012. */

#ifndef Emiray_Ay_Emir_hw6_Board_h
#define Emiray_Ay_Emir_hw6_Board_h

template <class Type>
class Board
{
private:
    Type** matrix;
    int rows;
    int cols;
    
public:
    Board(int row, int col);
    Board(const Board &);
    ~Board();
    Type** createClone() const;
    void displayBoard();
    void updateBoardCells(int playerId, Type value);
    int getPlayerCellsCount (int playerId);
    void update(int i, int j, Type value, int no, bool& isChange);
    void updateAll(int playerId, Type value);
    void unclaim(int i, int j, int playerId, bool& isUnc);
    void unclaimAll(int playerId);
    Type knowTheOwner(int i, int j);
};

#include "Emiray_Ay_Emir_hw6_Board.cpp"

#endif
