#include "View.h"
#include "Control.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QActionGroup>
#include <QPushButton>
#include <QToolBar>
#include <QTimer>
#include <QLCDNumber>
#include <QGraphicsView>

View::View(QWidget *parent):
	QWidget(parent),
	control(new Control(this)),
	grid(new QGraphicsScene(this))
{
	QGraphicsView *grid_view = new QGraphicsView(grid, this);

	QVBoxLayout *main_layout = new QVBoxLayout(this);
	QHBoxLayout *head_layout = new QHBoxLayout();
	main_layout->addLayout(head_layout);
	main_layout->addWidget(grid_view);
	main_layout->addStretch();

	//Menu
	QMenuBar *menu_bar = new QMenuBar();
	QMenu *file = new QMenu("File");
	QAction *menu_new_game = new QAction("New Game");
	QMenu *options = new QMenu("Options");

	QActionGroup *difficulty = new QActionGroup(file);
	QAction *easy = new QAction("Easy", difficulty);
	easy->setCheckable(true);
	easy->setChecked(true);
	QAction *intermediate = new QAction("Intermediate", difficulty);
	intermediate->setCheckable(true);
	QAction *hard = new QAction("Hard", difficulty);
	hard->setCheckable(true);

	QAction *exit = new QAction("Exit");

	layout()->setMenuBar(menu_bar);
	menu_bar->addMenu(file);
	file->addAction(menu_new_game);
	file->addSeparator();
	file->addMenu(options);
	options->addAction(easy);
	options->addAction(intermediate);
	options->addAction(hard);
	file->addSeparator();
	file->addAction(exit);

	//Head Bar
	QPushButton *new_game = new QPushButton("New Game");
	QLCDNumber *bomb_screen = new QLCDNumber();
	QLCDNumber *time_screen = new QLCDNumber();
	QTimer *timer = new QTimer(time_screen);
	head_layout->addWidget(bomb_screen);
	head_layout->addStretch();
	head_layout->addWidget(new_game);
	head_layout->addStretch();
	head_layout->addWidget(time_screen);

	//connects for menu and head bar
	connect(menu_new_game, &QAction::triggered,
			new_game, &QPushButton::clicked);

	connect(difficulty, &QActionGroup::triggered,
			new_game, &QPushButton::clicked);

	connect(exit, &QAction::triggered,
			this, &View::close);

	connect(new_game, &QPushButton::clicked,
			timer, [timer]()
	{
		timer->start(1000);
	});

	connect(new_game, &QPushButton::clicked,
			time_screen, [time_screen]()
	{
		time_screen->display(0);
	});

	connect(new_game, &QPushButton::clicked,
			control, [this, options]()
	{
		foreach (const QAction *a, options->actions())
			if (a->isChecked())
				control->newGame(a->text());
	});

	connect(timer, &QTimer::timeout,
			time_screen, [time_screen]()
	{
		time_screen->display(time_screen->value() + 1);
	});

	emit new_game->clicked();
}

void View::paintGrid(unsigned int width, unsigned int height)
{

}
