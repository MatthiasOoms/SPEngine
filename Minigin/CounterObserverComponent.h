#pragma once
#include <string>
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class GameObject;

	class CounterObserverComponent final : public Component, public Observer
	{
	public:
		virtual void Update(float) override {};
		virtual void Render(float) const override {};

		CounterObserverComponent(GameObject* pObj);
		virtual ~CounterObserverComponent();

		virtual void OnNotify(GameObject* obj, Event event) override;
		void UpdateText(GameObject* obj);

		void SetPrefix(const std::string& prefix) { m_Prefix = prefix; }
		void SetSuffix(const std::string& suffix) { m_Suffix = suffix; }

	private:
		std::string m_CountText;
		std::string m_Prefix;
		std::string m_Suffix;
	};
}