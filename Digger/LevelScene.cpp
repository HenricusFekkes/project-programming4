#include "LevelScene.h"

#include "CollisionComponent.h"
#include "FpsComponent.h"
#include "GameObject.h"
#include "GroundComponent.h"
#include "InputManager.h"
#include "MinerComponent.h"
#include "MoveCommand.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "TextComponent.h"
#include "RenderComponent.h"
#include "CollisionManagerComponent.h"
#include "PlayerComponent.h"
#include "ScoreComponent.h"

using namespace dae;


LevelScene::LevelScene(const std::string& name)
	: Scene{name}
{}

void LevelScene::Initialize()
{
	m_pCollisionManager = GetRoot()->AddComponent<CollisionManagerComponent>();

	InitializeGround();
	InitializePlayer();
	InitializeSpawner();

	// FPS GameObject
	GameObject* pFpsCounter = AddGameObject();
	auto font = ResourceManager::GetInstance().LoadFont("Lingua.otf", 18);
	pFpsCounter->GetComponent<TransformComponent>()->SetLocalPosition(10, 10);
	pFpsCounter->AddComponent<FpsComponent>();
	pFpsCounter->GetComponent<TextComponent>()->SetFont(font);

	AddEmeralds(200, 250);
}

void LevelScene::AddRock(int x, int y)
{
	auto& resourceManager = ResourceManager::GetInstance();
	GameObject* pRock = AddGameObject();
	auto renderComponent = pRock->AddComponent<RenderComponent>();
	renderComponent->SetTexture(resourceManager.LoadTexture("rock.png"));
	const int rockSize = 50;
	renderComponent->SetSize(rockSize, rockSize);
	renderComponent->SetOffset(-rockSize / 2, -rockSize / 2);
	pRock->GetComponent<TransformComponent>()->SetLocalPosition(x, y); // TODO

	auto pCollider = pRock->AddComponent<CollisionComponent>();
	pCollider->AttachObserver(m_pCollisionManager);
	pCollider->SetRadius(rockSize);
	m_pRocks.push_back(pRock);
}

void LevelScene::AddEmeralds(int x, int y)
{
	const int emeraldSize = 50;

	auto& resourceManager = ResourceManager::GetInstance();
	GameObject* pEmerald = AddGameObject();

	// RENDERCOMPONENT
	auto renderComponent = pEmerald->AddComponent<RenderComponent>();
	renderComponent->SetTexture(resourceManager.LoadTexture("emerald.png"));
	renderComponent->SetSize(emeraldSize, emeraldSize);
	renderComponent->SetOffset(-emeraldSize / 2, -emeraldSize / 2);


	// TRANSFORMCOMPONENT
	pEmerald->GetComponent<TransformComponent>()->SetLocalPosition(x, y); // TODO

	// COLLISIONCOMPONENT
	auto pCollider = pEmerald->AddComponent<CollisionComponent>();
	pCollider->AttachObserver(m_pCollisionManager);
	pCollider->SetRadius(emeraldSize);


	// SCORECOMPONENT
	pEmerald->AddComponent<ScoreComponent>()->SetValue(10);

	m_pEmeralds.push_back(pEmerald);
}

void LevelScene::InitializePlayer()
{
	auto& inputManager = InputManager::GetInstance();
	auto& resourceManager = ResourceManager::GetInstance();

	m_pPlayer = AddGameObject();
	auto renderComponent = m_pPlayer->AddComponent<RenderComponent>();
	renderComponent->SetTexture(resourceManager.LoadTexture("player1.png"));
	const int playerSize = 50;
	renderComponent->SetSize(playerSize, playerSize);
	renderComponent->SetOffset(-playerSize / 2, -playerSize / 2);

	auto transformComponent = m_pPlayer->GetComponent<TransformComponent>();
	transformComponent->SetLocalPosition(100, 100);

	auto moveLeftCommand = std::make_shared<MoveCommand>(glm::vec3{ -1, 0, 0 }, 10.f, *m_pPlayer);
	inputManager.ButtonBind(SDL_SCANCODE_LEFT, InputManager::InputState::Down, moveLeftCommand);

	auto moveRightCommand = std::make_shared<MoveCommand>(glm::vec3{ 1, 0, 0 }, 10.f, *m_pPlayer);
	inputManager.ButtonBind(SDL_SCANCODE_RIGHT, InputManager::InputState::Down, moveRightCommand);

	auto moveUpCommand = std::make_shared<MoveCommand>(glm::vec3{ 0, -1, 0 }, 10.f, *m_pPlayer);
	inputManager.ButtonBind(SDL_SCANCODE_UP, InputManager::InputState::Down, moveUpCommand);

	auto moveDownCommand = std::make_shared<MoveCommand>(glm::vec3{ 0, 1, 0 }, 10.f, *m_pPlayer);
	inputManager.ButtonBind(SDL_SCANCODE_DOWN, InputManager::InputState::Down, moveDownCommand);

	auto pMinerComponent = m_pPlayer->AddComponent<MinerComponent>();
	pMinerComponent->SetLevel(m_pGround);
	pMinerComponent->SetRadius(playerSize); // 2 for radius

	auto pCollider = m_pPlayer->AddComponent<CollisionComponent>();
	pCollider->SetRadius(playerSize);
	pCollider->AttachObserver(m_pCollisionManager);

	m_pPlayer->AddComponent<PlayerComponent>();
}

void LevelScene::InitializeGround()
{
	m_pGround = AddGameObject();
	auto pGridComponent = m_pGround->AddComponent<GroundComponent>();
	int width{};
	int height{};
	Renderer::GetInstance().GetDimensions(&width, &height);
	pGridComponent->SetDimensions(width, height);
}

void LevelScene::InitializeSpawner()
{
	m_pSpawner = AddGameObject();
}