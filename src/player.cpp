
#include "rogue.hpp"

Player::Player() :
	pos {0, 0},
	hp {10},
	attack {1},
	xp {0},
	maxhp {10},
	name {"Player"},
	role {"Squire"}
{ }

Position Player::handleInput(char const input) const {
	switch(input){
		case 'w':
		case 'W':
			/*move up*/
			// playerMove(user->pos.y-1, user->pos.x, user);
			return {pos.x, pos.y - 1};
		case 's':
		case 'S':
			/*move up*/
			// playerMove(user->yPos+1, user->xPos, user);
			return {pos.x, pos.y + 1};
		case 'a':
		case 'A':
			/*move left*/
			// playerMove(user->yPos, user->xPos-1, user);
			return {pos.x - 1, pos.y};
		case 'd':
		case 'D':
			/*move right*/
			// playerMove(user->yPos, user->xPos+1, user);
			return {pos.x + 1, pos.y};
		default:
			return pos;
	}
}
