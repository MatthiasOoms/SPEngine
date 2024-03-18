#include "SteamAchievements.h"

#pragma warning(push)
#pragma warning(disable : 4996)

dae::SteamAchievements::SteamAchievements(Achievement_t* achievements, int numAchievements) :
    m_AppID(0),
    m_IsInitialized(false),
    m_CallbackUserStatsReceived(this, &SteamAchievements::OnUserStatsReceived),
    m_CallbackUserStatsStored(this, &SteamAchievements::OnUserStatsStored),
    m_CallbackAchievementStored(this, &SteamAchievements::OnAchievementStored)
{
    m_AppID = SteamUtils()->GetAppID();
    m_pAchievements = achievements;
    m_NumAchievements = numAchievements;
    RequestStats();
}

dae::SteamAchievements::~SteamAchievements()
{
}

bool dae::SteamAchievements::RequestStats()
{
	// Is Steam loaded? If not we can't get stats.
	if (NULL == SteamUserStats() || NULL == SteamUser())
	{
		return false;
	}
	// Is the user logged on?  If not we can't get stats.
	if (!SteamUser()->BLoggedOn())
	{
		return false;
	}
	// Request user stats.
	return SteamUserStats()->RequestCurrentStats();
}

bool dae::SteamAchievements::SetAchievement(const char* ID)
{
	// Have we received a call back from Steam yet?
	if (m_IsInitialized)
	{
		SteamUserStats()->SetAchievement(ID);
		return SteamUserStats()->StoreStats();
	}
	// If not then we can't set achievements yet
	return false;
}

void dae::SteamAchievements::OnUserStatsReceived(UserStatsReceived_t* pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_AppID == pCallback->m_nGameID)
	{
		if (k_EResultOK == pCallback->m_eResult)
		{
			m_IsInitialized = true;

			// load achievements
			for (int iAch = 0; iAch < m_NumAchievements; ++iAch)
			{
				Achievement_t& ach = m_pAchievements[iAch];

				SteamUserStats()->GetAchievement(ach.m_pAchievementID, &ach.m_IsAchieved);
				_snprintf(ach.m_AchievementName, sizeof(ach.m_AchievementName), "%s",
					SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pAchievementID,
						"name"));
				_snprintf(ach.m_AchievementDescription, sizeof(ach.m_AchievementDescription), "%s",
					SteamUserStats()->GetAchievementDisplayAttribute(ach.m_pAchievementID,
						"desc"));
			}
		}
		else
		{
			char buffer[128];
			_snprintf(buffer, 128, "RequestStats - failed, %d\n", pCallback->m_eResult);
		}
	}
}

void dae::SteamAchievements::OnUserStatsStored(UserStatsStored_t* pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_AppID == pCallback->m_nGameID)
	{
		if (k_EResultOK == pCallback->m_eResult)
		{
		}
		else
		{
			char buffer[128];
			_snprintf(buffer, 128, "StatsStored - failed, %d\n", pCallback->m_eResult);
		}
	}
}

void dae::SteamAchievements::OnAchievementStored(UserAchievementStored_t * pCallback)
{
	// we may get callbacks for other games' stats arriving, ignore them
	if (m_AppID == pCallback->m_nGameID)
	{
	}
}
#pragma warning(pop)