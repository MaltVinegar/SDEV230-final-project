
#pragma once

/*INCLUDES */
#include <iostream>
#include <vector>

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

/*STRUCTURES*/

struct Level;
struct Position;
struct Player;
struct Equip;
struct Room;
struct Monster;

struct Position {
	bool inline operator==(Position const &) const;

	int x, y;
};

struct Player {
	Player();

	Position handleInput(char const input) const;

	Position pos;
	int hp, attack, xp, maxhp;
	char name[8];
	char role[8];
};

struct Level {
	Level();

	void moveMonsters();
	Monster *getMonsterAt(Position const);
	void print() const;
	void checkPos(Position const &newPos);

	std::vector<Room> rooms;
	std::vector<Monster> monsters;

	Player user;
};

/*monster stuff*/
void combat(Player &player, Monster &monster, int const order);
Monster selectMonster();

struct Room {
	Room(int const grid);

	void draw() const;

	Position pos;//top left corner or "pin" for the room
	int height, width;
	std::vector<Position> doors;
};

/*room stuff*/
void connectDoors(Position const &doorOne, Position const &doorTwo);

struct Monster {
	Monster(
		std::string const symbol,
		int const health,
		int const attack,
		int const pathfinding
	);

	void setStartingPosition(Room const &room);

	void pathfindingRandom();
	void pathfindingSeek(Position const player);

	std::string const symbol;
	int health, attack, pathfinding;
	bool alive;
	Position pos;
};

bool inline Position::operator==(Position const &p) const {
	return x == p.x && y == p.y;
}
