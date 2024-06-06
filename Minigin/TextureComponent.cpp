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

	void TextureComponent::SetScale(int scale)
	{
		if (scale >= 0)
		{
			m_Scale = scale;
			GetOwner()->GetTransform().SetDimensions(GetDimensions());
		}
		else
		{
			throw std::exception("TextureComponent::SetScale() > Scale must be greater than or equal to 0");
		}
	}

	glm::ivec2 TextureComponent::GetDimensions()
	{
		// If a texture is set, return its dimensions
		if (m_pTexture != nullptr)
		{
			return (glm::vec2(m_pTexture->GetSize() * m_Scale));
		}

		// If no texture is set, throw an exception
		throw std::exception("TextureComponent::GetDimensions() > No texture set");
	}

	void TextureComponent::Render(float) const
	{
		if (m_pTexture != nullptr)
		{
			const auto& pos = GetOwner()->GetTransform().GetWorldPosition();
			Renderer::GetInstance().RenderTexture(*m_pTexture, pos.x, pos.y, m_Scale);
		}
	}
}