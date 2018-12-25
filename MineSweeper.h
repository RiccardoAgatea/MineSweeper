#ifndef MINESWEEPER_H
#define MINESWEEPER_H
#include <random>
#include <iostream>

class MineSweeper
{
public:
    enum Difficulty : char {E = 'e', I = 'i', H = 'h'};
private:
    class Cell
    {
    public:
        short int surrounding_bombs;
        bool clicked;
        bool flag;

        Cell();
        void addBomb();
    };

    const Difficulty dif;
    const unsigned int width, height;
    const unsigned int bombs;
    Cell *grid;
    unsigned int flags, unclicked_cells;
    bool winning;
    std::uniform_int_distribution<unsigned int> BOMB;

    static std::default_random_engine gen;
    static unsigned int widthFromDif(Difficulty);
    static unsigned int heightFromDif(Difficulty);
    static unsigned int bombsFromDif(Difficulty);

    void gameOver();
public:
    explicit MineSweeper(Difficulty);
    MineSweeper(const MineSweeper &) = delete;
    ~MineSweeper();
    MineSweeper &operator=(const MineSweeper &) = delete;
    void clickAt(unsigned int, unsigned int);
    void doubleClickAt(unsigned int, unsigned int);
    void switchFlagAt(unsigned int, unsigned int);
    bool isGameFinished() const;
    bool isGameWon() const;
    unsigned char whatIsAt(unsigned int, unsigned int) const;
    friend std::ostream &operator<<(std::ostream &, const MineSweeper &);
};

#endif // MINESWEEPER_H
