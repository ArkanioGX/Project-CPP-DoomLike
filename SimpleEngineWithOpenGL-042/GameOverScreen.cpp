#include "GameOverScreen.h"
#include "Game.h"
#include "DialogBox.h"

GameOverScreen::GameOverScreen() : UIScreen()
{
	Game::instance().setState(GameState::Pause);
	Game::instance().getInputSystem().setMouseRelativeMode(false);
	setTitle("GameOver");
	addButton("QuitButton", [this]() {
		new DialogBox("QuitText", [this]() { Game::instance().setState(GameState::Quit); });
		});
}

GameOverScreen::~GameOverScreen()
{
	Game::instance().setState(GameState::Gameplay);
	Game::instance().getInputSystem().setMouseRelativeMode(true);
}

void GameOverScreen::processInput(const InputState& inputState)
{
	UIScreen::processInput(inputState);
}

