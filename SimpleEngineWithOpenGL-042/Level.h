#pragma once
#include <vector>
#include "Vector2.h"

struct DoorData {
	Vector2 pos;
	unsigned int keyID;
};

struct KeyData {
	Vector2 pos;
	unsigned int keyID;
};

class Level
{
public:
	Level();
	~Level();

	void setTileAt(int posx,int posy, int i);
	void setTiles(std::vector<std::vector<int>>& tiles);
	int getTileAt(int posx, int posy);

	void addDoor(DoorData d);
	void addKey(KeyData k);

	std::vector<KeyData> getKeyList() { return keyList; }
	std::vector<DoorData> getDoors() { return lockedDoorList; }

	int getMaxSize();

	

private:
	std::vector<std::vector<int>> mapLevel;
	std::vector<KeyData> keyList;
	std::vector<DoorData> lockedDoorList;
};

