#include "Command.h"
#include "GameObject.h"
#include "CounterComponent.h"

dae::Command::Command()
{
}

dae::Command::~Command()
{
}

dae::MoveCommand::MoveCommand(GameObject* pGameObject, glm::vec3 dir, float speed)
	: Command{}
	, m_pGameObject{ pGameObject }
	, m_MoveDir{ dir }
	, m_MoveSpeed{ speed }
{
}

void dae::MoveCommand::Execute(float elapsedSec)
{
	GetGameObject()->SetLocalPosition(GetGameObject()->GetTransform().GetLocalPosition() + (m_MoveDir * m_MoveSpeed * elapsedSec));
}

dae::KillCommand::KillCommand(GameObject* pGameObject)
	: Command{ }
	, m_pGameObject{ pGameObject }
{
}

void dae::KillCommand::Execute(float)
{
	if (GetGameObject()->HasComponent<CounterComponent>())
	{
		GetGameObject()->GetComponent<CounterComponent>()->IncrementCount(-1);
	}
}

dae::ScoreSmallCommand::ScoreSmallCommand(GameObject* pGameObject)
	: Command{ }
	, m_pGameObject{ pGameObject }
{
}

void dae::ScoreSmallCommand::Execute(float)
{
	if (GetGameObject()->HasComponent<CounterComponent>())
	{
		GetGameObject()->GetComponent<CounterComponent>()->IncrementCount(100);
	}
}
