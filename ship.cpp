#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include"getopt.h"
#include"Layout.h"

using namespace std;

//reducing memory usage

int main(int argc, char *argv[])
{
	std::ios_base::sync_with_stdio(false);

	Layout ship;

	ship.reader();
	
	struct option longOpts[] = 
	{
		{ "stack", no_argument, NULL, 's' },
		{ "queue", no_argument, NULL, 'q' },
		{ "output", required_argument, NULL, 'o' },
		{ "help", no_argument, NULL, 'h' },
	};
	
	opterr = false;

	if (argc != 2 && argc != 4)
	{
		cout << "Error in command line" << endl;
		exit(1);
	}
	
	int opt = 0, index = 0;
	while ((opt = getopt_long(argc, argv, "sqo:h", longOpts, &index)) != -1)
	{
		switch (opt)
		{
		case 's':
			ship.setRoutingScheme('S');
			break;
		case 'q':
			ship.setRoutingScheme('Q');
			break;
		case 'o':
			ship.setOutput(*optarg);
			break;
		case 'h':
			cout << "Program Information" << endl;
			cout << "This program determines a path from a starting point to an ending point" << endl;
			cout << "using an input file\n" << endl;
			cout << "Command Line Flags" << endl;
			cout << "--stack/-s uses the stack based routing scheme to find the path" << endl;
			cout << "--queue/-q uses the queue based routing scheme to find the path" << endl;
			cout << "--output/-o use this flag along with an M or L to determine the output mode, Map or List" << endl;
			return 0;
			break;
		default:
			cout << "Error in command line" << endl;
		}
	}

	ship.routing();
	ship.printShip();

	return 0;
}