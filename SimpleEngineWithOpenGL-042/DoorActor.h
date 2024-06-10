#pragma once
#include "Actor.h"
#include <vector>
class DoorActor : public Actor
{
public:
	DoorActor();
	void Open(int kid = -1);
	void setSize(float s);
	void createDoors();
	void LockedKey(int kID);

private:
	bool isOpen = false;
	bool isLocked = false;
	int keyID = 0;
	float size;
	std::vector<class DoorPlaneActor*> DoorWalls;
};

