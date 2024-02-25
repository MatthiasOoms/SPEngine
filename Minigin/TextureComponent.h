#pragma once
#include "Component.h"
#include <memory>

namespace dae
{
	class Texture2D;
	class GameObject;

	class TextureComponent final : public RenderComponent
	{
	public:
		TextureComponent(std::weak_ptr<GameObject> pOwner);
		virtual ~TextureComponent();

		TextureComponent(const TextureComponent& other) = delete;
		TextureComponent(TextureComponent&& other) = delete;
		TextureComponent& operator=(const TextureComponent& other) = delete;
		TextureComponent& operator=(TextureComponent&& other) = delete;

		void SetTexture(const std::shared_ptr<Texture2D>& texture);
		virtual void Render(float elapsedSec) const override;

	private:
		std::shared_ptr<Texture2D> m_pTexture;
	};
};

