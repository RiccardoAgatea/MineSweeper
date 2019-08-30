#include "cellwidget.h"
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QPixmap>

void CellWidget::mousePressEvent(QMouseEvent *event)
{
	if (!cell->isClicked() &&
			!cell->isFlagged() &&
			event->button() == Qt::LeftButton)
		setFrameShadow(QFrame::Sunken);

	QFrame::mousePressEvent(event);
}

void CellWidget::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->type() == QEvent::MouseButtonRelease)
	{
		if (event->button() == Qt::LeftButton)
			emit clicked();
		else if (event->button() == Qt::RightButton)
			emit rightClicked();
	}
	else if (event->type() == QEvent::MouseButtonDblClick &&
			 event->button() == Qt::LeftButton)
		emit doubleClicked();

	QFrame::mouseReleaseEvent(event);
}

CellWidget::CellWidget(const MineSweeper::Index &c, QWidget *parent):
	QFrame(parent),
	cell(c),
	icon(new QLabel)
{
	setFrameStyle(QFrame::Panel | QFrame::Raised);
	setLineWidth(2);
	setMidLineWidth(0);
	setMaximumSize(sizeHint());
	setMinimumSize(sizeHint());

	QHBoxLayout *layout = new QHBoxLayout;
	layout->addWidget(icon);
	layout->setContentsMargins(0, 0, 0, 0);
	//layout->setSizeConstraint(QLayout::SetFixedSize);
	setLayout(layout);

	icon->setMinimumSize({15, 15});
	icon->setMaximumSize({15, 15});
}

QSize CellWidget::sizeHint() const
{
	return {20, 20};
}

MineSweeper::Index CellWidget::getCell() const
{
	return cell;
}

void CellWidget::update()
{
	if (!cell->isClicked())
	{
		setFrameStyle(QFrame::Panel | QFrame::Raised);

		if (cell->isFlagged())
			icon->setPixmap(QPixmap(":/icon/flag").scaled({15, 15}));
		else
			icon->setPixmap(QPixmap());
	}
	else
	{
		setFrameStyle(QFrame::Panel | QFrame::Sunken);

		if (cell->isBomb())
			icon->setPixmap(QPixmap(":/icon/explod").scaled({15, 15}));
		else if (cell->getSurroundingBombs() != 0)
			icon->setPixmap(
				QPixmap(":/numbers/" +
						QString::number(cell->getSurroundingBombs()))
				.scaled({15, 15}));
	}

}
