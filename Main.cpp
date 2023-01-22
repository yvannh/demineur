#include "Commands.h"
#include "Container.h"
#include <iostream>
#include <ctime>
using namespace std;

int main() {

	Grid grid;

	srand(time(NULL));

	
	int command;
	cin >> command;

	commandCheck(grid, command);

	destroy(grid);
	return 0;
}