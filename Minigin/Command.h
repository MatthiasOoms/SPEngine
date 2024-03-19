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
		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

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

		virtual ~MoveCommand() override = default;
		MoveCommand(const MoveCommand& other) = delete;
		MoveCommand(MoveCommand&& other) = delete;
		MoveCommand& operator=(const MoveCommand& other) = delete;
		MoveCommand& operator=(MoveCommand&& other) = delete;

		void Execute(float elapsedSec) override;
	};

	class KillCommand final : public Command
	{
	private:
		GameObject* m_pGameObject;
	protected:
		GameObject* GetGameObject() { return m_pGameObject; }
	public:
		KillCommand(GameObject* pGameObject);

		virtual ~KillCommand() override = default;
		KillCommand(const KillCommand& other) = delete;
		KillCommand(KillCommand&& other) = delete;
		KillCommand& operator=(const KillCommand& other) = delete;
		KillCommand& operator=(KillCommand&& other) = delete;

		void Execute(float elapsedSec) override;
	};

	class ScoreSmallCommand final : public Command
	{
	private:
		GameObject* m_pGameObject;
	protected:
		GameObject* GetGameObject() { return m_pGameObject; }
	public:
		ScoreSmallCommand(GameObject* pGameObject);

		virtual ~ScoreSmallCommand() override = default;
		ScoreSmallCommand(const ScoreSmallCommand& other) = delete;
		ScoreSmallCommand(ScoreSmallCommand&& other) = delete;
		ScoreSmallCommand& operator=(const ScoreSmallCommand& other) = delete;
		ScoreSmallCommand& operator=(ScoreSmallCommand&& other) = delete;

		void Execute(float elapsedSec) override;
	};
}

