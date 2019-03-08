#include<iostream>
#include<vector>
#include<string>
#include"Layout.h"

using namespace std;

void Layout::reader()
{
	cin >> inputFileType >> levels >> size;

	resizeShip();

	if (inputFileType == 'M')
	{
		readerWhenMap();
	}
	else
	{
		readerWhenList();
	}
}

void Layout::readerWhenList()
{
	char charRead;
	string cinLine;

	for (int i = 0; i < levels; i++) //set all tiles of layout to '.'
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				grid[i][j][k].character = '.';
			}
		}
	}

	getline(cin, cinLine); //gets rid of blank line at top????

	while (getline(cin, cinLine))
	{
		if (cinLine[0] != '/') //checks if line is a comment
		{
			int level, row, column;
			string levelAsString, rowAsString, columnAsString;

			cinLine.erase(cinLine.begin()); //removes '(' from string

			for (unsigned int i = 0; i < cinLine.length(); i++) //removes ')' from string
			{
				if (cinLine[i] == ')')
				{
					cinLine.erase(i);
				}
			}

			auto positionComma1 = cinLine.find(',');
			levelAsString = cinLine.substr(0, positionComma1);
			level = atoi(levelAsString.c_str());
			if ((level < 0) || (level >= levels))
			{
				cerr << "error input is out of bounds" << endl;
				exit(1);
			}

			auto positionComma2 = cinLine.find(",", positionComma1 + 1);
			rowAsString = cinLine.substr(positionComma1 + 1, positionComma2 - positionComma1 - 1);
			row = atoi(rowAsString.c_str());
			if ((row < 0) || (row >= size))
			{
				cerr << "error input is out of bounds" << endl;
				exit(1);
			}

			auto positionComma3 = cinLine.find(",", positionComma2 + 1);
			columnAsString = cinLine.substr(positionComma2 + 1, positionComma3 - positionComma2 - 1);
			column = atoi(columnAsString.c_str());
			if ((column < 0) || (column >= size))
			{
				cerr << "error input is out of bounds" << endl;
				exit(1);
			}

			charRead = cinLine[positionComma3 + 1];
			if ((charRead != '.') && (charRead != '#') &&
				(charRead != 'S') && (charRead != 'H') &&
				(charRead != 'E'))
			{
				cerr << "error input is not valid" << endl;
				exit(1);
			}

			if (charRead == 'S')
			{
				startLevel = level;
				startRow = row;
				startColumn = column;
			}

			grid[level][row][column].level = level;
			grid[level][row][column].row = row;
			grid[level][row][column].column = column;
			grid[level][row][column].character = charRead;
		}
	}

	for (int i = 0; i < levels; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				grid[i][j][k].level = i;
				grid[i][j][k].row = j;
				grid[i][j][k].column = k;
			}
		}
	}
}

void Layout::readerWhenMap()
{
	vector<char> charsFromFile;
	string cinLine;

	while (getline(cin, cinLine)) //gets a line from the file
	{
		if (cinLine[0] != '/') //checks if line is a comment
		{
			for (unsigned int j = 0; j < cinLine.length(); j++)
			{
				//checks if input is valid
				if ((cinLine[j] == '.') || (cinLine[j] == '#') ||
					(cinLine[j] == 'S') || (cinLine[j] == 'H') ||
					(cinLine[j] == 'E'))
				{
					charsFromFile.push_back(cinLine[j]);
				}
				else
				{
				    cerr << "reading from map, error input is not valid" << endl;
					exit(1);
				}
			}
		}
	}

	//putting data into 3D vector
	int count = 0;
	for (int i = 0; i < levels; i++)
	{
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				grid[i][j][k].level = i;
				grid[i][j][k].row = j;
				grid[i][j][k].column = k;
				grid[i][j][k].character = charsFromFile[count];
				if (charsFromFile[count] == 'S')
				{
					startLevel = i;
					startRow = j;
					startColumn = k;
				}
				count++;
			}
		}
	}
}

void Layout::resizeShip()
{
	grid.resize(levels);
	for (int i = 0; i < levels; i++)
	{
		grid[i].resize(size);
		for (int j = 0; j < size; j++)
		{
			grid[i][j].resize(size);
		}
	}
}

void Layout::printShip()
{
	if (outputType == 'M')
	{
		printShipMap();
	}
	else
	{
		printShipList();
	}
}

