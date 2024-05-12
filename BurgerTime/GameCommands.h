#pragma once
#include "Command.h"

namespace dae
{
	class GameObject;

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

	class SceneSwapCommand final : public Command
	{
	private:
		std::string m_Scene;
	protected:
		std::string GetScene() { return m_Scene; }
	public:
		SceneSwapCommand(std::string m_Scene);

		virtual ~SceneSwapCommand() override = default;
		SceneSwapCommand(const SceneSwapCommand& other) = delete;
		SceneSwapCommand(SceneSwapCommand&& other) = delete;
		SceneSwapCommand& operator=(const SceneSwapCommand& other) = delete;
		SceneSwapCommand& operator=(SceneSwapCommand&& other) = delete;

		void Execute(float elapsedSec) override;
	};
}


