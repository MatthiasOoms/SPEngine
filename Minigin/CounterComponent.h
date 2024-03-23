#pragma once
#include "Component.h"
#include <string>

namespace dae
{
	class Subject;
	class Observer;

	class CounterComponent final : public Component
	{
	public:
		CounterComponent(GameObject* pOwner);
		~CounterComponent();

		CounterComponent(const CounterComponent& other) = delete;
		CounterComponent(CounterComponent&& other) = delete;
		CounterComponent& operator=(const CounterComponent& other) = delete;
		CounterComponent& operator=(CounterComponent&& other) = delete;

		virtual void Update(float) override {};
		virtual void Render(float) const override {};

		void IncrementCount(int amount);
		void SetCount(int health);
		void SetName(std::string name);
		void AddObserver(Observer* pObserver);
		int GetCount() const;
		std::string GetName() const;

	private:
		int m_Count;
		std::string m_Name;
		Subject* m_pSubject;
	};
}