#include "SceneLoaders.h"

#include <iostream>

#include "ResourceManager.h"
#include "Scene.h"
#include "GameObject.h"

#include "RenderComponent.h"
#include "TransformComponent.h"
#include "FpsComponent.h"
#include "TextComponent.h"
#include "InputManager.h"
#include "PlayAudioCommand.h"

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
	std::cout << "\n===| Press spacebar to hear a sound |===\n";

	auto& inputManager = InputManager::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	Scene* pScene = sceneManager.CreateScene("AudioScene");

	InsertBackground(pScene);

	// Input
	std::shared_ptr<Sound> sound = ResourceManager::GetInstance().LoadSound("wave.mp3");
	auto audioCommand = std::make_shared<PlayAudioCommand>(sound, 100);
	inputManager.ButtonBind(SDL_SCANCODE_SPACE, InputManager::InputState::Down, audioCommand);
}