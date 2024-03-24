#pragma once
// These things make sure the sign mismatch error isn't thrown in matchmakingtypes.h
#pragma warning(push)
#pragma warning(disable : 6340)
// Some include(s) with unfixable warnings
#include <steam_api.h>
#pragma warning(pop)

namespace dae
{
#define _ACH_ID( id, name ) { id, #id, name, "", 0, 0 }
	struct Achievement_t
	{
		int m_AchievementID;
		const char* m_pAchievementID;
		char m_AchievementName[128];
		char m_AchievementDescription[256];
		bool m_IsAchieved;
		int m_IconImageInt;
	};

	class SteamAchievements final
	{
	private:
		uint64 m_AppID; // Our current AppID
		Achievement_t* m_pAchievements; // Achievements data
		int m_NumAchievements; // The number of Achievements
		bool m_IsInitialized; // Have we called Request stats and received the callback?

	public:
		SteamAchievements(Achievement_t* achievements, int numAchievements);
		~SteamAchievements();

		bool RequestStats();
		bool SetAchievement(const char* ID);

		STEAM_CALLBACK(SteamAchievements, OnUserStatsReceived, UserStatsReceived_t,
			m_CallbackUserStatsReceived);
		STEAM_CALLBACK(SteamAchievements, OnUserStatsStored, UserStatsStored_t,
			m_CallbackUserStatsStored);
		STEAM_CALLBACK(SteamAchievements, OnAchievementStored,
			UserAchievementStored_t, m_CallbackAchievementStored);
	};
}