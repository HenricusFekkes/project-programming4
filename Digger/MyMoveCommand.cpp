#include "MyMoveCommand.h"

#include "GridComponent.h"
#include "MoveComponent.h"
#include "Timer.h"


using namespace dae;

MyMoveCommand::MyMoveCommand(GameObject& movingObject, Direction direction, GameObject& gridObject)
	: m_MovingObject{movingObject}, m_GridObject{ gridObject }, m_Direction{ direction }
{}


bool MyMoveCommand::Execute()
{
	auto& moveComponent = *m_MovingObject.GetComponent<MoveComponent>();
	auto& gridComponent = *m_GridObject.GetComponent<GridComponent>();
	auto& transformComponent = *m_MovingObject.GetComponent<TransformComponent>();

	auto currentDirection = moveComponent.GetDirection();
	auto speed = moveComponent.GetSpeed();
	auto deltaTime = Timer::GetInstance().GetDeltaTime();

	float distance = speed * deltaTime;


	if(!SameOrientation(currentDirection, m_Direction))
	{
		auto newPosition = gridComponent.ClampToCell(transformComponent.GetLocalPosition(), currentDirection, distance);
		transformComponent.SetLocalPosition(newPosition.x, newPosition.y);

		if(distance <= 0.01f)
		{
			return true;
		}
	}

	auto dirvec = Dir2Vector(m_Direction);
	auto travelledDistance = distance * dirvec;
	auto desiredPosition = transformComponent.GetLocalPosition() + travelledDistance;
	auto newPosition = gridComponent.ClampToGrid(desiredPosition);
	transformComponent.SetLocalPosition(newPosition.x, newPosition.y);
	moveComponent.SetDirection(m_Direction);
	return true;
}
