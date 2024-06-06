#ifndef LIVESCOMPONENT_H
#define LIVESCOMPONENT_H
#include "Component.h"

namespace dae
{
	class Subject;
	class Observer;

	class LivesComponent final : public Component
	{
	public:
		LivesComponent(GameObject* pOwner);
		~LivesComponent();

		LivesComponent(const LivesComponent& other) = delete;
		LivesComponent(LivesComponent&& other) = delete;
		LivesComponent& operator=(const LivesComponent& other) = delete;
		LivesComponent& operator=(LivesComponent&& other) = delete;

		virtual void Update(float) override {};
		virtual void Render(float) const override {};

		void LowerLives();
		void LowerLives(int amount);
		void SetLives(int health);
		void AddObserver(Observer* pObserver);
		int GetLives() const;

	private:
		int m_CurrentLives;

		Subject* m_pSubject;
	};
}

#endif // ! LIVESCOMPONENT_H
