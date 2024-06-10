#include "PickableKeyActor.h"
#include "MeshComponent.h"
#include "Mesh.h"
#include "Assets.h"
#include "BoxComponent.h"
#include "Game.h"
#include "FPSActor.h"

void PickableKeyActor::updateActor(float dt)
{
	Vector3 dir = getPosition() - Game::instance().getPlayer()->getPosition();
	dir.normalize();
	dir = Vector3(dir.x, dir.y, 0);
	Quaternion q = Quaternion(dir, Maths::piOver2);
	q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::piOver2));
	
	setRotation(q);
}

void PickableKeyActor::setKeyID(int id)
{
	keyID = id;
	getMesh()->setTextureIndex(6+(id%2));
}

PickableKeyActor::PickableKeyActor():
	Actor()
{
	mc = new MeshComponent(this);
	Mesh* mesh = &Assets::getMesh("Mesh_Plane");

	mc->setMesh(*mesh);
	mc->setTextureIndex(7);
	box = new BoxComponent(this);
	box->setObjectBox(mesh->getBox());
	box->setCanPassThrough(false);

	getGame().addKey(this);
}

PickableKeyActor::~PickableKeyActor()
{
	getGame().removeKey(this);
}

void PickableKeyActor::Pick()
{
	for (int i = 0; i < getGame().getDoors().size(); i++) {
		DoorActor* currentDoor = getGame().getDoors()[i];
		currentDoor->Open(keyID);
	}
	setPosition(Vector3(0, 0, -1000));
	//setState(ActorState::Dead);
	//Iterate Through Doors to unlock them
}
