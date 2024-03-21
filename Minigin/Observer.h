#pragma once

namespace dae
{
	class GameObject;

	enum class Event
	{
		ObserverAdd,
		CountChange
	};

	class Observer
	{
	public:
		virtual ~Observer() {};
		virtual void OnNotify(GameObject* obj, Event event) = 0;
	};
}