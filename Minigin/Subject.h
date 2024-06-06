#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>

namespace dae
{
	class GameObject;
	class Observer;
	enum class Event;

	class Subject final
	{
	private:
		std::vector<Observer*> m_pObservers;

	public:
		Subject();
		virtual ~Subject();

		void AddObserver(Observer* pObserver);
		void RemoveObserver(Observer* pObserver);
		void OnNotify(GameObject* obj, Event event);
	};
}

#endif // ! SUBJECT_H
