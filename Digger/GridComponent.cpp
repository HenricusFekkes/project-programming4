#include "GridComponent.h"

#include "GameObject.h"

using namespace dae;


GridComponent::GridComponent(GameObject& gameObject)
	: IComponent{gameObject}
{}

void GridComponent::Update(float)
{}

void GridComponent::FixedUpdate(float)
{}

void GridComponent::Render()
{}

glm::vec3 GridComponent::GridSpaceToWorldSpace(int x, int y) const
{
	return {(x*m_Width)/m_Columns, (y * m_Height) / m_Rows, 0};
}


void GridComponent::SetWidth(float width)
{
	m_Width = width;
	m_Height = (width * m_Rows) / m_Columns;
}

float GridComponent::GetCellSize() const
{
	return m_Width / float(m_Columns);
}


bool GridComponent::OutOfBounds(const glm::vec3 pos) const
{
	if (pos.x < 0 or pos.x > m_Width)
		return true;
	if (pos.y < 0 or pos.y > m_Height)
		return true;
	return false;
}


glm::vec3 GridComponent::ClampToCell(glm::vec3 position, Direction direction, float& distance) const
{
	float travelledDistance{};
	switch (direction)
	{
	case Up:
		{
			float topOfCell = floor(position.y / GetCellSize()) * GetCellSize();
			travelledDistance = std::min(distance,  position.y - topOfCell);
			position.y -= travelledDistance;
			break;
		}
	case Down:
		{
			float bottomOfCell = ceil(position.y / GetCellSize()) * GetCellSize();
			travelledDistance = std::min(distance, bottomOfCell - position.y);
			position.y += travelledDistance;
			break;
		}
	case Left:
		{
			float leftOfCell = floor(position.x / GetCellSize()) * GetCellSize();
			travelledDistance = std::min(distance, position.x - leftOfCell);
			position.x -= travelledDistance;
			break;
		}
	case Right:
		{
			float rightOfCell = ceil(position.x / GetCellSize()) * GetCellSize();
			travelledDistance = std::min(distance, rightOfCell - position.x);
			position.x += travelledDistance;
			break;
		}
	}
	distance = std::max(distance - travelledDistance, 0.f);
	return ClampToGrid(position);
}

glm::vec3 GridComponent::ClampToGrid(glm::vec3 position) const
{
	float x = std::min(std::max(position.x, 0.f), m_Width);
	float y = std::min(std::max(position.y, 0.f), m_Height);
	return glm::vec3{ x, y,0 };
}

