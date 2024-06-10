#include "DoorPlaneActor.h"
#include "DoorActor.h"
#include "Log.h"

DoorPlaneActor::DoorPlaneActor(DoorActor* doorOwner):
	PlaneActor(),
	doorActor(doorOwner)
{
}

void DoorPlaneActor::updateActor(float dt)
{
	float newZ = getPosition().z;
	if (isOpen && newZ != maxHeightDoor) {
		newZ += dt * 200;
		newZ = Maths::clamp(newZ, 0.f, maxHeightDoor);
		setPosition(Vector3(getPosition().x, getPosition().y, newZ));
	}
}

void DoorPlaneActor::open()
{
	isOpen = true;
}

void DoorPlaneActor::activate()
{
	doorActor->Open();
}

void DoorPlaneActor::setMaxHeight(float mh)
{
	maxHeightDoor = mh;
}
