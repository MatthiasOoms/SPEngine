#pragma once
#include "Command.h"

namespace dae
{
	class GameObject;

	class WalkStartCommand final : public Command
	{
	private:
		GameObject* m_pGameObject;
	protected:
		GameObject* GetGameObject() { return m_pGameObject; }
	public:
		WalkStartCommand(GameObject* pGameObject);

		virtual ~WalkStartCommand() override = default;
		WalkStartCommand(const WalkStartCommand& other) = delete;
		WalkStartCommand(WalkStartCommand&& other) = delete;
		WalkStartCommand& operator=(const WalkStartCommand& other) = delete;
		WalkStartCommand& operator=(WalkStartCommand&& other) = delete;

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

	class WalkCommand final : public Command
	{
	private:
		GameObject* m_pGameObject;
		float m_MoveSpeed;
		//float m_Acceleration; // Not present in my game
	protected:
		GameObject* GetGameObject() { return m_pGameObject; }
	public:
		WalkCommand(GameObject* pGameObject, float speed);

		virtual ~WalkCommand() override = default;
		WalkCommand(const WalkCommand& other) = delete;
		WalkCommand(WalkCommand&& other) = delete;
		WalkCommand& operator=(const WalkCommand& other) = delete;
		WalkCommand& operator=(WalkCommand&& other) = delete;

		void Execute(float elapsedSec) override;
	};

	class ClimbCommand final : public Command
	{
	private:
		GameObject* m_pGameObject;
		float m_ClimbSpeed;
		//float m_Acceleration; // Not present in my game
	protected:
		GameObject* GetGameObject() { return m_pGameObject; }
	public:
		ClimbCommand(GameObject* pGameObject, float speed);

		virtual ~ClimbCommand() override = default;
		ClimbCommand(const ClimbCommand& other) = delete;
		ClimbCommand(ClimbCommand&& other) = delete;
		ClimbCommand& operator=(const ClimbCommand& other) = delete;
		ClimbCommand& operator=(ClimbCommand&& other) = delete;

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

	class WalkEndCommand final : public Command
	{
	private:
		GameObject* m_pGameObject;
	protected:
		GameObject* GetGameObject() { return m_pGameObject; }
	public:
		WalkEndCommand(GameObject* pGameObject);

		virtual ~WalkEndCommand() override = default;
		WalkEndCommand(const WalkEndCommand& other) = delete;
		WalkEndCommand(WalkEndCommand&& other) = delete;
		WalkEndCommand& operator=(const WalkEndCommand& other) = delete;
		WalkEndCommand& operator=(WalkEndCommand&& other) = delete;

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


