#pragma once
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;

	class Command
	{
	public:
		explicit Command();
		virtual ~Command();
		virtual void Execute(float) = 0;
	};

	class MoveCommand final : public Command
	{
	private:
		GameObject* m_pGameObject;
		glm::vec3 m_MoveDir;
		float m_MoveSpeed;
		//float m_Acceleration; // Not present in my game
	protected:
		GameObject* GetGameObject() { return m_pGameObject; }
	public:
		MoveCommand(GameObject* pGameObject, glm::vec3 dir, float speed);
		virtual ~MoveCommand() = default;
		void Execute(float elapsedSec) override;
	};
}

