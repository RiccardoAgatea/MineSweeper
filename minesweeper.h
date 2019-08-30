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

	class Cell;
private:
	struct GameSize
	{
		unsigned int width, height;
		int bombs;
	};

	std::vector<std::vector<Cell>> grid;
	int bombs;

	static GameSize getGameSize(Difficulty d);
public:
	class Cell
	{
		friend class MineSweeper;
	private:
		bool clicked, flagged, bomb;
		unsigned int surrounding_bombs;
	public:
		Cell();
		bool isClicked() const;
		bool isFlagged() const;
		bool isBomb() const;
		unsigned int getSurroundingBombs() const;
	};

	class Index
	{
		friend class MineSweeper;
	private:
		std::vector<std::vector<Cell>> &grid;
		unsigned int i, j;
		Index(std::vector<std::vector<Cell>> &g,
			  unsigned int row,
			  unsigned int column);
	public:
		Cell &operator*() const;
		Cell *operator->() const;
		unsigned int row() const;
		unsigned int column() const;
	};

	explicit MineSweeper(Difficulty d, QObject *parent = nullptr);
	std::vector<std::vector<Index>> getGrid();
	int getBombs() const;
	Cell &getCell(const Index &i);

signals:
	void change(const Index &);
	void gameOver();
	void youWon();

public slots:
	void click(const Index &i);
	void doubleClick(const Index &i);
	void switchFlag(const Index &i);
};

#endif // MINESWEEPER_H
