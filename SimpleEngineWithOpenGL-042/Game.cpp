#include "Game.h"
#include "Actor.h"
#include "Timer.h"
#include "Assets.h"
#include <algorithm>
#include "MeshComponent.h"
#include "CubeActor.h"
#include "SphereActor.h"
#include "PlaneActor.h"
#include "FPSActor.h"
#include "FollowActor.h"
#include "OrbitActor.h"
#include "SplineActor.h"
#include "TargetActor.h"
#include "PauseScreen.h"
#include "DoorActor.h"
#include "PickableKeyActor.h"

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);
	bool isInputInit = inputSystem.initialize();
	bool isFontInit = Font::initialize();

	return isWindowInit && isRendererInit && isInputInit && isFontInit; // Return bool && bool && bool ...to detect error
}

void Game::load()
{
	inputSystem.setMouseRelativeMode(true);

	Assets::loadShader("Res\\Shaders\\Sprite.vert", "Res\\Shaders\\Sprite.frag", "", "", "", "Sprite");
	Assets::loadShader("Res\\Shaders\\Phong.vert", "Res\\Shaders\\Phong.frag", "", "", "", "Phong");
	Assets::loadShader("Res\\Shaders\\BasicMesh.vert", "Res\\Shaders\\BasicMesh.frag", "", "", "", "BasicMesh");

	Assets::loadTexture(renderer, "Res\\Textures\\Default.png", "Default");
	Assets::loadTexture(renderer, "Res\\Textures\\Cube.png", "Cube");
	Assets::loadTexture(renderer, "Res\\Textures\\HealthBar.png", "HealthBar");
	Assets::loadTexture(renderer, "Res\\Textures\\Plane.png", "Plane");
	Assets::loadTexture(renderer, "Res\\Textures\\GroundBrick.png", "Ground");
	Assets::loadTexture(renderer, "Res\\Textures\\WallBrick.png", "Wall");
	Assets::loadTexture(renderer, "Res\\Textures\\Radar.png", "Radar");
	Assets::loadTexture(renderer, "Res\\Textures\\Sphere.png", "Sphere");
	Assets::loadTexture(renderer, "Res\\Textures\\Crosshair.png", "Crosshair");
	Assets::loadTexture(renderer, "Res\\Textures\\RacingCar.png", "RacingCar");
	Assets::loadTexture(renderer, "Res\\Textures\\Rifle.png", "Rifle");
	Assets::loadTexture(renderer, "Res\\Textures\\Target.png", "Target");
	Assets::loadTexture(renderer, "Res\\Textures\\ButtonYellow.png", "ButtonYellow");
	Assets::loadTexture(renderer, "Res\\Textures\\ButtonBlue.png", "ButtonBlue");
	Assets::loadTexture(renderer, "Res\\Textures\\DialogBG.png", "DialogBG");
	Assets::loadTexture(renderer, "Res\\Textures\\Crosshair.png", "Crosshair");
	Assets::loadTexture(renderer, "Res\\Textures\\CrosshairRed.png", "CrosshairRed");
	Assets::loadTexture(renderer, "Res\\Textures\\Radar.png", "Radar");
	Assets::loadTexture(renderer, "Res\\Textures\\Blip.png", "Blip");
	Assets::loadTexture(renderer, "Res\\Textures\\RadarArrow.png", "RadarArrow");
	Assets::loadTexture(renderer, "Res\\Textures\\Door.png", "Door");
	Assets::loadTexture(renderer, "Res\\Textures\\DoorLockedR.png", "DoorR");
	Assets::loadTexture(renderer, "Res\\Textures\\DoorLockedB.png", "DoorB");
	Assets::loadTexture(renderer, "Res\\Textures\\KeyR.png", "KeyR");
	Assets::loadTexture(renderer, "Res\\Textures\\KeyB.png", "KeyB");
	Assets::loadTexture(renderer, "Res\\Textures\\HPLogo.png", "HPLogo");
	Assets::loadTexture(renderer, "Res\\Textures\\BallImpact.png", "BImpact");
	Assets::loadTexture(renderer, "Res\\Textures\\ExitPlatform.png", "Exit");
	Assets::loadTexture(renderer, "Res\\Textures\\RadarArrow.png", "RadarArrow");

	Assets::loadMesh("Res\\Meshes\\Cube.gpmesh", "Mesh_Cube");
	Assets::loadMesh("Res\\Meshes\\Plane.gpmesh", "Mesh_Plane");
	Assets::loadMesh("Res\\Meshes\\Sphere.gpmesh", "Mesh_Sphere");
	Assets::loadMesh("Res\\Meshes\\Rifle.gpmesh", "Mesh_Rifle");
	Assets::loadMesh("Res\\Meshes\\RacingCar.gpmesh", "Mesh_RacingCar");
	Assets::loadMesh("Res\\Meshes\\Target.gpmesh", "Mesh_Target");
	Assets::loadMesh("Res\\Meshes\\BulletImpact.gpmesh", "Mesh_BImpact");

	Assets::loadFont("Res\\Fonts\\Carlito-Regular.ttf", "Carlito");
	Assets::loadText("Res\\Localization\\English.gptext");

	Assets::loadLevel("Res\\Levels\\level1.json", "Level1");

	Vector3 StartPos = Vector3(-500.f, -500.f, 0.f);

	Level& l1 = Assets::getLevel("Level1");
	float size = 200.0f;
	int mapSize =  l1.getMaxSize();
	//Load Tiles
	for (int x = 0; x < mapSize; x++) {
		for (int y = 0; y < mapSize; y++) {
			PlaneActor* pw;
			Quaternion q;
			DoorActor* da;
			switch (l1.getTileAt(x, y)) {
			case 1:
				q = Quaternion(Vector3::unitX, Maths::piOver2);
				pw = new PlaneActor();
				pw->setPosition(Vector3(x * size, (y - 0.5) * size, 0));
				pw->setScale(2);
				pw->setRotation(q);
				pw->getMesh()->setTextureIndex(2);
				pw = new PlaneActor();
				pw->setPosition(Vector3(x * size, (y + 0.5) * size, 0));
				pw->setScale(2);
				pw->setRotation(q);
				pw->getMesh()->setTextureIndex(2);
				q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::piOver2));
				pw = new PlaneActor();
				pw->setPosition(Vector3((x - 0.5) * size, (y)*size, 0));
				pw->setScale(2);
				pw->setRotation(q);
				pw->getMesh()->setTextureIndex(2);
				pw = new PlaneActor();
				pw->setPosition(Vector3((x + 0.5) * size, (y)*size, 0));
				pw->setScale(2);
				pw->setRotation(q);
				pw->getMesh()->setTextureIndex(2);
				break;
			case 2:
				StartPos = Vector3(x * size, y * size, 0);
				break;
			case 3:
				endPos = Vector3(x * size, y * size, 0);
				break;

			case 4:
				da = new DoorActor();
				da->setPosition(Vector3(x * size, y * size, 0));
				da->setSize(size);
				da->createDoors();
				break;
			default:
				break;
			}

			PlaneActor* p = new PlaneActor();
			p->setPosition(Vector3(x * size, y * size, -size/2));
			p->setScale(2);
			if (l1.getTileAt(x, y) == 3) {
				p->getMesh()->setTextureIndex(9);
			}

			 p = new PlaneActor();
			p->setPosition(Vector3(x * size, y * size, size / 2));
			p->setScale(2);
			//Quaternion q(Vector3::unitY, -Maths::piOver2);
			//q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::pi + Maths::pi / 4.0f));
			//ca->setRotation(q);
		}
	}
	//Load keys
	for (int i = 0; i < l1.getKeyList().size(); i++) {
		KeyData kd = l1.getKeyList()[i];
		PickableKeyActor* pka = new PickableKeyActor();
		pka->setKeyID(kd.keyID);
		pka->setPosition(Vector3(kd.pos.y*size,kd.pos.x*size,0));
		addKey(pka);
	}
	//Load doors
	for (int i = 0; i < l1.getDoors().size(); i++) {
		DoorData kd = l1.getDoors()[i];
		DoorActor* dka = new DoorActor();
		
		dka->setPosition(Vector3(kd.pos.y * size, kd.pos.x * size, 0));
		dka->setSize(size);
		dka->createDoors();
		dka->LockedKey(kd.keyID);
		addDoors(dka);
	}

	fps = new FPSActor();
	fps->setPosition(StartPos);

	

	/*
	// Floor and walls

	// Setup floor
	const float start = -1250.0f;
	const float size = 250.0f;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			PlaneActor* p = new PlaneActor();
			p->setPosition(Vector3(start + i * size, start + j * size, -100.0f));
		}
	}

	// Left/right walls
	q = Quaternion(Vector3::unitX, Maths::piOver2);
	for (int i = 0; i < 10; i++)
	{
		PlaneActor* p = new PlaneActor();
		p->setPosition(Vector3(start + i * size, start - size, 0.0f));
		p->setRotation(q);

		p = new PlaneActor();
		p->setPosition(Vector3(start + i * size, -start + size, 0.0f));
		p->setRotation(q);
	}

	q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::piOver2));
	// Forward/back walls
	for (int i = 0; i < 10; i++)
	{
		PlaneActor* p = new PlaneActor();
		p->setPosition(Vector3(start - size, start + i * size, 0.0f));
		p->setRotation(q);

		p = new PlaneActor();
		p->setPosition(Vector3(-start + size, start + i * size, 0.0f));
		p->setRotation(q);
	}*/

	// Setup lights
	renderer.setAmbientLight(Vector3(0.4f, 0.4f, 0.4f));
	DirectionalLight& dir = renderer.getDirectionalLight();
	dir.direction = Vector3(0.0f, -0.707f, -0.707f);
	dir.diffuseColor = Vector3(0.78f, 0.88f, 1.0f);
	dir.specColor = Vector3(0.8f, 0.8f, 0.8f);

	// HUD
	hud = new HUD();
	/*
	Actor* crosshairActor = new Actor();
	crosshairActor->setScale(2.0f);
	crosshair = new SpriteComponent(crosshairActor, Assets::getTexture("Crosshair"));
	*/

	/*
	TargetActor* t = new TargetActor();
	t->setPosition(Vector3(1450.0f, 0.0f, 100.0f));
	t = new TargetActor();
	t->setPosition(Vector3(1450.0f, 0.0f, 400.0f));
	t = new TargetActor();
	t->setPosition(Vector3(1450.0f, -500.0f, 200.0f));
	t = new TargetActor();
	t->setPosition(Vector3(1450.0f, 500.0f, 200.0f));*/
}

