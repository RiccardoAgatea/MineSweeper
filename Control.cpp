#include "Control.h"
#include "MineSweeper.h"
#include "View.h"

Control::Control(QWidget *parent):
    QWidget(parent),
    mine_sweeper(nullptr),
    view(new View(this, this))
{

}