void Layout::printShipMap()
{
	cout << levels << '\n' << size << '\n';

	for (int i = 0; i < levels; i++)
	{
		cout << "//level " << i << endl;
		for (int j = 0; j < size; j++)
		{
			for (int k = 0; k < size; k++)
			{
				cout << grid[i][j][k].character;
			}
			cout << endl;
		}
	}
}

void Layout::printShipList()
{
	cout << levels << '\n' << size << '\n';
	cout << "//path taken" << '\n';

	int levelToPrint = startLevel;
	int rowToPrint = startRow;
	int columnToPrint = startColumn;

	while (grid[levelToPrint][rowToPrint][columnToPrint].character != 'H')
	{
		cout << "(" << levelToPrint << "," << rowToPrint << "," << columnToPrint << "," << grid[levelToPrint][rowToPrint][columnToPrint].character << ")" << '\n';

		if (grid[levelToPrint][rowToPrint][columnToPrint].character == 'n')
		{
			rowToPrint--;
		}
		else if (grid[levelToPrint][rowToPrint][columnToPrint].character == 'e')
		{
			columnToPrint++;
		}
		else if (grid[levelToPrint][rowToPrint][columnToPrint].character == 's')
		{
			rowToPrint++;
		}
		else if (grid[levelToPrint][rowToPrint][columnToPrint].character == 'w')
		{
			columnToPrint--;
		}
		else
		{
			levelToPrint = grid[levelToPrint][rowToPrint][columnToPrint].character - 48;
		}
	}
}

void Layout::setRoutingScheme(char myRoutingScheme)
{
  routingScheme = myRoutingScheme;
}

void Layout::setOutput(char myOutputStyle)
{
  outputType = myOutputStyle;
}

void Layout::routing()
{
	int currentLevel, currentRow, currentColumn;

	stackOrQueue.push_back(grid[startLevel][startRow][startColumn]);

	if (routingScheme == 'S') //pop from back
	{
		while (!stackOrQueue.empty() && endFound == false)
		{
			currentLevel = stackOrQueue.back().level;
			currentRow = stackOrQueue.back().row;
			currentColumn = stackOrQueue.back().column;

			stackOrQueue.pop_back();

			pushSurrounding(currentLevel, currentRow, currentColumn);
		}
	}
	else //pop from front
	{
		while (!stackOrQueue.empty() && endFound == false)
		{
			currentLevel = stackOrQueue.front().level;
			currentRow = stackOrQueue.front().row;
			currentColumn = stackOrQueue.front().column;

			stackOrQueue.pop_front();

			pushSurrounding(currentLevel, currentRow, currentColumn);
		}
	}

	if (endFound == true)
	{
		backTrack(currentLevel, currentRow, currentColumn);
	}
	else
	{
		return;
	}
}

