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
	};
	class Index
	{
		friend class MineSweeper;
	private:
		unsigned int i, j;
		Index(unsigned int row, unsigned int column);
	};

	explicit MineSweeper(Difficulty d, QObject *parent = nullptr);
	std::vector<std::vector<Index>> getGrid() const;
	Cell &getCell(const Index &i);

signals:
	void change(const Index &);
	void gameOver();
	void youWon();

public slots:
	void click(const Index &i);
	void doubleClick(const Index &i);
	void swtichFlag(const Index &i);
};

#endif // MINESWEEPER_H
