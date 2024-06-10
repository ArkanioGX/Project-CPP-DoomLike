#pragma once
#include "Actor.h"
class PickableKeyActor : public Actor
{
public:
	void updateActor(float dt) override;

	void setKeyID(int id);

	PickableKeyActor();
	~PickableKeyActor();

	void Pick();

	class BoxComponent* getBox() { return box; }
	class MeshComponent* getMesh() { return mc; }

private:
	class BoxComponent* box;
	class MeshComponent* mc;

	int keyID = -2;
};

