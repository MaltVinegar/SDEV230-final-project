
#include "rogue.hpp"
#include <ncurses.h>

void screenSetup(){
	initscr();//starts ncurses mode
	printw("Hit q to quit!");//prints a string
	noecho();//makes it so typing is not displayed on the screen
	refresh();//updates screen with what is in memomry
}

int main() {
	int ch;

	Position newPos;
	srand(time(NULL));
	Level level { };
	screenSetup();

	level.print();
	/*main game loop*/
	while((ch = getch()) != 'q') {
		level.moveMonsters();

		newPos = level.user.handleInput(ch);
		level.checkPos(newPos);

		clear();
		level.print();

		if(level.user.hp <= 0)
			break;
		if(level.user.hp < 10 && !(rand()%30))
			level.user.hp++;
	}
	/*end main game loop*/

	endwin();//turn off ncurses mode or you will have to close the terminal and restart the program

	std::cout << "\nYou Lose!\n";

	return 0;
}
