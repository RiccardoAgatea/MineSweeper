#include "MineSweeper.h"

#include <ctime>
#include <iostream>

std::default_random_engine MineSweeper::gen(static_cast<unsigned int>(time(nullptr)));

unsigned int MineSweeper::widthFromDif(Difficulty d)
{
    switch (d)
    {
    case E:
        return 8;

    case I:
        return 16;

    case H:
        return 30;
    }

    return 0;
}

unsigned int MineSweeper::heightFromDif(Difficulty d)
{
    switch (d)
    {
    case E:
        return 13;

    case I:
        return 16;

    case H:
        return 16;
    }

    return 0;
}

unsigned int MineSweeper::bombsFromDif(Difficulty d)
{
    switch (d)
    {
    case E:
        return 10;

    case I:
        return 39;

    case H:
        return 87;
    }

    return 0;
}

MineSweeper::Cell::Cell():
    surrounding_bombs(0),
    clicked(false),
    flag(false)
{

}

void MineSweeper::Cell::addBomb()
{
    //PRE=!clicked && !flag
    if (surrounding_bombs != -1)
        ++surrounding_bombs;
}

MineSweeper::MineSweeper(Difficulty d):
    dif(d),
    width(widthFromDif(d)),
    height(heightFromDif(d)),
    bombs(bombsFromDif(d)),
    grid(new Cell[width * height]),
    flags(0),
    unclicked_cells(width * height),
    winning(true),
    BOMB(0, width * height - 1)
{
    for (unsigned int k = 0; k < bombs; ++k)
    {
        unsigned int i = 0, j = 0;

        {
            unsigned int bomb_place = BOMB(gen);
            i = bomb_place / width;
            j = bomb_place % width;
        }

        if (grid[i * width + j].surrounding_bombs != -1)
        {
            grid[i * width + j].surrounding_bombs = -1;

            if ((i >= 1) && (j >= 1))
                grid[(i - 1) * width + j - 1].addBomb();

            if (i >= 1)
                grid[(i - 1) * width + j].addBomb();

            if ((i >= 1) && (j < width - 1))
                grid[(i - 1) * width + j + 1].addBomb();

            if (j >= 1)
                grid[i * width + j - 1].addBomb();

            if (j < width - 1)
                grid[i * width + j + 1].addBomb();

            if ((i < height - 1) && (j >= 1))
                grid[(i + 1) * width + j - 1].addBomb();

            if (i < height - 1)
                grid[(i + 1) * width + j].addBomb();

            if ((i < height - 1) && (j < width - 1))
                grid[(i + 1) * width + j + 1].addBomb();
        }
        else
            --k;
    }
}

MineSweeper::~MineSweeper()
{
    delete[] grid;
}

void MineSweeper::gameOver()
{
    winning = false;
}

void MineSweeper::clickAt(unsigned int i, unsigned int j)
{
    if (i >= height || j >= width) //i,j>=0 becuase of type unsigned
        return; //throw "Out of bounds";

    if (winning && !grid[i * width + j].flag && !grid[i * width + j].clicked)
    {
        --unclicked_cells;
        grid[i * width + j].clicked = true;

        if (grid[i * width + j].surrounding_bombs == -1)
            gameOver();
        else if (grid[i * width + j].surrounding_bombs == 0)
        {
            if ((i >= 1) && (j >= 1))
                clickAt(i - 1, j - 1);

            if (i >= 1)
                clickAt(i - 1, j);

            if ((i >= 1) && (j < width - 1))
                clickAt(i - 1, j + 1);

            if (j >= 1)
                clickAt(i, j - 1);

            if (j < width - 1)
                clickAt(i, j + 1);

            if ((i < height - 1) && (j >= 1))
                clickAt(i + 1, j - 1);

            if (i < height - 1)
                clickAt(i + 1, j);

            if ((i < height - 1) && (j < width - 1))
                clickAt(i + 1, j + 1);
        }
    }
}

