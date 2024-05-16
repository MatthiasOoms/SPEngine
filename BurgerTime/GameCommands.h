#pragma once
#include "Command.h"

namespace dae
{
	class GameObject;

	class MoveStartCommand final : public Command
	{
	private:
		GameObject* m_pGameObject;
	protected:
		GameObject* GetGameObject() { return m_pGameObject; }
	public:
		MoveStartCommand(GameObject* pGameObject);

		virtual ~MoveStartCommand() override = default;
		MoveStartCommand(const MoveStartCommand& other) = delete;
		MoveStartCommand(MoveStartCommand&& other) = delete;
		MoveStartCommand& operator=(const MoveStartCommand& other) = delete;
		MoveStartCommand& operator=(MoveStartCommand&& other) = delete;

		void Execute(float elapsedSec) override;
	};

	class ClimbStartCommand final : public Command
	{
	private:
		GameObject* m_pGameObject;
	protected:
		GameObject* GetGameObject() { return m_pGameObject; }
	public:
		ClimbStartCommand(GameObject* pGameObject);

		virtual ~ClimbStartCommand() override = default;
		ClimbStartCommand(const ClimbStartCommand& other) = delete;
		ClimbStartCommand(ClimbStartCommand&& other) = delete;
		ClimbStartCommand& operator=(const ClimbStartCommand& other) = delete;
		ClimbStartCommand& operator=(ClimbStartCommand&& other) = delete;

		void Execute(float elapsedSec) override;
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

	class ClimbEndCommand final : public Command
	{
	private:
		GameObject* m_pGameObject;
	protected:
		GameObject* GetGameObject() { return m_pGameObject; }
	public:
		ClimbEndCommand(GameObject* pGameObject);

		virtual ~ClimbEndCommand() override = default;
		ClimbEndCommand(const ClimbEndCommand& other) = delete;
		ClimbEndCommand(ClimbEndCommand&& other) = delete;
		ClimbEndCommand& operator=(const ClimbEndCommand& other) = delete;
		ClimbEndCommand& operator=(ClimbEndCommand&& other) = delete;

		void Execute(float elapsedSec) override;
	};

	class MoveEndCommand final : public Command
	{
	private:
		GameObject* m_pGameObject;
	protected:
		GameObject* GetGameObject() { return m_pGameObject; }
	public:
		MoveEndCommand(GameObject* pGameObject);

		virtual ~MoveEndCommand() override = default;
		MoveEndCommand(const MoveEndCommand& other) = delete;
		MoveEndCommand(MoveEndCommand&& other) = delete;
		MoveEndCommand& operator=(const MoveEndCommand& other) = delete;
		MoveEndCommand& operator=(MoveEndCommand&& other) = delete;

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
		std::string m_MusicPath;
	protected:
		std::string GetScene() { return m_Scene; }
		std::string GetMusicPath() { return m_MusicPath; }
	public:
		SceneSwapCommand(std::string scene, std::string musicPath);

		virtual ~SceneSwapCommand() override = default;
		SceneSwapCommand(const SceneSwapCommand& other) = delete;
		SceneSwapCommand(SceneSwapCommand&& other) = delete;
		SceneSwapCommand& operator=(const SceneSwapCommand& other) = delete;
		SceneSwapCommand& operator=(SceneSwapCommand&& other) = delete;

		void Execute(float elapsedSec) override;
	};
}


