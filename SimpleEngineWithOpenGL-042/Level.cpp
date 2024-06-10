#include "Level.h"



Level::Level()
{
	std::vector<std::vector<int>> mapLevel;
}

Level::~Level()
{
}

void Level::setTileAt(int posx, int posy, int i)
{
	mapLevel[posx][posy] = i;
}

void Level::setTiles(std::vector<std::vector<int>>& tiles)
{
	mapLevel.clear();
	mapLevel.resize(tiles.size(), std::vector<int>(tiles[0].size()));
	for (int x = 0; x < tiles.size(); x++) {
		for (int y = 0; y < tiles[x].size(); y++) {
			mapLevel[x][y] = tiles[x][y];
		}
	}
}

int Level::getTileAt(int posx, int posy)
{
	return mapLevel[posx][posy];
}

void Level::addDoor(DoorData d)
{
	lockedDoorList.push_back(d);
}

void Level::addKey(KeyData k)
{
	keyList.push_back(k);
}

int Level::getMaxSize()
{
	return mapLevel.size();
}
