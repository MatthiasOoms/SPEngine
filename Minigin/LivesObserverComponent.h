#pragma once
#include <string>
#include <vector>
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class GameObject;
	class LivesComponent;
	class Subject;

	class LivesObserverComponent final : public Component, public Observer
	{
	public:
		virtual void Update(float) override {};
		virtual void Render(float) const override {};

		LivesObserverComponent(GameObject* pObj);
		virtual ~LivesObserverComponent();

		virtual void OnNotify(GameObject* obj, Event event) override;
		virtual void OnSubjectRemoved(GameObject* obj) override;
		void UpdateText(GameObject* obj);

	private:
		std::string m_ScoreText;
		std::vector<Subject*> m_pSubjects;
	};
}