void Game::processInput()
{
	inputSystem.preUpdate();

	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		bool isRunning = inputSystem.processEvent(event);
		if (!isRunning) state = GameState::Quit;
	}

	inputSystem.update();
	const InputState& input = inputSystem.getInputState();

	if (state == GameState::Gameplay)
	{
		// Escape: pause game
		if (input.keyboard.getKeyState(SDL_SCANCODE_ESCAPE) == ButtonState::Released)
		{
			new PauseScreen();
			return;
		}

		// Actor input
		isUpdatingActors = true;
		for (auto actor : actors)
		{
			actor->processInput(input);
		}
		isUpdatingActors = false;
	}
	else
	{
		if (!UIStack.empty())
		{
			UIStack.back()->processInput(input);
		}
	}
}

void Game::update(float dt)
{

	if (state == GameState::Gameplay)
	{
		// Update actors 
		isUpdatingActors = true;
		for (auto actor : actors)
		{
			actor->update(dt);
		}
		isUpdatingActors = false;

		// Move pending actors to actors
		for (auto pendingActor : pendingActors)
		{
			pendingActor->computeWorldTransform();
			actors.emplace_back(pendingActor);
		}
		pendingActors.clear();

		// Delete dead actors
		vector<Actor*> deadActors;
		for (auto actor : actors)
		{
			if (actor->getState() == Actor::ActorState::Dead)
			{
				deadActors.emplace_back(actor);
			}
		}
		for (auto deadActor : deadActors)
		{
			delete deadActor;
		}
	}

	// Update UI screens
	for (auto ui : UIStack)
	{
		if (ui->getState() == UIState::Active)
		{
			ui->update(dt);
		}
	}
	// Delete any UIScreens that are closed
	auto iter = UIStack.begin();
	while (iter != UIStack.end())
	{
		if ((*iter)->getState() == UIState::Closing)
		{
			delete* iter;
			iter = UIStack.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void Game::render()
{
	renderer.beginDraw();
	renderer.draw();
	renderer.endDraw();
}

void Game::loop()
{
	Timer timer;
	float dt = 0;
	while (state != GameState::Quit)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::reload()
{
	for (int i = 0; i < actors.size(); i++) {
		actors[i]->setState(Actor::ActorState::Dead);
	}
	actors.clear();
	Vector3 StartPos = Vector3(-500.f, -500.f, 0.f);
	Vector3 EndPos = Vector3(-500.f, -500.f, 0.f);
	Level& l1 = Assets::getLevel("Level1");
	float size = 200.0f;
	int mapSize = l1.getMaxSize();
	//Load Tiles
	for (int x = 0; x < mapSize; x++) {
		for (int y = 0; y < mapSize; y++) {
			PlaneActor* pw;
			Quaternion q;
			DoorActor* da;
			switch (l1.getTileAt(x, y)) {
			case 1:
				q = Quaternion(Vector3::unitX, Maths::piOver2);
				pw = new PlaneActor();
				pw->setPosition(Vector3(x * size, (y - 0.5) * size, 0));
				pw->setScale(2);
				pw->setRotation(q);
				pw->getMesh()->setTextureIndex(2);
				pw = new PlaneActor();
				pw->setPosition(Vector3(x * size, (y + 0.5) * size, 0));
				pw->setScale(2);
				pw->setRotation(q);
				pw->getMesh()->setTextureIndex(2);
				q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::piOver2));
				pw = new PlaneActor();
				pw->setPosition(Vector3((x - 0.5) * size, (y)*size, 0));
				pw->setScale(2);
				pw->setRotation(q);
				pw->getMesh()->setTextureIndex(2);
				pw = new PlaneActor();
				pw->setPosition(Vector3((x + 0.5) * size, (y)*size, 0));
				pw->setScale(2);
				pw->setRotation(q);
				pw->getMesh()->setTextureIndex(2);
				break;
			case 2:
				StartPos = Vector3(x * size, y * size, 0);
				break;
			case 3:
				EndPos = Vector3(x * size, y * size, 0);
				break;

			case 4:
				da = new DoorActor();
				da->setPosition(Vector3(x * size, y * size, 0));
				da->setSize(size);
				da->createDoors();
				break;
			default:
				break;
			}

			PlaneActor* p = new PlaneActor();
			p->setPosition(Vector3(x * size, y * size, -size / 2));
			p->setScale(2);

			p = new PlaneActor();
			p->setPosition(Vector3(x * size, y * size, size / 2));
			p->setScale(2);
			//Quaternion q(Vector3::unitY, -Maths::piOver2);
			//q = Quaternion::concatenate(q, Quaternion(Vector3::unitZ, Maths::pi + Maths::pi / 4.0f));
			//ca->setRotation(q);
		}
	}
	//Load keys
	for (int i = 0; i < l1.getKeyList().size(); i++) {
		KeyData kd = l1.getKeyList()[i];
		PickableKeyActor* pka = new PickableKeyActor();
		pka->setKeyID(kd.keyID);
		pka->setPosition(Vector3(kd.pos.y * size, kd.pos.x * size, 0));
		addKey(pka);
	}
	//Load doors
	for (int i = 0; i < l1.getDoors().size(); i++) {
		DoorData kd = l1.getDoors()[i];
		DoorActor* dka = new DoorActor();

		dka->setPosition(Vector3(kd.pos.y * size, kd.pos.x * size, 0));
		dka->setSize(size);
		dka->createDoors();
		dka->LockedKey(kd.keyID);
		addDoors(dka);
	}

	fps = new FPSActor();
	fps->setPosition(StartPos);

}

void Game::unload()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!actors.empty())
	{
		delete actors.back();
	}

	// Resources
	Assets::clear();
}

void Game::close()
{
	Font::close();
	inputSystem.close();
	renderer.close();
	window.close();
	SDL_Quit();
}

void Game::setState(GameState stateP)
{
	state = stateP;
}

void Game::addActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor)
{
	// Erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}

void Game::pushUI(UIScreen* screen)
{
	UIStack.emplace_back(screen);
}

void Game::addPlane(PlaneActor* plane)
{
	planes.emplace_back(plane);
}

void Game::removePlane(PlaneActor* plane)
{
	auto iter = std::find(begin(planes), end(planes), plane);
	planes.erase(iter);
}

void Game::removeKey(PickableKeyActor* k)
{
	auto iter = std::find(begin(keys), end(keys), k);
	keys.erase(iter);
}

void Game::addDoors(DoorActor* k)
{
	doors.emplace_back(k);
}

void Game::removeDoors(DoorActor* k)
{
	auto iter = std::find(begin(doors), end(doors), k);
	doors.erase(iter);
}

void Game::addKey(PickableKeyActor* k)
{
	keys.emplace_back(k);
}
