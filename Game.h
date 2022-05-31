#ifndef Game_H
#define Game_H

#include <iostream>
#include <vector>

enum entries
{
    unfilled,
    player1,
    player2
};

enum checks
{
    rows,
    cols,
    diag1,
    diag2
};

class Game
{
public:
    // Initialize game with board size provided
    Game(int);
    //Player1
    std::vector<unsigned> Player1();
    //Player2
    std::vector<unsigned> Player2();
    // returns 0 if no winner else the player who won
    entries FindWinner();
    // Display board
    void Display();
    // true if no more entries to fill
    bool isFull();

private:
    std::vector<std::vector<entries>> board_;                     // stores the board
    bool flip;                                                    // alternates to check each player at a time
    bool Checks(entries p, checks c, unsigned row, unsigned col); // functions the checks either a row/ column/ diagonal if there is five in a row
    bool isWinner(entries p);                                     // checks if this player won
    std::vector<std::vector<unsigned>> avail;                     // stores all the playable coordinates
    std::vector<std::vector<unsigned>> player1;                   // stores coordinates played by player1
    int Find(std::vector<unsigned> pts);                          // find out if the passed point is still available to play
};

#endif