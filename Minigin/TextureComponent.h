#pragma once
#include "Component.h"
#include <memory>
#include <glm/vec2.hpp>

namespace dae
{
	class Texture2D;
	class GameObject;

	class TextureComponent final : public RenderComponent
	{
	public:
		TextureComponent(GameObject* pOwner);
		virtual ~TextureComponent();

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void SetTexture(const std::shared_ptr<Texture2D>& texture);
		void SetScale(float scale);
		glm::ivec2 GetDimensions();

		virtual void Render(float elapsedSec) const override;

	private:
		std::shared_ptr<Texture2D> m_pTexture;
		float m_Scale{ 1 };
	};
};

