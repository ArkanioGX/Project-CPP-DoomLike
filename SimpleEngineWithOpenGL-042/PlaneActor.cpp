#include "PlaneActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "Game.h"
#include "BoxComponent.h"

PlaneActor::PlaneActor() : Actor()
{
	setScale(10.0f);
	mc = new MeshComponent(this);
	Mesh* mesh = &Assets::getMesh("Mesh_Plane");

	mc->setMesh(*mesh);
	mc->setTextureIndex(1);
	box = new BoxComponent(this);
	box->setObjectBox(mesh->getBox());

	getGame().addPlane(this);
}

PlaneActor::~PlaneActor()
{

	getGame().removePlane(this);
}
