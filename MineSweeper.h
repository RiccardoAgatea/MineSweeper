#ifndef MINESWEEPER_H
#define MINESWEEPER_H

#include <QObject>
#include <vector>

class Cell;

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
	struct GameSize
	{
		unsigned int width, height;
		int bombs;
	};

	std::vector<std::vector<Cell *>> grid;
	int bombs;

	static GameSize getGameSize(Difficulty d);
public:
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
	void click(const Index &i);
	void doubleClick(const Index &i);
	void swtichFlag(const Index &i);

signals:
	void gameOver();
	void youWon();

public slots:
};

//Cell should be a nested public class for Minesweeper, but nested classes can't use the moc functionalities
class Cell: public QObject
{
	Q_OBJECT
	friend class MineSweeper;
private:
	bool open, flagged, bomb;
	unsigned short surrounding_bombs;
	Cell();
public:
	void click();
	void switchFlag();

signals:
	void clicked();
	void switchedFlag();
};

#endif // MINESWEEPER_H
