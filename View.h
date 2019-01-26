#ifndef VIEW_H
#define VIEW_H

#include <QWidget>
#include <QGraphicsScene>

class Control;

class View : public QWidget
{
	Q_OBJECT
private:
	Control *control;
	QGraphicsScene *grid;
public:
	View(QWidget *parent = nullptr);
	void paintGrid(unsigned int width, unsigned int height);

signals:

public slots:
};

#endif // VIEW_H
