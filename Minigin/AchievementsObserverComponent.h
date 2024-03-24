#pragma once
// These things make sure the sign mismatch error isn't thrown in matchmakingtypes.h
#pragma warning(push)
#pragma warning(disable : 6340)
// Some include(s) with unfixable warnings
#include <steam_api.h>
#pragma warning(pop)

#include "Component.h"
#include "Observer.h"
#include "SteamAchievements.h"

namespace dae
{
	class GameObject;

	class AchievementsObserverComponent final : public Component, public Observer
	{
	public:
		virtual void Update(float) override {};
		virtual void Render(float) const override {};

		AchievementsObserverComponent(GameObject* pObj);
		virtual ~AchievementsObserverComponent() = default;

		virtual void OnNotify(GameObject* obj, Event event) override;

	private:
		void UnlockAchievement(const char* id);

		bool m_HasAchWinOne;
	};
}