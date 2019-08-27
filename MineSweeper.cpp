#include "MineSweeper.h"

MineSweeper::GameSize MineSweeper::getGameSize(MineSweeper::Difficulty
        d)
{
	switch (d)
	{
	case Easy:
		return {8, 13, 10};
	case Intermediate:
		return {16, 16, 39};
	case Hard:
		return {30, 16, 87};
	}

	return {0, 0, 0};
}

MineSweeper::MineSweeper(Difficulty d, QObject *parent):
	QObject(parent)
{
	GameSize g = getGameSize(d);

	grid = std::vector<std::vector<Cell>>(g.height,
	                                      std::vector<Cell>(g.width));
	bombs = g.bombs;
}

void MineSweeper::click(const Position &p)
{
	if (
	    p.i >= 0 &&
	    p.getUI() < grid.size() &&
	    p.j >= 0 &&
	    p.getUJ() < grid[0].size()
	)
	{
		Cell &c = grid
		          [p.getUI()]
		          [p.getUJ()];

		if (c.isClicked() || c.isFlagged())
			return;

		c.click();

		if (c.isBomb())
			emit gameOver();
		else
			emit clicked(p);

		if (c.surrounding_bombs == 0)
		{
			click({p.i - 1, p.j - 1});
			click({p.i - 1, p.j});
			click({p.i - 1, p.j + 1});
			click({p.i, p.j - 1});
			click({p.i, p.j + 1});
			click({p.i + 1, p.j - 1});
			click({p.i + 1, p.j});
			click({p.i + 1, p.j + 1});
		}
	}
}

void MineSweeper::doubleClick(const MineSweeper::Position &p)
{
	if (
	    p.i >= 0 &&
	    p.getUI() < grid.size() &&
	    p.j >= 0 &&
	    p.getUJ() < grid[0].size()
	)
	{
		Cell &c = grid
		          [p.getUI()]
		          [p.getUJ()];

		unsigned int surrounding_flags = 0;

		std::vector<unsigned int> i_range, j_range;

		if (p.i > 0)
			i_range.push_back(p.getUI() - 1);

		i_range.push_back(p.getUI());

		if (p.getUI() < grid.size() - 1)
			i_range.push_back(p.getUI() + 1);

		if (p.j > 0)
			j_range.push_back(p.getUJ() - 1);

		j_range.push_back(p.getUJ());

		if (p.getUJ() < grid[0].size() - 1)
			j_range.push_back(p.getUJ() + 1);

		for (auto i : i_range)
			for (auto j : j_range)
				if (
					!(i == p.getUI() && j == p.getUJ()) &&
					grid[i][j].isFlagged()
				)
					++surrounding_flags;

		if (surrounding_flags == c.surrounding_bombs)
		{
			click({p.i - 1, p.j - 1});
			click({p.i - 1, p.j});
			click({p.i - 1, p.j + 1});
			click({p.i, p.j - 1});
			click({p.i, p.j + 1});
			click({p.i + 1, p.j - 1});
			click({p.i + 1, p.j});
			click({p.i + 1, p.j + 1});
		}
	}
}

void MineSweeper::swichFlag(const MineSweeper::Position &p)
{
	if (
	    p.i >= 0 &&
	    p.getUI() < grid.size() &&
	    p.j >= 0 &&
	    p.getUJ() < grid[0].size()
	)
	{
		Cell &c = grid
		          [p.getUI()]
		          [p.getUJ()];

		if (!c.isFlagged())
		{
			c.setFlag(true);
			--bombs;

			emit flagged(p, true);
		}
		else
		{
			c.setFlag(false);
			++bombs;

			emit flagged(p, false);
		}
	}
}

MineSweeper::Cell::Cell():
	flags(0),
	surrounding_bombs(0)
{

}

bool MineSweeper::Cell::isClicked() const
{
	return (flags / Cell::Clicked) % 2 == 1;
}

void MineSweeper::Cell::click()
{
	if (!isClicked())
		flags |= Cell::Clicked;
}

bool MineSweeper::Cell::isFlagged() const
{
	return (flags / Cell::Flagged) % 2 == 1;
}

void MineSweeper::Cell::setFlag(bool f)
{
	if (isFlagged() && !f)
		flags &= ~Cell::Flagged;
	else if (!isFlagged() && f)
		flags |= Cell::Flagged;
}

bool MineSweeper::Cell::isBomb() const
{
	return (flags / Cell::Bomb) % 2 == 1;
}

void MineSweeper::Cell::setBomb()
{
	flags |= Cell::Bomb;
}

unsigned int MineSweeper::Position::getUI() const
{
	return static_cast<unsigned int>(i);
}

unsigned int MineSweeper::Position::getUJ() const
{
	return static_cast<unsigned int>(j);
}
