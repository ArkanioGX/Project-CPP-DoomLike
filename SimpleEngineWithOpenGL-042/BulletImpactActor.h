#pragma once
#include "Actor.h"
class BulletImpactActor : public Actor
{
private:
	float lifeTime = 5;
	float ttl = lifeTime;
public:
	BulletImpactActor();

	void updateActor(float dt)override;

};

