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
#include "GridComponent.h"
#include "MoveComponent.h"
#include "MyMoveCommand.h"
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

	AddEmeralds(5, 5);
}

void LevelScene::AddRock(int x, int y)
{
	auto& resourceManager = ResourceManager::GetInstance();
	GameObject* pRock = AddGameObject();
	auto renderComponent = pRock->AddComponent<RenderComponent>();
	renderComponent->SetTexture(resourceManager.LoadTexture("rock.png"));
	const int rockSize = 50;
	renderComponent->SetSize(rockSize, rockSize);
	renderComponent->SetOffset(-rockSize / 2.f, -rockSize / 2.f);

	glm::vec3 position = m_pGround->GetComponent<GridComponent>()->GridSpaceToWorldSpace(x, y);
	pRock->GetComponent<TransformComponent>()->SetLocalPosition(position); // TODO

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
	glm::vec3 position = m_pGround->GetComponent<GridComponent>()->GridSpaceToWorldSpace(x, y);
	pEmerald->GetComponent<TransformComponent>()->SetLocalPosition(position);

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

	// Render component
	auto renderComponent = m_pPlayer->AddComponent<RenderComponent>();
	renderComponent->SetTexture(resourceManager.LoadTexture("player1.png"));
	const float playerSize = m_pGround->GetComponent<GridComponent>()->GetCellSize() * 0.6f;
	const float minerArea = m_pGround->GetComponent<GridComponent>()->GetCellSize() * 0.8f;
	renderComponent->SetSize(playerSize, playerSize);
	renderComponent->SetOffset(-playerSize / 2, -playerSize / 2);

	// Transform component
	auto transformComponent = m_pPlayer->GetComponent<TransformComponent>();
	transformComponent->SetLocalPosition(100, 100);

	// Move component
	m_pPlayer->AddComponent<MoveComponent>()->SetSpeed(200.f);

	// Input
	auto moveLeftCommand = std::make_shared<MyMoveCommand>(*m_pPlayer, Left, *m_pGround);
	inputManager.ButtonBind(SDL_SCANCODE_LEFT, InputManager::InputState::Down, moveLeftCommand);

	auto moveRightCommand = std::make_shared<MyMoveCommand>(*m_pPlayer, Right, *m_pGround);
	inputManager.ButtonBind(SDL_SCANCODE_RIGHT, InputManager::InputState::Down, moveRightCommand);

	auto moveUpCommand = std::make_shared<MyMoveCommand>(*m_pPlayer, Up, *m_pGround);
	inputManager.ButtonBind(SDL_SCANCODE_UP, InputManager::InputState::Down, moveUpCommand);

	auto moveDownCommand = std::make_shared<MyMoveCommand>(*m_pPlayer, Down, *m_pGround);
	inputManager.ButtonBind(SDL_SCANCODE_DOWN, InputManager::InputState::Down, moveDownCommand);

	// Miner Component
	auto pMinerComponent = m_pPlayer->AddComponent<MinerComponent>();
	pMinerComponent->SetLevel(m_pGround);
	pMinerComponent->SetRadius(minerArea/2); // 2 for radius

	// Collider component
	auto pCollider = m_pPlayer->AddComponent<CollisionComponent>();
	pCollider->SetRadius(playerSize);
	pCollider->AttachObserver(m_pCollisionManager);

	// Player component
	m_pPlayer->AddComponent<PlayerComponent>();
}

void LevelScene::InitializeGround()
{
	m_pGround = AddGameObject();

	// Ground Component
	auto pGroundComponent = m_pGround->AddComponent<GroundComponent>();
	int width{};
	int height{};
	Renderer::GetInstance().GetDimensions(&width, &height);
	pGroundComponent->SetDimensions(width, height);

	// Grid Component
	auto pGridComponent = m_pGround->AddComponent<GridComponent>();
	pGridComponent->SetWidth(static_cast<float>(width));
}

void LevelScene::InitializeSpawner()
{
	m_pSpawner = AddGameObject();
}