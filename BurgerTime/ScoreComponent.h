#ifndef SCORECOMPONENT_H
#define SCORECOMPONENT_H
#include "Component.h"

namespace dae
{
	class Subject;
	class Observer;

	class ScoreComponent final : public Component
	{
	public:
		ScoreComponent(GameObject* pOwner);
		~ScoreComponent();

		ScoreComponent(const ScoreComponent& other) = delete;
		ScoreComponent(ScoreComponent&& other) = delete;
		ScoreComponent& operator=(const ScoreComponent& other) = delete;
		ScoreComponent& operator=(ScoreComponent&& other) = delete;

		virtual void Update(float) override {};
		virtual void Render(float) const override {};

		void IncreaseScore(int amount);
		void SetScore(int score);
		void AddObserver(Observer* pObserver);
		int GetScore() const;

	private:
		int m_Score;

		Subject* m_pSubject;
	};
}

#endif // ! SCORECOMPONENT_H
