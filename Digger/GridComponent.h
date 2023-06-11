#pragma once
#include <glm/vec3.hpp>


#include "IComponent.h"
#include "Directions.h"

namespace dae
{
	class GridComponent final : public IComponent
	{
	public:
		GridComponent(GameObject& gameObject);

		void Update(float deltaTime) override;

		void FixedUpdate(float fixedStep) override;

		void Render() override;

		glm::vec3 GridSpaceToWorldSpace(int x, int y) const;

		void SetWidth(float width);
		float GetCellSize() const;

		glm::vec3 ClampToGrid(glm::vec3 position) const;
		glm::vec3 ClampToCell(glm::vec3 position, Direction direction, float& distance) const;

	private:
		bool OutOfBounds(glm::vec3 pos) const;

		const int m_Columns{15};
		const int m_Rows{10};
		float m_Width{};
		float m_Height{};
	};
}


