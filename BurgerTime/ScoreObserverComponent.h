#pragma once
#include <string>
#include <vector>
#include "Component.h"
#include "Observer.h"

namespace dae
{
	class GameObject;
	class ScoreComponent;
	class Subject;

	class ScoreObserverComponent final : public Component, public Observer
	{
	public:
		virtual void Update(float) override {};
		virtual void Render(float) const override {};

		ScoreObserverComponent(GameObject* pObj);
		virtual ~ScoreObserverComponent();

		virtual void OnNotify(GameObject* obj, Event event) override;
		virtual void OnSubjectRemoved(GameObject* obj) override;
		void UpdateText(GameObject* obj);

	private:
		std::string m_ScoreText;
		std::vector<Subject*> m_pSubjects;
	};
}