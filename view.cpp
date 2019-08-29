#include "view.h"
#include "cellwidget.h"
#include <QWidget>
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

void View::paintGrid()
{
	while (!grid_layout->isEmpty())
	{
		auto *item = grid_layout->takeAt(0);
		delete item->widget();
		delete item;
	}

	std::vector<std::vector<MineSweeper::Index>> grid = game->getGrid();

	for (unsigned int i = 0; i < grid.size(); ++i)
		for (unsigned int j = 0; j < grid[0].size(); ++j)
		{
			CellWidget *cell = new CellWidget(grid[i][j]);

			grid_layout->addWidget(cell,
								   static_cast<int>(i),
								   static_cast<int>(j));

			connect(cell, &CellWidget::clicked,
					game, [this, cell]()
			{
				game->click(cell->getCell());
			});

			connect(cell, &CellWidget::rightClicked,
					game, [this, cell]()
			{
				game->switchFlag(cell->getCell());
			});
		}

	connect(game, &MineSweeper::change,
			this, [this](const MineSweeper::Index & i)
	{
		qobject_cast<CellWidget *>(grid_layout->
								   itemAtPosition(i.row(), i.column())->
								   widget())->update();
	});
}

View::View(QWidget *parent):
	QMainWindow(parent),
	game(nullptr),
	grid_layout(new QGridLayout)
{
	setWindowFlags(windowFlags() | Qt::MSWindowsFixedSizeDialogHint);
	QWidget *main_widget = new QWidget;
	QVBoxLayout *main_layout = new QVBoxLayout;
	QHBoxLayout *head_layout = new QHBoxLayout;
	QHBoxLayout *centrate_grid_layout = new QHBoxLayout;
	main_layout->addLayout(head_layout);
	main_layout->addLayout(centrate_grid_layout);
	main_layout->addStretch();

	centrate_grid_layout->addStretch(1);
	centrate_grid_layout->addLayout(grid_layout);
	centrate_grid_layout->addStretch(1);

	main_widget->setLayout(main_layout);
	setCentralWidget(main_widget);
	layout()->setSizeConstraint(QLayout::SetFixedSize);
	grid_layout->setSizeConstraint(QLayout::SetFixedSize);

	grid_layout->setSpacing(1);

	//Menu
	QMenu *file = new QMenu("File");
	QAction *menu_new_game = new QAction("New Game");
	QMenu *options = new QMenu("Options");

	QActionGroup *difficulty = new QActionGroup(options);
	QAction *easy = new QAction("Easy", difficulty);
	easy->setCheckable(true);
	easy->setChecked(true);
	QAction *intermediate = new QAction("Intermediate", difficulty);
	intermediate->setCheckable(true);
	QAction *hard = new QAction("Hard", difficulty);
	hard->setCheckable(true);

	QAction *exit = new QAction("Exit");

	menuBar()->addMenu(file);
	file->addAction(menu_new_game);
	file->addSeparator();
	file->addMenu(options);
	options->addAction(easy);
	options->addAction(intermediate);
	options->addAction(hard);
	file->addSeparator();
	file->addAction(exit);

	//Head Bar
	QPushButton *smile_button = new QPushButton(QIcon(":/icon/default"),
			"");
	QLCDNumber *bomb_screen = new QLCDNumber();
	QLCDNumber *time_screen = new QLCDNumber();
	QTimer *timer = new QTimer(time_screen);
	head_layout->addWidget(bomb_screen);
	head_layout->addStretch();
	head_layout->addWidget(smile_button);
	head_layout->addStretch();
	head_layout->addWidget(time_screen);

	//connects for menu and head bar
	connect(menu_new_game, &QAction::triggered,
			smile_button, &QPushButton::clicked);

	connect(difficulty, &QActionGroup::triggered,
			smile_button, &QPushButton::clicked);

	connect(exit, &QAction::triggered,
			this, &View::close);

	connect(smile_button, &QPushButton::clicked,
			timer, [timer]()
	{
		timer->start(1000);
	});

	connect(smile_button, &QPushButton::clicked,
			time_screen, [time_screen]()
	{
		time_screen->display(0);
	});

	connect(timer, &QTimer::timeout,
			time_screen, [time_screen]()
	{
		time_screen->display(time_screen->value() + 1);
	});

	connect(smile_button, &QPushButton::clicked,
			this, [this, difficulty, smile_button, timer, bomb_screen]()
	{
		delete game;

		if (difficulty->checkedAction()->text() == "Easy")
			game = new MineSweeper(MineSweeper::Easy, this);
		else if (difficulty->checkedAction()->text() == "Intermediate")
			game = new MineSweeper(MineSweeper::Intermediate, this);
		else if (difficulty->checkedAction()->text() == "Hard")
			game = new MineSweeper(MineSweeper::Hard, this);

		bomb_screen->display(game->getBombs());

		connect(game, &MineSweeper::gameOver,
				smile_button, [smile_button, timer]()
		{
			timer->stop();
			smile_button->setIcon(QIcon(":/icon/lose"));
		});

		connect(game, &MineSweeper::youWon,
				smile_button, [smile_button, timer]()
		{
			timer->stop();
			smile_button->setIcon(QIcon(":/icon/win"));
		});

		connect(game, &MineSweeper::change,
				this, [this, bomb_screen]()
		{
			if (game->getBombs() != static_cast<int>(bomb_screen->value()))
				bomb_screen->display(game->getBombs());
		});

		paintGrid();
	});

	connect(smile_button, &QPushButton::pressed,
			smile_button, [smile_button]()
	{
		smile_button->setIcon(QIcon(":/icon/click"));
	});

	connect(smile_button, &QPushButton::released,
			smile_button, [smile_button]()
	{
		smile_button->setIcon(QIcon(":/icon/default"));
	});

	emit smile_button->clicked();
}

QSize View::sizeHint() const
{
	return {0, 0};
}
