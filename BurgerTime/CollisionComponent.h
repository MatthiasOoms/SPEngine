#pragma once
#include "Component.h"

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
		int GetWidth() const;
		int GetHeight() const;

	private:
		int m_Width;
		int m_Height;
	};
}

