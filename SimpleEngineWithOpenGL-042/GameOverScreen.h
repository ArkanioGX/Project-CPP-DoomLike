#pragma once
#include "UIScreen.h"
class GameOverScreen : public UIScreen
{
public:
	GameOverScreen();
	~GameOverScreen();

	void processInput(const class InputState& inputState) override;
};

