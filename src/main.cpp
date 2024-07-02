#include <curses.h>
#include <iostream>
#include <math.h>
#include <string.h>

#include <ncurses.h>
#include <panel.h>

char scrn[48][96] { "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};

//213x60
//60 93 60
//213x20

int main() {
	for(auto &i : scrn)
		strcpy(i, scrn[0]);

	initscr();
	noecho();
	cbreak();
	raw();
	curs_set(0);
	keypad(stdscr, TRUE);

	int ch, done;
	WINDOW *stats, *playarea, *chat, *inventory;


	stats = newwin(50, 57, 0, 0);
	playarea = newwin(50, 98, 0, 57);
	chat = newwin(50, 57, 0, 155);
	inventory = newwin(10, 212, 50, 0);

	wrefresh(stats);
	wrefresh(playarea);
	wrefresh(chat);
	wrefresh(inventory);

	keypad(stats, TRUE);
	keypad(playarea, TRUE);
	keypad(chat, TRUE);
	keypad(inventory, TRUE);

	mousemask(ALL_MOUSE_EVENTS, NULL);

	MEVENT event;
	done = 0;

	while(!done) {
		box(stats, 0, 0);
		box(playarea, 0, 0);
		box(chat, 0, 0);
		box(inventory, 0, 0);
		ch = getch();

		if(ch == 'q')
			done = 1;
		else if(ch == 'p')
			for(unsigned i {0}; i < 48; i++)
				mvwprintw(playarea, i+1, 1, "%s", scrn[i]);
		else if(ch == KEY_MOUSE) {
			if(getmouse(&event) == OK) {
				if(event.bstate & (BUTTON1_CLICKED|BUTTON1_PRESSED|BUTTON1_DOUBLE_CLICKED|BUTTON1_TRIPLE_CLICKED|BUTTON1_RELEASED)) {
					mvwprintw(playarea, 2, 1, "You pressed the button1");
				} else if(event.bstate & BUTTON2_PRESSED)
					mvwprintw(playarea, 2, 1, "You pressed the button2");
				else
					mvwprintw(playarea, 2, 1, "You pressed the key %i", event.bstate);
				mvwprintw(playarea, 3, 1, "(x %i, y %i)", event.x, event.y);
				mvwprintw(stdscr, event.y, event.x, "(x %i, y %i)", event.x, event.y);
			}
		} else
			mvwprintw(playarea, 2, 1, "You pressed the key %c", ch);


		wrefresh(stats);
		wrefresh(playarea);
		wrefresh(chat);
		wrefresh(inventory);
		wclear(stats);
		wclear(playarea);
		wclear(chat);
		wclear(inventory);
	}

	delwin(stats);
	delwin(playarea);
	delwin(chat);
	delwin(inventory);
	erase();

	endwin();
	echo();
	curs_set(1);
/*
	while(true) {
		refresh();
		auto i = getch();
		std::cout << i;
	}*/
}
