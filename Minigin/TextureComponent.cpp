#pragma once
#include "TextureComponent.h"
#include "Texture2D.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Transform.h"

namespace dae
{
	TextureComponent::TextureComponent(GameObject* pOwner)
		: RenderComponent(pOwner)
	{
	}

	TextureComponent::~TextureComponent()
	{
	}

	void TextureComponent::SetTexture(const std::shared_ptr<Texture2D>& texture)
	{
		m_pTexture = texture;
	}

	void TextureComponent::Render(float) const
	{
		if (m_pTexture != nullptr)
		{
			const auto& pos = m_pOwner->GetTransform().GetWorldPosition();
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y);
		}
	}
}