void MineSweeper::doubleClickAt(unsigned int i, unsigned int j)
{
    if (i >= height || j >= width) //i,j>=0 becuase of type unsigned
        return; //throw "Out of bounds";

    if (grid[i * width + j].clicked && grid[i * width + j].surrounding_bombs != 0)
    {
        unsigned int surrounding_flags = 0;

        if ((i >= 1) && (j >= 1) && grid[(i - 1) * width + j - 1].flag)
            ++surrounding_flags;

        if (i >= 1 && grid[(i - 1) * width + j].flag)
            ++surrounding_flags;

        if ((i >= 1) && (j < width - 1) && grid[(i - 1) * width + j + 1].flag)
            ++surrounding_flags;

        if (j >= 1 && grid[i * width + j - 1].flag)
            ++surrounding_flags;

        if (j < width - 1 && grid[i * width + j + 1].flag)
            ++surrounding_flags;

        if ((i < height - 1) && (j >= 1) && grid[(i + 1) * width + j - 1].flag)
            ++surrounding_flags;

        if (i < height - 1 && grid[(i + 1) * width + j].flag)
            ++surrounding_flags;

        if ((i < height - 1) && (j < width - 1) && grid[(i + 1) * width + j + 1].flag)
            ++surrounding_flags;

        if (surrounding_flags == static_cast<unsigned int>(grid[i * width + j].surrounding_bombs))
        {
            if ((i >= 1) && (j >= 1))
                clickAt(i - 1, j - 1);

            if (i >= 1)
                clickAt(i - 1, j);

            if ((i >= 1) && (j < width - 1))
                clickAt(i - 1, j + 1);

            if (j >= 1)
                clickAt(i, j - 1);

            if (j < width - 1)
                clickAt(i, j + 1);

            if ((i < height - 1) && (j >= 1))
                clickAt(i + 1, j - 1);

            if (i < height - 1)
                clickAt(i + 1, j);

            if ((i < height - 1) && (j < width - 1))
                clickAt(i + 1, j + 1);
        }
    }
}

void MineSweeper::switchFlagAt(unsigned int i, unsigned int j)
{
    if (winning & !grid[i * width + j].clicked)
    {
        if (!grid[i * width + j].flag)
        {
            grid[i * width + j].flag = true;
            ++flags;
        }
        else
        {
            grid[i * width + j].flag = false;
            --flags;
        }
    }
}

bool MineSweeper::isGameFinished() const
{
    //game has finished <=> !winning || all the unclicked cells are bombs
    return !winning || (unclicked_cells == bombs);
}

bool MineSweeper::isGameWon() const
{
    //game is won <=> winning && all the unclicked cells are bombs
    //winning is necessary, because if unclicked_cells == bombs, but one of the unclicked
    //	cells is not a bomb (which means a bomb has been clicked), the game is lost,
    //	so winning is false
    return winning && (unclicked_cells == bombs);
}

unsigned char MineSweeper::whatIsAt(unsigned int i, unsigned int j) const
{

    if (i >= height || j >= width) //i,j>=0 becuase of type unsigned
        return 19; //throw "Out of bounds";

    if (!winning) //game lost
    {
        if (grid[i * width + j].flag)
            return static_cast<unsigned char>(245);
        else if (grid[i * width + j].surrounding_bombs == -1)
        {
            if (grid[i * width + j].clicked)
                return '#';
            else
                return '*';
        }
        else if (grid[i * width + j].surrounding_bombs == 0)
            return ' ';
        else
            return static_cast<unsigned char>(grid[i * width + j].surrounding_bombs + 48);
    }
    else if (unclicked_cells == bombs) //game won
    {
        if (grid[i * width + j].flag)
            return 245;
        else if (grid[i * width + j].surrounding_bombs == -1)
            return '@';
        else if (grid[i * width + j].surrounding_bombs == 0)
            return ' ';
        else
            return static_cast<unsigned char>(grid[i * width + j].surrounding_bombs + 48);
    }
    else
    {
        if (grid[i * width + j].flag)
            return 245;
        else if (!grid[i * width + j].clicked)
            return 219; //a solid block
        else if (grid[i * width + j].surrounding_bombs == 0)
            return ' ';
        else
            //digits have an offset in the ASCII table
            return static_cast<unsigned char>(grid[i * width + j].surrounding_bombs + 48);
    }
}

std::ostream &operator<<(std::ostream &os, const MineSweeper &m)
{
    using std::endl;
    os << ' ' << ' ' << ' ';

    for (unsigned int i = 0; i < m.width; ++i)
    {
        if (i < 10)
            os << ' ';

        os << ' ' << i;
    }

    os << endl;

    for (unsigned int i = 0; i < m.height; ++i)
    {
        if (i < 10)
            os << ' ';

        os << ' ' << i;

        for (unsigned int j = 0; j < m.width; ++j)
            os << ' ' << ' ' << m.whatIsAt(i, j);

        os << endl << endl;
    }

    return os;
}
