#include "Game.h"
#include <time.h>

using namespace std;

int main()
{
    srand(time(0));            // for random values
    const int bsize = 10;      // stores the size of the board
    Game game(bsize);          // initialize the board
    std::vector<unsigned> pts; // stores the point played by each algorithm

    // game loop
    while (true)
    {
        // algorithm 1 playing
        pts = game.Player1();
        game.Display(); // display the results
        cout << endl;
        // ends game if find winner
        if (game.FindWinner() != 0)
        {
            cout << "player 1 won : " << game.FindWinner() << endl;
            break;
        }
        // ends game if no winner and board full
        if (game.isFull())
        {
            cout << "Draw: " << game.FindWinner() << endl;
            break;
        }
        // algorithm 1 playing
        pts = game.Player2();
        game.Display();
        cout << endl;
        if (game.FindWinner() != 0)
        {
            cout << "player 2 won : " << game.FindWinner() << endl;
            break;
        }
        if (game.isFull())
        {
            cout << "Draw: " << game.FindWinner() << endl;
            break;
        }
    }

    return 0;
}