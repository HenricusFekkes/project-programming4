#include "SceneLoaders.h"

#include <iostream>

#include "ChangeHealthCommand.h"
#include "ChangePointsCommand.h"
#include "EventManager.h"
#include "Events.h"
#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "FpsComponent.h"
#include "HealthComponent.h"
#include "TextComponent.h"
#include "InputManager.h"
#include "LivesComponent.h"
#include "MoveCommand.h"
#include "PlayAudioCommand.h"

#include "SceneManager.h"
#include "ScoreComponent.h"

using namespace dae;

void InsertBackground(Scene* scene)
{
	auto root = scene->GetRoot();

	auto go = root->AddChild();
	go->GetComponent<RenderComponent>()->SetTexture("background.tga");

	go = root->AddChild();
	go->GetComponent<TransformComponent>()->SetLocalPosition(216, 180);
	go->GetComponent<RenderComponent>()->SetTexture("logo.tga");

	go = root->AddChild();
	auto font1 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	go->GetComponent<TransformComponent>()->SetLocalPosition(80, 20);
	go->AddComponent<TextComponent>();
	go->GetComponent<TextComponent>()->SetFont(font1);
	go->GetComponent<TextComponent>()->SetText("Programming 4 Assignment");

	go = root->AddChild();
	auto font2 = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	go->GetComponent<TransformComponent>()->SetLocalPosition(10, 10);
	go->AddComponent<TextComponent>();
	go->GetComponent<TextComponent>()->SetFont(font2);
	go->AddComponent<FpsComponent>();
}

void LoadInputScene()
{
	auto& inputManager = InputManager::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto* pScene = sceneManager.CreateScene("InputScene");
	auto root = pScene->GetRoot();

	InsertBackground(pScene);

	const float speedPlayer1 = 100;
	auto player1 = root->AddChild();
	auto posPlayer1 = glm::vec3{ 300.f, 320.f, 0.f };
	player1->GetComponent<RenderComponent>()->SetTexture("bonus.BMP");
	player1->GetComponent<TransformComponent>()->SetLocalPosition(posPlayer1);


	const float speedPlayer2 = 2 * speedPlayer1;
	auto player2 = root->AddChild();
	auto posPlayer2 = glm::vec3{ 400.f, 320.f, 0.f };
	player2->GetComponent<RenderComponent>()->SetTexture("bonus.BMP");
	player2->GetComponent<TransformComponent>()->SetLocalPosition(posPlayer2);

	auto left = glm::vec3{ -1, 0, 0 };
	auto right = glm::vec3{ 1, 0, 0 };
	auto up = glm::vec3{ 0, -1, 0 };
	auto down = glm::vec3{ 0, 1, 0 };
	
	auto commandLeft = std::make_shared<MoveCommand>(player1, left * speedPlayer1);
	auto commandRight = std::make_shared<MoveCommand>(player1, right * speedPlayer1);
	auto commandUp = std::make_shared<MoveCommand>(player1, up * speedPlayer1);
	auto commandDown = std::make_shared<MoveCommand>(player1, down * speedPlayer1);
	inputManager.ButtonBind(SDL_SCANCODE_LEFT, InputManager::InputState::Pressed, commandLeft);
	inputManager.ButtonBind(SDL_SCANCODE_RIGHT, InputManager::InputState::Pressed, commandRight);
	inputManager.ButtonBind(SDL_SCANCODE_UP, InputManager::InputState::Pressed, commandUp);
	inputManager.ButtonBind(SDL_SCANCODE_DOWN, InputManager::InputState::Pressed, commandDown);

	unsigned gamepadNr = inputManager.AddGamepad();
	commandLeft = std::make_shared<MoveCommand>(player2, left * speedPlayer2);
	commandRight = std::make_shared<MoveCommand>(player2, right * speedPlayer2);
	commandUp = std::make_shared<MoveCommand>(player2, up * speedPlayer2);
	commandDown = std::make_shared<MoveCommand>(player2, down * speedPlayer2);
	inputManager.ButtonBind(gamepadNr, Gamepad::Button::DPadLeft, InputManager::InputState::Pressed, commandLeft);
	inputManager.ButtonBind(gamepadNr, Gamepad::Button::DPadRight, InputManager::InputState::Pressed, commandRight);
	inputManager.ButtonBind(gamepadNr, Gamepad::Button::DPadUp, InputManager::InputState::Pressed, commandUp);
	inputManager.ButtonBind(gamepadNr, Gamepad::Button::DPadDown, InputManager::InputState::Pressed, commandDown);
}

