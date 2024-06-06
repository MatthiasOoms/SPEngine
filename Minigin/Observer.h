#ifndef OBSERVER_H
#define OBSERVER_H

namespace dae
{
	class GameObject;

	enum class Event
	{
		PlayerDeath,
		EnemyDeath,
		ObserverAdded
	};

	class Observer
	{
	public:
		virtual ~Observer() = default;
		virtual void OnNotify(GameObject* obj, Event event) = 0;
		virtual void OnSubjectRemoved(GameObject* obj) = 0;
	};
}

#endif // ! OBSERVER_H
