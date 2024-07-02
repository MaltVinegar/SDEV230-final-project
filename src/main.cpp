#include <curses.h>
#include <iostream>
#include <math.h>
#include <string.h>

#include <ncurses.h>
#include <panel.h>

char scrn[18][58] { "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"};

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
	WINDOW *win1, *win2, *focus;

	win1 = newwin(20, 60, 0, 0);
	win2 = newwin(20, 30, 0, 60);
	wrefresh(win1);
	wrefresh(win2);

	focus = win1;

	keypad(win1, TRUE);
	keypad(win2, TRUE);
	mousemask(ALL_MOUSE_EVENTS, NULL);

        MEVENT event;
	done = 0;

	while(!done) {
		box(win1, 0, 0);
		wattron(win2, A_STANDOUT);
		box(win2, 0, 0);
		wattroff(win2, A_STANDOUT);
		ch = getch();

		if(ch == 'q')
			done = 1;
		else if(ch == 'a')
			focus = win2;
		else if(ch == 'p') {
			for(unsigned i {0}; i < 58; i++)
				mvwprintw(win1, i+1, 1, "%s", scrn[i]);
		} else if(ch == KEY_MOUSE) {
			if(getmouse(&event) == OK) {
				if(event.bstate & (BUTTON1_CLICKED|BUTTON1_PRESSED|BUTTON1_DOUBLE_CLICKED|BUTTON1_TRIPLE_CLICKED|BUTTON1_RELEASED)) {
					mvwprintw(win1, 2, 1, "You pressed the button1");
					if(event.x < 60 && event.y < 20)
						focus = win1;
					else if(event.x < 90 && event.y < 20)
						focus = win2;
				} else if(event.bstate & BUTTON2_PRESSED)
					mvwprintw(win1, 2, 1, "You pressed the button2");
				else
					mvwprintw(win1, 2, 1, "You pressed the key %i", event.bstate);
				mvwprintw(win1, 3, 1, "(x %i, y %i)", event.x, event.y);
				mvwprintw(win1, event.y, event.x, "(x %i, y %i)", event.x, event.y);
			}
		} else
			mvwprintw(win1, 2, 1, "You pressed the key %c", ch);

		wattron(focus, A_STANDOUT);
		mvwprintw(focus, 1, 1, "Focus is on this window");
		wattroff(focus, A_STANDOUT);

		wrefresh(win1);
		wrefresh(win2);
		wclear(win1);
		wclear(win2);
	}

	delwin(win1);
	delwin(win2);
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
