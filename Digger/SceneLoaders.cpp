#include "SceneLoaders.h"

#include <iostream>

#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "FpsComponent.h"
#include "GroundComponent.h"
#include "TextComponent.h"
#include "InputManager.h"
#include "LevelScene.h"
#include "MinerComponent.h"
#include "MoveCommand.h"
#include "PlayAudioCommand.h"
#include "Renderer.h"

#include "SceneManager.h"

using namespace dae;

void InsertBackground(Scene* pScene)
{
	auto root = pScene->GetRoot();

	auto go = root->AddChild();
	go->AddComponent<RenderComponent>();
	go->GetComponent<RenderComponent>()->SetTexture("background.tga");

	go = root->AddChild();
	go->GetComponent<TransformComponent>()->SetLocalPosition(216, 180);
	go->AddComponent<RenderComponent>();
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

void LoadAudioScene()
{
	auto& inputManager = InputManager::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	Scene* pScene = sceneManager.CreateScene("AudioScene");

	InsertBackground(pScene);

	// Input
	std::shared_ptr<Sound> sound = ResourceManager::GetInstance().LoadSound("wave.mp3");
	auto audioCommand = std::make_shared<PlayAudioCommand>(sound, 100);
	inputManager.ButtonBind(SDL_SCANCODE_SPACE, InputManager::InputState::Down, audioCommand);
}

void LoadTestingScene()
{

	auto& inputManager = InputManager::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	Scene* pScene = sceneManager.CreateScene("TestingScene");

	// Level gameobject
	GameObject* level = pScene->AddGameObject();
	auto pGridComponent = level->AddComponent<GroundComponent>();
	int width{};
	int height{};
	Renderer::GetInstance().GetDimensions(&width, &height);
	pGridComponent->SetDimensions(width, height);

	// Player gameobject
	GameObject* pPlayer = pScene->AddGameObject();
	auto renderComponent = pPlayer->AddComponent<RenderComponent>();
	renderComponent->SetTexture(ResourceManager::GetInstance().LoadTexture("character.png"));
	const int playerSize = 50;
	renderComponent->SetSize(playerSize, playerSize);
	renderComponent->SetOffset(-playerSize/2, -playerSize/2);

	auto transformComponent = pPlayer->GetComponent<TransformComponent>();
	transformComponent->SetLocalPosition(100, 100);

	auto moveLeftCommand = std::make_shared<MoveCommand>(glm::vec3{-1, 0, 0}, 10.f, *pPlayer);
	inputManager.ButtonBind(SDL_SCANCODE_LEFT, InputManager::InputState::Down, moveLeftCommand);

	auto moveRightCommand = std::make_shared<MoveCommand>(glm::vec3{ 1, 0, 0 }, 10.f, *pPlayer);
	inputManager.ButtonBind(SDL_SCANCODE_RIGHT, InputManager::InputState::Down, moveRightCommand);

	auto moveUpCommand = std::make_shared<MoveCommand>(glm::vec3{ 0, -1, 0 }, 10.f, *pPlayer);
	inputManager.ButtonBind(SDL_SCANCODE_UP, InputManager::InputState::Down, moveUpCommand);

	auto moveDownCommand = std::make_shared<MoveCommand>(glm::vec3{ 0, 1, 0 }, 10.f, *pPlayer);
	inputManager.ButtonBind(SDL_SCANCODE_DOWN, InputManager::InputState::Down, moveDownCommand);

	auto pMinerComponent = pPlayer->AddComponent<MinerComponent>();
	pMinerComponent->SetLevel(level);
	pMinerComponent->SetRadius(playerSize); // 2 for radius

	// FPS counter gamobject
	GameObject* pFpsCounter = pScene->AddGameObject();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	pFpsCounter->GetComponent<TransformComponent>()->SetLocalPosition(10, 10);
	pFpsCounter->AddComponent<TextComponent>();
	pFpsCounter->GetComponent<TextComponent>()->SetFont(font);
	pFpsCounter->AddComponent<FpsComponent>();

	// Testing
}

void LoadLevelScene()
{
	std::unique_ptr<LevelScene> pLevelScene = std::make_unique<LevelScene>("LevelScene");
	SceneManager::GetInstance().AddScene(std::move(pLevelScene));
}
