#include "DoorActor.h"
#include "DoorPlaneActor.h"
#include "MeshComponent.h"

DoorActor::DoorActor()
{
	
}

void DoorActor::Open(int kid)
{
	if (isLocked) {
		if (kid != keyID) {
			return;
		}
	}
	for (int i = 0; i < DoorWalls.size(); i++) {
		DoorWalls[i]->open();
		
	}
}

void DoorActor::setSize(float s)
{
	size = s;
}

void DoorActor::createDoors()
{
	DoorPlaneActor* pw;
	Quaternion q;
	q = Quaternion(Vector3::unitX, Maths::piOver2);
	pw = new DoorPlaneActor(this);
	pw->setPosition(Vector3(getPosition().x, (getPosition().y) - size/2, 0));
	pw->setScale(2);
	pw->setRotation(q);
	pw->getMesh()->setTextureIndex(3);
	pw->setMaxHeight(size);
	DoorWalls.push_back(pw);
	pw = new DoorPlaneActor(this);
	pw->setPosition(Vector3(getPosition().x, (getPosition().y) + size/2, 0));
	pw->setScale(2);
	pw->setRotation(q);
	pw->getMesh()->setTextureIndex(3);
	pw->setMaxHeight(size);
	q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::piOver2));
	DoorWalls.push_back(pw);
	pw = new DoorPlaneActor(this);
	pw->setPosition(Vector3((getPosition().x) - (size/2), getPosition().y, 0));
	pw->setScale(2);
	pw->setRotation(q);
	pw->getMesh()->setTextureIndex(3);
	pw->setMaxHeight(size);
	DoorWalls.push_back(pw);
	pw = new DoorPlaneActor(this);
	pw->setPosition(Vector3((getPosition().x) + (size/2), getPosition().y, 0));
	pw->setScale(2);
	pw->setRotation(q);
	pw->getMesh()->setTextureIndex(3);
	pw->setMaxHeight(size);
	DoorWalls.push_back(pw);
}

void DoorActor::LockedKey(int kID)
{
	isLocked = true;
	keyID = kID;

	for (int i = 0; i < DoorWalls.size(); i++) {
		DoorWalls[i]->getMesh()->setTextureIndex(4 + (keyID%2));

	}
}
