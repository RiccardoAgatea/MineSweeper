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
	MineSweeper *game;
	QGridLayout *grid_layout;

	void paintGrid();

public:
	View(QWidget *parent = nullptr);

signals:

public slots:
};

//ViewCell should be a nested public class for View, but nested classes can't use the moc functionalities
class ViewCell: public QFrame
{
	Q_OBJECT
private:
	const MineSweeper::Index &pos;

protected:
	virtual void mousePressEvent(QMouseEvent *event) override;
	virtual void mouseReleaseEvent(QMouseEvent *event) override;

public:
	ViewCell(const MineSweeper::Index &p);
};

#endif // VIEW_H
