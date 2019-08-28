#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QMainWindow>
#include <QGridLayout>
#include "minesweeper.h"

class View: public QMainWindow
{
	Q_OBJECT
private:
	MineSweeper *game;
	QGridLayout *grid_layout;

	void paintGrid();

public:
	View(QWidget *parent = nullptr);
	virtual QSize sizeHint() const override;

signals:

public slots:
};

#endif // VIEW_H
