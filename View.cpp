#include "View.h"
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QPushButton>
#include <QToolBar>

View::View(Control *cont, QWidget *parent):
    QWidget(parent),
    control(cont),
    window(new QMainWindow(this))
{
    window->setWindowTitle("MineSweeper");
    window->setCentralWidget(new QWidget(window));

    QMenu *file = new QMenu(window->menuBar());
    QAction *exit = new QAction("Exit", file);

    window->menuBar()->addMenu(file);
    file->addAction(exit);

    QToolBar *tool_bar = new QToolBar(window);
    QAction *new_game = new QAction("New Game", tool_bar);

    window->addToolBar(tool_bar);
    tool_bar->addAction(new_game);
}
/*
void View::show()
{
    window->show();
}*/
