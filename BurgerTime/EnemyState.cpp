#include "EnemyState.h"
#include "GameObject.h"

dae::EnemyState::EnemyState(GameObject* player)
	: m_pEnemy{ player }
{
}
