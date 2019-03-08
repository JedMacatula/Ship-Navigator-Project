#ifndef LAYOUT_H
#define LAYOUT_H

#include<iostream>
#include<string>
#include<vector>
#include<deque>

struct Tile
{
	int level, row, column;
	char character;
	char from;
	bool queued = false;
};

class Layout
{
private:
	std::vector<std::vector<std::vector<Tile>>> grid;
	std::deque<Tile> stackOrQueue;
	int levels, size;
	int startLevel, startRow, startColumn,
		endLevel, endRow, endColumn;
	char inputFileType, outputFuleType;
	char routingScheme;
	char outputType = 'M';
	bool endFound = false;

public:
	void reader();
	void readerWhenList();
	void readerWhenMap();
	void resizeShip();
	void printShip();
	void printShipMap();
	void printShipList();
	void routing();
	void setRoutingScheme(char myRoutingScheme);
	void setOutput(char myOutputStyle);
	void pushSurrounding(int &currentLevel, int &currentRow, int &currentColumn);
	void backTrack(int &currentLevel, int &currentRow, int &currentColumn);
};

#endif
