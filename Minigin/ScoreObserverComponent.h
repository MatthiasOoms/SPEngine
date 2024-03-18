#pragma once
#include <string>
#include "Component.h"
#include "Observer.h"

// TODO: Maybe make Score and Lives into a CounterComponent so I only need 1 component and 1 observer
namespace dae
{
	class GameObject;
	class ScoreComponent;

	class ScoreObserverComponent final : public Component, public Observer
	{
	public:
		virtual void Update(float) override {};
		virtual void Render(float) const override {};

		ScoreObserverComponent(GameObject* pObj);
		virtual ~ScoreObserverComponent();

		virtual void OnNotify(GameObject* obj, Event event) override;
		void UpdateText(GameObject* obj);

	private:
		std::string m_ScoreText;
	};
}