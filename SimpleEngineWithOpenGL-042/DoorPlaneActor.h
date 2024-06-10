#pragma once
#include "PlaneActor.h"
class DoorPlaneActor : public PlaneActor
{
public:
	DoorPlaneActor(class DoorActor* doorOwner);
	void updateActor(float dt) override;
	void open();
	void activate();
	void setMaxHeight(float mh);
	
private:
	bool isOpen;
	float maxHeightDoor;
	class DoorActor* doorActor;
};

