
#include "rogue.hpp"

Position constexpr grid_pins[] {
	{1, 1}, {27, 1}, {52, 1}, {77, 1},
	{1, 27}, {27, 27}, {52, 27}, {77, 27}
};

Room::Room(int const grid) :
	pos {grid_pins[grid]},
	height {12},
	width {18},
	doors { }
{
	int qtyDoors;
	if(grid == 0 || grid == 7)
		qtyDoors = 1;
	else
		qtyDoors = 2;

	int facing;

	if(grid == 0)
		facing = 4;
	else if(grid == 4)
		facing = 1;
	else
		facing = 3;

	for(int q { }; q < qtyDoors; q++) {
		if(facing == 1)
			/*north/top door*/
			doors.push_back({rand()%(width - 2) + pos.x + 1, pos.y});
		else if(facing == 2)
			/*south/bot door*/
			doors.push_back({rand()%(width - 2) + pos.x + 1, pos.y + height - 1});
		else if(facing == 3)
			/*west/left door*/
			doors.push_back({pos.x, rand()%(height - 2) + pos.y + 1});
		else if(facing == 4)
			/*east/right door*/
			doors.push_back({pos.x + width - 1, rand()%(height - 2) + pos.y + 1});

		if(grid == 3)
			facing = 2;
		else
			facing = 4;
	}
}

void Room::draw() const {
	for(int x {pos.x}; x < pos.x + width; x++) {
		mvprintw(pos.y, x, "-"); /*top*/
		mvprintw(pos.y + height - 1, x, "-");/*bot*/
	}

	for(int y {pos.y + 1}; y < pos.y + height -1; y++) {
		/*sidewalls*/
		mvprintw(y, pos.x, "|");
		mvprintw(y, pos.x + width - 1, "|");

		/*floors*/
		for(int x {pos.x + 1}; x < pos.x + width - 1; x++)
			mvprintw(y, x, ".");
	}

	for(int q { }; q < doors.size(); q++)
		mvprintw(doors.at(q).y, doors.at(q).x, "+");
}

void connectDoors(Position const &doorOne, Position const &doorTwo) {
	//create an array of each room and their doors
	//for each select nearest and draw conneciton
	Position temp {doorOne}, prev {doorOne};

	int count {0};

	while(true) {
		/*hall search cardinal directions*/
		//I think I want to make this always add a hallway and end at + or #, need to do each door then,
		//or a room may not get connected
		//so prefer the next space closer to the door by default
		//but if none, just find the next open space and continue

		/*east and west*/
		if((abs((temp.x - 1) - doorTwo.x) < abs(temp.x - doorTwo.x)) && (mvinch(temp.y, temp.x - 1) == ' ')) {
			prev.x = temp.x;
			temp.x = temp.x-1;
		} else if((abs((temp.x + 1) - doorTwo.x) < abs(temp.x - doorTwo.x)) && (mvinch(temp.y, temp.x + 1) == ' ')) {
			prev.x = temp.x;
			temp.x = temp.x + 1;
			/*north and south*/
		} else if((abs((temp.y + 1) - doorTwo.y) < abs(temp.y - doorTwo.y)) && (mvinch(temp.y + 1, temp.x) == ' ')) {
			prev.y = temp.y;
			temp.y = temp.y + 1;
		} else if((abs((temp.y - 1) - doorTwo.y) < abs(temp.y - doorTwo.y)) && (mvinch(temp.y - 1, temp.x) == ' ')) {
			prev.y = temp.y;
			temp.y = temp.y - 1;
		} else {
			if(count == 0) {
				temp = prev;
				count++;
				continue;
			} else return;
		}

		mvprintw(temp.y, temp.x, "#");
	}
}
