#pragma once
#include "IComponent.h"

namespace dae
{
	class GridComponent final : public IComponent
	{
	public:
		GridComponent();

		void Update(float deltaTime) override;

		void FixedUpdate(float fixedStep) override;

		void Render() override;

	private:
		int m_Columns{};
		int m_Rows{};
		float m_Width{};
		float m_Height{};
	};
}


