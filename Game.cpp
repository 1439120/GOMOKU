#include "Game.h"
#include <iostream>

// the entries are -1 on the board showing unfilled boxes
Game::Game(int s)
{
    flip = true;
    for (unsigned i = 0; i < s; i++)
    {
        std::vector<entries> row;
        for (unsigned j = 0; j < s; j++)
        {
            row.push_back(entries::unfilled);
            // add the points
            avail.push_back(std::vector<unsigned>{i, j});
        }
        board_.push_back(row);
    }
}

void Game::Display()
{
    for (unsigned i = 0; i < board_.size(); i++)
    {
        for (unsigned j = 0; j < board_.size(); j++)
        {
            std::cout << board_[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

entries Game::FindWinner()
{
    if (flip)
    {
        // find out if player 1 won
        if (isWinner(entries::player1))
        {
            return entries::player1;
            flip = !flip; // change the player to check
        }
    }
    else
    {
        // find out if player 2 won
        if (isWinner(entries::player2))
        {
            return entries::player2;
            flip = !flip; // change the player to check
        }
    }

    return entries::unfilled;
}

bool Game::Checks(entries p, checks c, unsigned row, unsigned col)
{
    unsigned countRows = 0;
    unsigned countCols = 0;
    unsigned countDiag1 = 0;
    unsigned countDiag2 = 0;
    for (unsigned i = 0; i < 5; i++)
    {
        if (c == checks::rows)
        {
            if (board_[row][col + i] == p)
                countRows++;
        }
        else if (c == checks::cols)
        {
            if (board_[row + i][col] == p)
                countCols++;
        }
        else if (c == checks::diag1)
        {
            if (board_[row + i][col + i] == p)
                countDiag1++;
        }
        else
        {
            if (board_[row + i][col - i] == p && c == checks::diag2)
                countDiag2++;
        }
    }
    if (countRows >= 5 || countCols >= 5 || countDiag1 >= 5 || countDiag2 >= 5)
        return true;
    return false;
}

bool Game::isWinner(entries p)
{
    for (unsigned i = 0; i < board_.size(); i++)
    {
        for (int j = 0; j < board_.size(); j++)
        {
            // checks for the rows
            if (board_.size() - j >= 5)
            {
                if (Checks(p, checks::rows, i, j))
                    return true;
            }
            // checks for the coloms
            if (board_.size() - i >= 5)
            {
                if (Checks(p, checks::cols, i, j))
                    return true;
            }
            // checks for diagonal one
            if (board_.size() - i >= 5 && board_.size() - j >= 5)
            {
                if (Checks(p, checks::diag1, i, j))
                    return true;
            }
            // checks for diagonal two
            if (board_.size() - i >= 5 && j >= 4)
            {
                if (Checks(p, checks::diag2, i, j))
                    return true;
            }
        }
    }
    return false;
}

std::vector<unsigned> Game::Player1()
{
    // if the board is still empty
    if (player1.empty())
    {
        board_[0][0] = entries::player1;
        avail.erase(avail.begin());
        player1.push_back(std::vector<unsigned>{0, 0});
        return std::vector<unsigned>{0, 0};
    }
    else
    {
        // add the point on its next diagonal
        for (unsigned i = 0; i < player1.size(); i++)
        {
            // diagonal
            std::vector<unsigned> pts = std::vector<unsigned>{player1[player1.size() - i - 1][0], player1[player1.size() - i - 1][1]};
            pts[0] += 1;
            pts[1] += 1;
            // find out if this position is available to play
            int pos = Find(pts);
            if (pos >= 0)
            {
                board_[pts[0]][pts[1]] = entries::player1;
                avail.erase(avail.begin() + pos);
                player1.push_back(std::vector<unsigned>{pts[0], pts[1]});
                return pts;
            }
            pts[1] -= 1;
            pos = Find(pts);
            if (pos >= 0)
            {
                board_[pts[0]][pts[1]] = entries::player1;
                avail.erase(avail.begin() + pos);
                player1.push_back(std::vector<unsigned>{pts[0], pts[1]});
                return pts;
            }
            pts[0] -= 1;
            pts[1] += 1;
            pos = Find(pts);
            if (pos >= 0)
            {
                board_[pts[0]][pts[1]] = entries::player1;
                avail.erase(avail.begin() + pos);
                player1.push_back(std::vector<unsigned>{pts[0], pts[1]});
                return pts;
            }
            pts[0] -= 1;
            pts[1] -= 1;
            pos = Find(pts);
            if (pos >= 0)
            {
                board_[pts[0]][pts[1]] = entries::player1;
                avail.erase(avail.begin() + pos);
                player1.push_back(std::vector<unsigned>{pts[0], pts[1]});
                return pts;
            }
        }
        int pos = rand() % avail.size();
        std::vector<unsigned> pts = std::vector<unsigned>{avail[pos][0], avail[pos][1]};
        board_[pts[0]][pts[1]] = entries::player1;
        avail.erase(avail.begin() + pos);
        return pts;
    }
}

std::vector<unsigned> Game::Player2()
{
    // // find the potential threat
    Player1();
    if (isWinner(entries::player1))
    {
        std::vector<unsigned> pts = player1[player1.size() - 1];
        board_[pts[0]][pts[1]] = entries::player2;
        player1.pop_back();
        return pts;
    }
    else
    {
        std::vector<unsigned> pts = player1[player1.size() - 1];
        board_[pts[0]][pts[1]] = entries::unfilled;
        player1.pop_back();
        avail.push_back(pts);
    }
    // play any random position
    int pos = rand() % avail.size();
    std::vector<unsigned> pts = std::vector<unsigned>{avail[pos][0], avail[pos][1]};
    board_[pts[0]][pts[1]] = entries::player2;
    avail.erase(avail.begin() + pos);
    return pts;
}

int Game::Find(std::vector<unsigned> pts)
{
    for (unsigned i = 0; i < avail.size(); i++)
    {
        if (avail[i][0] == pts[0] && avail[i][1] == pts[1])
            return i;
    }
    return -1;
}

bool Game::isFull()
{
    if (avail.empty())
        return true;
    return false;
}