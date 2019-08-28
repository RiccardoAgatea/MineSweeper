#include "cellwidget.h"

void CellWidget::mousePressEvent(QMouseEvent *event)
{
	QFrame::mousePressEvent(event);
}

void CellWidget::mouseReleaseEvent(QMouseEvent *event)
{
	QFrame::mouseReleaseEvent(event);
}

CellWidget::CellWidget(const MineSweeper::Index &c, QWidget *parent):
	QFrame(parent),
	cell(c)
{
	setFrameStyle(QFrame::Panel | QFrame::Raised);
	setMaximumSize(sizeHint());
	setMinimumSize(sizeHint());
}

QSize CellWidget::sizeHint() const
{
	return {20, 20};
}

void CellWidget::update()
{

}
