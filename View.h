#ifndef VIEW_H
#define VIEW_H

#include <QMainWindow>
#include <QGridLayout>
#include "MineSweeper.h"

class View: public QMainWindow
{
	Q_OBJECT
private:
	MineSweeper *game;
	QGridLayout *grid_layout;

	void paintGrid();

public:
	View(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // VIEW_H
