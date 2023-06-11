#pragma once
#include "Directions.h"
#include "GameObject.h"
#include "ICommand.h"

namespace dae
{
	class MyMoveCommand final : public dae::ICommand
	{
	public:
		MyMoveCommand(GameObject& movingObject, Direction direction, GameObject& gridObject);

		virtual bool Execute() override;
	private:
		GameObject& m_MovingObject;
		GameObject& m_GridObject;
		Direction m_Direction;
	};
}


