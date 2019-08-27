#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QMainWindow>
#include <QGridLayout>
#include "MineSweeper.h"

class View: public QMainWindow
{
	Q_OBJECT
private:
	class Cell: public QFrame
	{
		Q_OBJECT
	private:
		const MineSweeper::Position &pos;

	protected:
		virtual void mousePressEvent(QMouseEvent *event) override;
		virtual void mouseReleaseEvent(QMouseEvent *event) override;

	public:
		Cell(const MineSweeper::Position &p);
	};

	MineSweeper *game;
	QGridLayout *grid_layout;

	void paintGrid();

public:
	View(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // VIEW_H
