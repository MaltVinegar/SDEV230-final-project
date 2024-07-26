
#include "rogue.hpp"

Level::Level() :
	rooms { },
	monsters { },
	user { }
{
	for(int x {0}; x < 8; x++)
		rooms.push_back(Room(x));

	user.pos = {rooms.at(0).pos.x + 1, rooms.at(0).pos.y + 1};

	for(auto const &r : rooms) {
		monsters.push_back(selectMonster());

		(monsters.end() - 1)->setStartingPosition(r);
	}
}

void Level::moveMonsters() {
	for(auto &m : monsters) {
		if(!m.alive)
			continue;

		if(m.pathfinding == 1)
			m.pathfindingRandom();
		else
			m.pathfindingSeek(user.pos);
	}
}

Monster *Level::getMonsterAt(Position const pos) {
	for(auto &m : monsters)
		if(pos == m.pos)
			if(m.alive)
				return &m;

	return nullptr;
}

void Level::print() const {
	for(auto const &r : rooms)
		r.draw();

	for(unsigned i {1}; i < rooms.size() - 1; i++)
		connectDoors(rooms.at(i).doors.at(1), rooms.at(i + 1).doors.at(0));
	connectDoors(rooms.at(0).doors.at(0), rooms.at(1).doors.at(0));

	for(auto const &m : monsters)
		if(m.alive)
			mvprintw(m.pos.y, m.pos.x, m.symbol.c_str());

	mvprintw(user.pos.y, user.pos.x, "@");

	mvprintw(0, 114, "STATUS");
	mvprintw(1 ,101, "Name: %s   Class: %s", user.name, user.role);
	mvprintw(2, 101, "XP: %2d ", user.xp);
	printw("HP: %d/(%d) ", user.hp, user.maxhp);
}

void Level::checkPos(Position const &newPos) {
//	int space;
	Monster *monster = getMonsterAt(newPos);

	switch(mvinch(newPos.y, newPos.x)) {
		case '.':
		case '+':
		case '#':
			user.pos = newPos;
			break;
		case 'X':
		case 'G':
		case 'T':
			if(monster)
				combat(user, *monster, 1);
			//printGameHub(level);
			//may need to remove printGameHub(level) from here,
			//added because xp did not after killing monster until taking a step
			//segFault when I attck the second monster, need to free killed monster?
		default:
//			move(level.user->pos.y, level.user->pos.x);
			break;
	}
}

void combat(Player &player, Monster &monster, int const order) {
	/*player attacking*/
	if(order == 1) {
		monster.health -= player.attack;

		if(monster.health > 0) {
			player.hp -= monster.attack;
		} else {
			monster.alive = false;
			player.xp++;
			//this should really award exp on the basis of monster
			//a G could be a regular G or a strong G "miniboss", so I should pass in exp
			//from the actual monster, and calculate exp on the basis of gear, attributes,
			//enhancements, level, ect, and allow monsters to kill monsters and players and
			//otherwise have treasures that make them harder to kill
			//damn, that is going to get into the weeds, but I LOVE IT!
		}
	/*monster attacking*/
	} else {
		player.hp -= monster.attack;

		if(player.hp > 0)
			monster.health -= player.attack;
	}
}

Monster selectMonster() {
	int monster = (rand()%2) + 1;

	switch(monster) {
		case 1:
			/*spider*/
			return Monster {"X", 3, 1, 1};
		case 2:
			/*goblin*/
			return Monster {"G", 5, 2, 2};
		case 3:
			/*troll*/
			return Monster {"T", 15, 3, 1};
	}

	return Monster {"X", 3, 1, 1};
}
