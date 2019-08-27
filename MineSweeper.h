#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QObject>
#include <vector>

class MineSweeper: public QObject
{
	Q_OBJECT
public:
	enum Difficulty
	{
		Easy,
		Intermediate,
		Hard
	};
private:
	struct Cell
	{
		enum Flags
		{
			Clicked = 1,
			Flagged = 2,
			Bomb = 4
		};

		signed char flags;
		unsigned int surrounding_bombs;

		Cell();
		bool isClicked() const;
		void click();
		bool isFlagged() const;
		void setFlag(bool f);
		bool isBomb() const;
		void setBomb();
	};

	struct GameSize
	{
		unsigned int width, height, bombs;
	};

	std::vector<std::vector<Cell>> grid;
	unsigned int bombs;

	static GameSize getGameSize(Difficulty d);
public:
	struct Position
	{
		int i, j;

		unsigned int getUI() const;
		unsigned int getUJ() const;
	};

	explicit MineSweeper(Difficulty d, QObject *parent = nullptr);

signals:
	void clicked(const Position &);
	void flagged(const Position &, bool);
	void gameOver();
	void youWon();

public slots:
	void click(const Position &p);
	void doubleClick(const Position &p);
	void swichFlag(const Position &p);
};

#endif // MINESWEEPER_H