void Layout::pushSurrounding(int &currentLevel, int &currentRow, int &currentColumn)
{
	//checks if above space is out of bounds
	//checks if above space is a wall
	//checks if above space has been queued before
	if (((currentRow - 1) >= 0) &&
		(grid[currentLevel][currentRow - 1][currentColumn].character != '#') &&
		(grid[currentLevel][currentRow - 1][currentColumn].queued == false))
	{
		grid[currentLevel][currentRow - 1][currentColumn].from = 'S';
		grid[currentLevel][currentRow - 1][currentColumn].queued = true;

		if (grid[currentLevel][currentRow - 1][currentColumn].character == 'H')
		{
			currentRow--;
			endFound = true;
			return;
		}

		stackOrQueue.push_back(grid[currentLevel][currentRow - 1][currentColumn]);
	}
	//checks if space to right is out of bounds
	//checks if space to right is a wall
	//checks if space to right has been queued before
	if (((currentColumn + 1) < size) &&
		(grid[currentLevel][currentRow][currentColumn + 1].character != '#') &&
		(grid[currentLevel][currentRow][currentColumn + 1].queued == false))
	{
		grid[currentLevel][currentRow][currentColumn + 1].from = 'W';
		grid[currentLevel][currentRow][currentColumn + 1].queued = true;

		if (grid[currentLevel][currentRow][currentColumn + 1].character == 'H')
		{
			currentColumn++;
			endFound = true;
			return;
		}

		stackOrQueue.push_back(grid[currentLevel][currentRow][currentColumn + 1]);
	}
	//checks if below space is out of bounds
	//checks if below space is a wall
	//checks if below space has been queued before
	if (((currentRow + 1) < size) &&
		(grid[currentLevel][currentRow + 1][currentColumn].character != '#') &&
		(grid[currentLevel][currentRow + 1][currentColumn].queued == false))
	{
		grid[currentLevel][currentRow + 1][currentColumn].from = 'N';
		grid[currentLevel][currentRow + 1][currentColumn].queued = true;

		if (grid[currentLevel][currentRow + 1][currentColumn].character == 'H')
		{
			currentRow++;
			endFound = true;
			return;
		}

		stackOrQueue.push_back(grid[currentLevel][currentRow + 1][currentColumn]);
	}
	//checks if space to left is out of bounds
	//checks if space to left is a wall
	//checks if space to left has been queued before
	if (((currentColumn - 1) >= 0) &&
		(grid[currentLevel][currentRow][currentColumn - 1].character != '#') &&
		(grid[currentLevel][currentRow][currentColumn - 1].queued == false))
	{
		grid[currentLevel][currentRow][currentColumn - 1].from = 'E';
		grid[currentLevel][currentRow][currentColumn - 1].queued = true;

		if (grid[currentLevel][currentRow][currentColumn - 1].character == 'H')
		{
			currentColumn--;
			endFound = true;
			return;
		}

		stackOrQueue.push_back(grid[currentLevel][currentRow][currentColumn - 1]);
	}

	//checks if current tile is an elevator
	if (grid[currentLevel][currentRow][currentColumn].character == 'E')
	{
		//checks if above/lower levels have elevators
		for (int i = 0; i < levels; i++)
		{
			//checks if above/lower levels have an E
			//checks if they have been queued before
			if ((grid[i][currentRow][currentColumn].character == 'E') &&
				(grid[i][currentRow][currentColumn].queued == false))
			{
			    grid[i][currentRow][currentColumn].from = (char)currentLevel;
				grid[i][currentRow][currentColumn].queued = true;
				stackOrQueue.push_back(grid[i][currentRow][currentColumn]);
			}
		}
	}
}

void Layout::backTrack(int &currentLevel, int &currentRow, int &currentColumn)
{
	bool atStart = false;

	//handle hanger tile
	switch (grid[currentLevel][currentRow][currentColumn].from)
	{
	case('N'):
		currentRow--;
		grid[currentLevel][currentRow][currentColumn].character = 's';
		break;
	case('E'):
		currentColumn++;
		grid[currentLevel][currentRow][currentColumn].character = 'w';
		break;
	case('S'):
		currentRow++;
		grid[currentLevel][currentRow][currentColumn].character = 'n';
		break;
	case('W'):
		currentColumn--;
		grid[currentLevel][currentRow][currentColumn].character = 'e';
		break;
	default:
		cout << "the 'from' in the end is not a valid direction" << endl;
	}

	while (atStart == false)
	{
		if (grid[currentLevel][currentRow][currentColumn].from == 'N')
		{
			if (grid[currentLevel][currentRow - 1][currentColumn].character == 'S')
			{
				atStart = true;
			}
			grid[currentLevel][currentRow - 1][currentColumn].character = 's';
			currentRow--;
		}
		else if (grid[currentLevel][currentRow][currentColumn].from == 'E')
		{
			if (grid[currentLevel][currentRow][currentColumn + 1].character == 'S')
			{
				atStart = true;
			}
			grid[currentLevel][currentRow][currentColumn + 1].character = 'w';
			currentColumn++;
		}
		else if (grid[currentLevel][currentRow][currentColumn].from == 'S')
		{
			if (grid[currentLevel][currentRow + 1][currentColumn].character == 'S')
			{
				atStart = true;
			}
			grid[currentLevel][currentRow + 1][currentColumn].character = 'n';
			currentRow++;
		}
		else if (grid[currentLevel][currentRow][currentColumn].from == 'W')
		{
			if (grid[currentLevel][currentRow ][currentColumn - 1].character == 'S')
			{
				atStart = true;
			}
			grid[currentLevel][currentRow][currentColumn - 1].character = 'e';
			currentColumn--;
		}
		else //if (grid[currentLevel][currentRow][currentColumn].from//current space ".from" is a number (elevator)
		{
		  grid[(int)grid[currentLevel][currentRow][currentColumn].from][currentRow][currentColumn].character = (char)(currentLevel + 48);
			currentLevel = (int)grid[currentLevel][currentRow][currentColumn].from;
		}
	}
}