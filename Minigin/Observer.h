#pragma once

namespace dae
{
	class GameObject;

	enum class Event
	{
		AddObserver,
		PlayerDeath,
		EnemyDeath,
		ScoreChange
	};

	class Observer
	{
	public:
		virtual ~Observer() {};
		virtual void OnNotify(GameObject* obj, Event event) = 0;
	};
}