#pragma once
#include "Actor.h"
#include "Vector3.h"

class FPSActor : public Actor
{
public:
	FPSActor();
	~FPSActor();
	
	void updateActor(float dt) override;
	void actorInput(const struct InputState& inputState) override;
	void shoot();

	void setVisible(bool isVisible);
	void fixCollisions();

	void takeDamage(int dmg);

	int getHP() { return HP; }
	int getMaxHP() { return maxHP; }

private:
	class MoveComponent* moveComponent;
	class AudioComponent* audioComponent;
	class MeshComponent* meshComponent;
	class FPSCameraComponent* cameraComponent;
	class Actor* FPSModel;
	float lastFootstep;
	class BoxComponent* boxComponent;
	float SwayPosition = 0;
	float SwayMultiplier = 2;
	float SwayUpRatio = 0.3;

	int maxHP = 10;
	int HP = maxHP;
};

const Vector3 MODEL_OFFSET = Vector3(10.0f, 0.0f,-10.f);
