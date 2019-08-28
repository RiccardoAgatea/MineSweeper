#ifndef CELLWIDGET_H
#define CELLWIDGET_H

#include <QFrame>
#include "MineSweeper.h"

class CellWidget: public QFrame
{
	Q_OBJECT
private:
	MineSweeper::Index cell;

protected:
	virtual void mousePressEvent(QMouseEvent *event) override;
	virtual void mouseReleaseEvent(QMouseEvent *event) override;

public:
	explicit CellWidget(const MineSweeper::Index &c,
						QWidget *parent = nullptr);
	virtual QSize sizeHint() const override;

signals:

public slots:
	void update();
};

#endif // CELLWIDGET_H
