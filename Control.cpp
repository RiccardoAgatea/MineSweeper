#include "Control.h"
#include "MineSweeper.h"
#include "View.h"

Control::Control(View *parent):
    QWidget(parent),
    mine_sweeper(nullptr),
    view(parent)
{

}

void Control::newGame(const QString &difficulty)
{
    delete mine_sweeper;

    if (difficulty == "Easy")
        mine_sweeper = new MineSweeper(MineSweeper::Difficulty::E);
    else if (difficulty == "Intermediate")
        mine_sweeper = new MineSweeper(MineSweeper::Difficulty::I);
    else if (difficulty == "Hard")
        mine_sweeper = new MineSweeper(MineSweeper::Difficulty::H);

    MineSweeper::BoardSize size = mine_sweeper->getBoardSize();
    view->paintGrid(size.width, size.height);
}