void LoadEventScene()
{
	std::cout <<
		"Player one controls:\n"
		"- Change Score : Arrow down/up\n"
		"- Change health: Arrow left/right\n"
		"Player two controls:\n"
		"- Change Score: dpad down/up\n"
		"- Change health: dpad left/right\n";

	auto& inputManager = InputManager::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto* scene = sceneManager.CreateScene("InputScene");
	auto root = scene->GetRoot();

	InsertBackground(scene);

	// Player 1
	auto player1 = root->AddChild();
	player1->AddComponent<LivesComponent>();
	player1->AddComponent<HealthComponent>();
	player1->AddComponent<ScoreComponent>();

	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);

	auto p1LivesHud = root->AddChild();
	p1LivesHud->GetComponent<TransformComponent>()->SetLocalPosition(10, 180);
	p1LivesHud->AddComponent<TextComponent>();
	p1LivesHud->GetComponent<TextComponent>()->SetFont(font);
	p1LivesHud->GetComponent<TextComponent>()->SetText("Lives p1: " + std::to_string(player1->GetComponent<LivesComponent>()->GetLives()));
	EventManager<LivesChangedEvent>::GetInstance().Subscribe(
		[player1, p1LivesHud](LivesChangedEvent e)
		{
			if (e.pCaller == player1)
			{
				p1LivesHud->GetComponent<TextComponent>()->SetText("Lives P1: " + std::to_string(e.lives));
			}
		});

	auto p1HealthHud = root->AddChild();
	p1HealthHud->GetComponent<TransformComponent>()->SetLocalPosition(10, 200);
	p1HealthHud->AddComponent<TextComponent>();
	p1HealthHud->GetComponent<TextComponent>()->SetFont(font);
	p1HealthHud->GetComponent<TextComponent>()->SetText("Health: " + std::to_string(static_cast<int>(player1->GetComponent<HealthComponent>()->GetMaxHealth())));
	EventManager<HealthChangedEvent>::GetInstance().Subscribe(
		[player1, p1HealthHud](HealthChangedEvent e)
		{
			if(e.pCaller == player1)
			{
				p1HealthHud->GetComponent<TextComponent>()->SetText("Health: " + std::to_string(static_cast<int>(e.health)));
				if (e.health == 0) {
					std::cout << "Player 1 has died\n";
					player1->GetComponent<HealthComponent>()->SetHealth(player1->GetComponent<HealthComponent>()->GetMaxHealth());
					player1->GetComponent<LivesComponent>()->SetLives(player1->GetComponent<LivesComponent>()->GetLives() - 1);
				}
			}
		});

	auto p1ScorehHud = root->AddChild();
	p1ScorehHud->GetComponent<TransformComponent>()->SetLocalPosition(10, 220);
	p1ScorehHud->AddComponent<TextComponent>();
	p1ScorehHud->GetComponent<TextComponent>()->SetFont(font);
	p1ScorehHud->GetComponent<TextComponent>()->SetText("Score: " + std::to_string(static_cast<int>(player1->GetComponent<ScoreComponent>()->GetScore())));
	EventManager<ScoreChangedEvent>::GetInstance().Subscribe(
		[player1, p1ScorehHud](ScoreChangedEvent e)
		{
			if (e.pCaller == player1)
			{
				p1ScorehHud->GetComponent<TextComponent>()->SetText("Score: " + std::to_string(static_cast<int>(e.score)));
			}
		});

	// Input
	auto increaseHealthP1 = std::make_shared<ChangeHealthCommand>(player1, 25.f);
	auto decreaseHealthP1 = std::make_shared<ChangeHealthCommand>(player1, -25.f);
	auto increasePointsP1 = std::make_shared<ChangePointsCommand>(player1, 50.f);
	auto decreasePointsP1 = std::make_shared<ChangePointsCommand>(player1, -50.f);

	inputManager.ButtonBind(SDL_SCANCODE_LEFT, InputManager::InputState::Pressed, decreaseHealthP1);
	inputManager.ButtonBind(SDL_SCANCODE_RIGHT, InputManager::InputState::Pressed, increaseHealthP1);
	inputManager.ButtonBind(SDL_SCANCODE_UP, InputManager::InputState::Pressed, increasePointsP1);
	inputManager.ButtonBind(SDL_SCANCODE_DOWN, InputManager::InputState::Pressed, decreasePointsP1);

	// Player 2
	auto player2 = root->AddChild();
	player2->AddComponent<LivesComponent>();
	player2->AddComponent<HealthComponent>();
	player2->AddComponent<ScoreComponent>();

	auto p2LivesHud = root->AddChild();
	p2LivesHud->GetComponent<TransformComponent>()->SetLocalPosition(10, 280);
	p2LivesHud->AddComponent<TextComponent>();
	p2LivesHud->GetComponent<TextComponent>()->SetFont(font);
	p2LivesHud->GetComponent<TextComponent>()->SetText("Lives p2: " + std::to_string(player2->GetComponent<LivesComponent>()->GetLives()));
	EventManager<LivesChangedEvent>::GetInstance().Subscribe(
		[player2, p2LivesHud](LivesChangedEvent e)
		{
			if (e.pCaller == player2)
			{
				p2LivesHud->GetComponent<TextComponent>()->SetText("Lives P2: " + std::to_string(e.lives));
			}
		});

	auto p2HealthHud = root->AddChild();
	p2HealthHud->GetComponent<TransformComponent>()->SetLocalPosition(10, 300);
	p2HealthHud->AddComponent<TextComponent>();
	p2HealthHud->GetComponent<TextComponent>()->SetFont(font);
	p2HealthHud->GetComponent<TextComponent>()->SetText("Health: " + std::to_string(static_cast<int>(player2->GetComponent<HealthComponent>()->GetMaxHealth())));
	EventManager<HealthChangedEvent>::GetInstance().Subscribe(
		[player2, p2HealthHud](HealthChangedEvent e)
		{
			if (e.pCaller == player2)
			{
				p2HealthHud->GetComponent<TextComponent>()->SetText("Health: " + std::to_string(static_cast<int>(e.health)));
				if (e.health == 0) {
					std::cout << "Player 2 has died\n";
					player2->GetComponent<HealthComponent>()->SetHealth(player2->GetComponent<HealthComponent>()->GetMaxHealth());
					player2->GetComponent<LivesComponent>()->SetLives(player2->GetComponent<LivesComponent>()->GetLives() - 1);
				}
			}
		});

	auto p2ScorehHud = root->AddChild();
	p2ScorehHud->GetComponent<TransformComponent>()->SetLocalPosition(10, 320);
	p2ScorehHud->AddComponent<TextComponent>();
	p2ScorehHud->GetComponent<TextComponent>()->SetFont(font);
	p2ScorehHud->GetComponent<TextComponent>()->SetText("Score: " + std::to_string(static_cast<int>(player2->GetComponent<ScoreComponent>()->GetScore())));
	EventManager<ScoreChangedEvent>::GetInstance().Subscribe(
		[player2, p2ScorehHud](ScoreChangedEvent e)
		{
			if (e.pCaller == player2)
			{
				p2ScorehHud->GetComponent<TextComponent>()->SetText("Score: " + std::to_string(static_cast<int>(e.score)));
			}
		});

	// Input
	auto increaseHealthP2 = std::make_shared<ChangeHealthCommand>(player2, 25.f);
	auto decreaseHealthP2 = std::make_shared<ChangeHealthCommand>(player2, -25.f);
	auto increasePointsP2 = std::make_shared<ChangePointsCommand>(player2, 50.f);
	auto decreasePointsP2 = std::make_shared<ChangePointsCommand>(player2, -50.f);

	unsigned gamepadNr = inputManager.AddGamepad();
	inputManager.ButtonBind(gamepadNr, Gamepad::Button::DPadLeft, InputManager::InputState::Pressed, decreaseHealthP2);
	inputManager.ButtonBind(gamepadNr, Gamepad::Button::DPadRight, InputManager::InputState::Pressed, increaseHealthP2);
	inputManager.ButtonBind(gamepadNr, Gamepad::Button::DPadUp, InputManager::InputState::Pressed, increasePointsP2);
	inputManager.ButtonBind(gamepadNr, Gamepad::Button::DPadDown, InputManager::InputState::Pressed, decreasePointsP2);
}

void LoadAudioScene()
{
	std::cout << "\n===| Press spacebar to hear a sound |===\n";

	auto& inputManager = InputManager::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	auto* scene = sceneManager.CreateScene("AudioScene");

	InsertBackground(scene);

	// Input
	auto audioCommand = std::make_shared<PlayAudioCommand>("../Data/wave.mp3", 100);
	inputManager.ButtonBind(SDL_SCANCODE_SPACE, InputManager::InputState::Down, audioCommand);
}