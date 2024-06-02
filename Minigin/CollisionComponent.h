#pragma once
#include "Component.h"
#include <glm/vec2.hpp>

namespace dae
{
	class CollisionComponent : public UpdateComponent
	{
	public:
		CollisionComponent(GameObject* pOwner);
		virtual ~CollisionComponent() = default;

		virtual void Update(float elapsedSec) override;

		void SetWidth(int width);
		void SetHeight(int height);
		void SetDimensions(glm::ivec2 dimensions);
		int GetWidth() const;
		int GetHeight() const;

	private:
		int m_Width;
		int m_Height;
	};
}

