#pragma once
#include "TransformComponent.h"
#include <memory>
#include <vector>

namespace dae
{
	class Component;

	class GameObject final
	{
	public:
		GameObject();
		GameObject(GameObject* pParent);
		~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update(const float deltaTime);
		void Render(const float deltaTime) const;
		TransformComponent& GetTransform() const;

		template <typename Comp> Comp* AddComponent();
		template <typename Comp> Comp* GetComponent() const;
		template <typename Comp> bool HasComponent() const;
		template <typename Comp> void RemoveComponent();
		GameObject* GetParent() const;
		void SetParent(GameObject* pParent, bool keepWorldPosition);
		int GetChildCount() const;
		GameObject* GetChildAt(int idx) const;

		void SetLocalPosition(const glm::vec3& pos);
		void SetLocalPosition(const float x, const float y, const float z);

	private:
		std::unique_ptr<TransformComponent> m_pTransform;
		// Everything is owned by the scene, inside of smart_ptrs
		// why use smart ptrs inside of the objects

		// After quiz: Should I use smart ptr for parent and child or not?
		GameObject* m_pParent;
		std::vector<GameObject*> m_pChildren;
		std::vector<Component*> m_pComponents;
		bool m_IsPositionDirty;

		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);

		const glm::vec3& GetLocalPosition() const;
		const glm::vec3& GetWorldPosition();

		void UpdateWorldPosition();

		void SetPositionDirty();
	};

	template<typename Comp>
	inline Comp* GameObject::AddComponent()
	{
		// TODO: Implement check to see if Inherits from base class Component
		// Use a static_assert for it
		if (!std::is_base_of<Component, Comp>::value)
		{
			return nullptr;
		}
		Comp* temp{ new Comp{ this } };
		m_pComponents.push_back(temp);
		return temp;
	}

	template<typename Comp>
	inline Comp* GameObject::GetComponent() const
	{
		Comp* temp;
		for (size_t idx{}; idx < m_pComponents.size(); idx++)
		{
			temp = dynamic_cast<Comp*>(m_pComponents[idx]);
			if (temp != nullptr)
			{
				return temp;
			}
		}
		return nullptr;
	}

	template<typename Comp>
	inline void GameObject::RemoveComponent()
	{
		Comp* temp;
		for (size_t idx{}; idx < m_pComponents.size(); idx++)
		{
			temp = dynamic_cast<Comp*>(m_pComponents[idx]);
			if (temp != nullptr)
			{
				delete m_pComponents[idx];
				m_pComponents[idx] = nullptr;

				auto nth = m_pComponents.begin() + idx;
				m_pComponents.erase(nth);
			}
		}
		delete temp;
		temp = nullptr;
	}

	template<typename Comp>
	inline bool GameObject::HasComponent() const
	{
		Comp* temp;
		for (size_t idx{}; idx < m_pComponents.size(); idx++)
		{
			temp = dynamic_cast<Comp*>(m_pComponents[idx]);
			if (temp != nullptr)
			{
				return true;
			}
		}
		return false;
	}
}
