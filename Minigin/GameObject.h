#pragma once
#include "Transform.h"
#include <memory>
#include <vector>

namespace dae
{
	class Component;

	class GameObject final
	{
	public:
		GameObject();
		~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;

		void Update(const float deltaTime);
		void Render(const float deltaTime) const;
		Transform& GetTransform() const;
		
		template <typename Comp> std::shared_ptr<Comp> AddComponent();
		template <typename Comp> std::shared_ptr<Comp> GetComponent() const;
		template <typename Comp> bool HasComponent() const;
		template <typename Comp> void RemoveComponent();

		void SetLocalPosition(const glm::vec3& pos);
		void SetLocalPosition(const float x, const float y, const float z);

	private:
		std::unique_ptr<Transform> m_pTransform;
		std::vector<std::shared_ptr<Component>> m_pComponents;
		bool m_IsPositionDirty;

		const glm::vec3& GetLocalPosition() const;
		const glm::vec3& GetWorldPosition();
	};

	template<typename Comp>
	inline std::shared_ptr<Comp> GameObject::AddComponent()
	{
		static_assert(std::is_base_of<Component, Comp>(), "This is not a derived class of Component");

		auto temp = std::make_shared<Comp>(this);
		m_pComponents.push_back(std::move(temp));
		return std::move(temp);
	}

	template<typename Comp>
	inline std::shared_ptr<Comp> GameObject::GetComponent() const
	{
		Comp* temp;
		for (size_t idx{}; idx < m_pComponents.size(); idx++)
		{
			temp = dynamic_cast<Comp*>(m_pComponents[idx].get());
			if (temp != nullptr)
			{
				return std::make_shared<Comp>(m_pComponents[idx].get());
			}
		}
		return {};
	}

	template<typename Comp>
	inline void GameObject::RemoveComponent()
	{
		Comp* temp;
		for (size_t idx{}; idx < m_pComponents.size(); idx++)
		{
			temp = dynamic_cast<Comp*>(m_pComponents[idx].get());
			if (temp != nullptr)
			{
				m_pComponents[idx].reset();

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
			temp = dynamic_cast<Comp*>(m_pComponents[idx].get());
			if (temp != nullptr)
			{
				return true;
			}
		}
		return false;
	}
}
