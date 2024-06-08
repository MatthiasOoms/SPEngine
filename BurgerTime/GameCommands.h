#ifndef GAMECOMMANDS_H
#define GAMECOMMANDS_H
#include <memory>
#include "Command.h"
#include "Texture2D.h"

namespace dae
{
	class GameObject;

	class WalkStartCommand final : public Command
	{
	private:
		GameObject* m_pGameObject;
		float m_MoveSpeed;
		std::shared_ptr<Texture2D> m_PeterWalkTexture;
		std::shared_ptr<Texture2D> m_HotdogWalkTexture;
		std::shared_ptr<Texture2D> m_EggWalkTexture;
		std::shared_ptr<Texture2D> m_PickleWalkTexture;

		void HandlePlayer();
		void HandleEnemy();
	protected:
		GameObject* GetGameObject() const{ return m_pGameObject; }
	public:
		WalkStartCommand(GameObject* pGameObject, float moveSpeed);

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
		GameObject* m_pLadder;
		float m_MoveSpeed;
		std::shared_ptr<Texture2D> m_PeterClimbTexture;
		std::shared_ptr<Texture2D> m_HotdogClimbTexture;
		std::shared_ptr<Texture2D> m_EggClimbTexture;
		std::shared_ptr<Texture2D> m_PickleClimbTexture;

		void HandlePlayer();
		void HandleEnemy();
	protected:
		GameObject* GetGameObject() const{ return m_pGameObject; }
	public:
		ClimbStartCommand(GameObject* pGameObject, float moveSpeed);
		ClimbStartCommand(GameObject* pGameObject, GameObject* pLadder, float moveSpeed);

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
		std::shared_ptr<Texture2D> m_PeterWalkTexture;
	protected:
		GameObject* GetGameObject() const { return m_pGameObject; }
	public:
		WalkCommand(GameObject* pGameObject, float speed);

		virtual ~WalkCommand() override = default;
		WalkCommand(const WalkCommand& other) = delete;
		WalkCommand(WalkCommand&& other) = delete;
		WalkCommand& operator=(const WalkCommand& other) = delete;
		WalkCommand& operator=(WalkCommand&& other) = delete;

		void Execute(float elapsedSec) override;
	};

	class FallCommand final : public Command
	{
	private:
		GameObject* m_pGameObject;
		float m_MoveSpeed;
	protected:
		GameObject* GetGameObject() const { return m_pGameObject; }
	public:
		FallCommand(GameObject* pGameObject, float speed);

		virtual ~FallCommand() override = default;
		FallCommand(const FallCommand& other) = delete;
		FallCommand(FallCommand&& other) = delete;
		FallCommand& operator=(const FallCommand& other) = delete;
		FallCommand& operator=(FallCommand&& other) = delete;

		void Execute(float elapsedSec) override;
	};

	class ClimbCommand final : public Command
	{
	private:
		GameObject* m_pGameObject;
		float m_ClimbSpeed;
		std::shared_ptr<Texture2D> m_PeterIdleTexture;
		std::shared_ptr<Texture2D> m_HotdogWalkTexture;
		std::shared_ptr<Texture2D> m_EggWalkTexture;
		std::shared_ptr<Texture2D> m_PickleWalkTexture;

	protected:
		GameObject* GetGameObject() const{ return m_pGameObject; }
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
		std::shared_ptr<Texture2D> m_PeterIdleTexture;
		std::shared_ptr<Texture2D> m_HotdogWalkTexture;
		std::shared_ptr<Texture2D> m_EggWalkTexture;
		std::shared_ptr<Texture2D> m_PickleWalkTexture;

		void HandlePlayer();
		void HandleEnemy();
	protected:
		GameObject* GetGameObject() const{ return m_pGameObject; }
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
		std::shared_ptr<Texture2D> m_PeterIdleTexture;
	protected:
		GameObject* GetGameObject() const{ return m_pGameObject; }
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
		GameObject* GetGameObject() const{ return m_pGameObject; }
	public:
		KillCommand(GameObject* pGameObject);

		virtual ~KillCommand() override = default;
		KillCommand(const KillCommand& other) = delete;
		KillCommand(KillCommand&& other) = delete;
		KillCommand& operator=(const KillCommand& other) = delete;
		KillCommand& operator=(KillCommand&& other) = delete;

		void Execute(float elapsedSec) override;
	};

	class HotdogKilledCommand final : public Command
	{
	private:
		GameObject* m_pGameObject;
	protected:
		GameObject* GetGameObject() const{ return m_pGameObject; }
	public:
		HotdogKilledCommand(GameObject* pGameObject);

		virtual ~HotdogKilledCommand() override = default;
		HotdogKilledCommand(const HotdogKilledCommand& other) = delete;
		HotdogKilledCommand(HotdogKilledCommand&& other) = delete;
		HotdogKilledCommand& operator=(const HotdogKilledCommand& other) = delete;
		HotdogKilledCommand& operator=(HotdogKilledCommand&& other) = delete;

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

	class SceneNextCommand final : public Command
	{
	public:
		SceneNextCommand();

		virtual ~SceneNextCommand() override = default;
		SceneNextCommand(const SceneNextCommand& other) = delete;
		SceneNextCommand(SceneNextCommand&& other) = delete;
		SceneNextCommand& operator=(const SceneNextCommand& other) = delete;
		SceneNextCommand& operator=(SceneNextCommand&& other) = delete;

		void Execute(float elapsedSec) override;
	};

	class ToggleSoundCommand final : public Command
	{
	public:
		ToggleSoundCommand();

		virtual ~ToggleSoundCommand() override = default;
		ToggleSoundCommand(const ToggleSoundCommand& other) = delete;
		ToggleSoundCommand(ToggleSoundCommand&& other) = delete;
		ToggleSoundCommand& operator=(const ToggleSoundCommand& other) = delete;
		ToggleSoundCommand& operator=(ToggleSoundCommand&& other) = delete;

		void Execute(float elapsedSec) override;
	};

	class ThrowPepperCommand final : public Command
	{
	private:
		GameObject* m_pGameObject;

	protected:
		GameObject* GetGameObject() const { return m_pGameObject; }

	public:
		ThrowPepperCommand(GameObject* pOwner);

		virtual ~ThrowPepperCommand() override = default;
		ThrowPepperCommand(const ThrowPepperCommand& other) = delete;
		ThrowPepperCommand(ThrowPepperCommand&& other) = delete;
		ThrowPepperCommand& operator=(const ThrowPepperCommand& other) = delete;
		ThrowPepperCommand& operator=(ThrowPepperCommand&& other) = delete;

		void Execute(float elapsedSec) override;
	};
}

#endif // ! GAMECOMMANDS_H
