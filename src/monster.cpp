
#include "rogue.hpp"

Monster::Monster(
	std::string const symbol,
	int const health,
	int const attack,
	int const pathfinding
) :
	symbol {symbol},
	health {health},
	attack {attack},
	pathfinding {pathfinding},
	alive {true},
	pos {0, 0}
{ }

void Monster::setStartingPosition(Room const &room) {
	pos = {
		rand()%(room.width - 2) + room.pos.x + 1,
		rand()%(room.height - 2) + room.pos.y + 1
	};
}

/*
 * Spider
 *  symbol: X
 *  levels: 1-3
 *  health: 3
 *  attack: 1
 *  pthfnd: 1 (random)
 *
 * Goblin
 *  symbol: G
 *  levels: 2-7
 *  health: 5
 *  attack: 2
 *  pthfnd: 2 (seeking)
 *
 *Troll
 * symbol: T
 *  levels: 4-7
 *  health: 15
 *  attack: 3
 *  pthfnd: 1 (random)
 *///regen each turn as well
 /*
 *
 */

void Monster::pathfindingRandom() {
	int rnd = rand()%5;

	switch(rnd) {
		case 0:
			if(mvinch(pos.y - 1, pos.x) == '.')
				pos.y = pos.y - 1;
			break;
		case 1:
			if(mvinch(pos.y + 1, pos.x) == '.')
				pos.y = pos.y + 1;
			break;
		case 2:
			if(mvinch(pos.y, pos.x - 1) == '.')
				pos.x = pos.x - 1;
			break;
		case 3:
			if(mvinch(pos.y, pos.x + 1) == '.')
				pos.x = pos.x + 1;
			break;
		case 4:
			break;
	}
}

void Monster::pathfindingSeek(Position const player) {
	if((abs((pos.x - 1) - player.x) < abs(pos.x - player.x)) && (mvinch(pos.y, pos.x - 1) == '.'))
		pos.x = pos.x - 1;
	else if((abs((pos.x + 1) - player.x) < abs(pos.x - player.x) ) && (mvinch(pos.y, pos.x + 1) == '.'))
		pos.x = pos.x + 1;
	else if((abs((pos.y + 1) - player.y) < abs(pos.y - player.y) ) && (mvinch(pos.y + 1, pos.x) == '.'))
		pos.y = pos.y + 1;
	else if((abs((pos.y - 1) - player.y) < abs(pos.y - player.y) ) && (mvinch(pos.y - 1, pos.x) == '.'))
		pos.y = pos.y - 1;
}
