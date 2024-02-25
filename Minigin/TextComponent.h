#pragma once
#include "Component.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include <memory>
#include <string>
namespace dae
{
	class GameObject;
	class Texture2D;
	class Transform;
	class Font;

	class TextComponent final : public UpdateComponent
	{
	public:
		TextComponent(GameObject* pOwner);
		virtual ~TextComponent() = default;

		TextComponent(const TextComponent& other) = delete;
		TextComponent(TextComponent&& other) = delete;
		TextComponent& operator=(const TextComponent& other) = delete;
		TextComponent& operator=(TextComponent&& other) = delete;

		virtual void Update(float) override;

		void SetText(const std::string& text);
		void SetFont(const std::shared_ptr<Font>& font);

	private:
		bool m_NeedsUpdate;
		std::string m_Text;
		std::shared_ptr<Font> m_pFont;

		// Add ptr to GameObject in Interface classes
		// Now there's only access in Update and Render
	};
}

