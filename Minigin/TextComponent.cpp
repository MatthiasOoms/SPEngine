#include <stdexcept>
#include "TextComponent.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "Font.h"
#include "TextureComponent.h"

namespace dae
{
    TextComponent::TextComponent(GameObject* pOwner)
        : UpdateComponent(pOwner)
        , m_NeedsUpdate{ false }
    {
        // Add TextureComponent if not already made
        if (!GetOwner()->HasComponent<TextureComponent>())
        {
            m_pTextureComponent = GetOwner()->AddComponent<TextureComponent>();
        }
        else
        {
            m_pTextureComponent = GetOwner()->GetComponent<TextureComponent>();
        }
    }

    void TextComponent::Update(float)
    {
        if (m_NeedsUpdate)
        {
            const SDL_Color color = { 255,255,255 }; // only white text is supported now
            const auto surf = TTF_RenderText_Blended(m_pFont->GetFont(), m_Text.c_str(), color);
            if (surf == nullptr)
            {
                throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
            }
            auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
            if (texture == nullptr)
            {
                throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
            }
            SDL_FreeSurface(surf);

            // Set the texture
            m_pTextureComponent->SetTexture(std::make_shared<Texture2D>(texture));

            m_NeedsUpdate = false;
        }
    }

    void TextComponent::SetText(const std::string& text)
    {
        m_Text = text;
        m_NeedsUpdate = true;
    }

    void TextComponent::SetFont(const std::shared_ptr<Font>& font)
    {
        m_pFont = font;
    }
}
