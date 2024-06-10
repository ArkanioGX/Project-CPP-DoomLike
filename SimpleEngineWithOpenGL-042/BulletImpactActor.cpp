#include "BulletImpactActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "Mesh.h"

BulletImpactActor::BulletImpactActor():
	Actor()
{
	MeshComponent* mc = new MeshComponent(this);
	Mesh* mesh = &Assets::getMesh("Mesh_BImpact");

	mc->setMesh(*mesh);
	setScale(0.1);
	
}

void BulletImpactActor::updateActor(float dt)
{
	ttl -= dt;
	if (ttl <= 0) {
		setState(ActorState::Dead);
	}
}

