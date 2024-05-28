#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

std::vector<GameObject*> dae::Scene::GetObjectsByTag(std::string tag) const
{
	std::vector<GameObject*> tempVec;
	for (const auto& object : m_Objects)
	{
		if (object->GetTag() == tag)
		{
			tempVec.push_back(object.get());
		}
	}
	return tempVec;
}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	m_Objects.emplace_back(std::move(object));
}

void Scene::Remove(std::unique_ptr<GameObject>& object)
{
	m_Objects.erase(std::remove(m_Objects.begin(), m_Objects.end(), object), m_Objects.end());
}

void Scene::RemoveAll()
{
	m_Objects.clear();
}

void Scene::Update(const float deltaTime)
{
	for(size_t i{}; i < m_Objects.size(); ++i)
	{
		m_Objects[i]->Update(deltaTime);
	}

	// Remove dead objects
	for (int i{ static_cast<int>(m_Objects.size() - 1) }; i >= 0; i--)
	{
		if (m_Objects[i]->IsDead())
		{
			// If object has parent, set parent of children
			if (m_Objects[i]->GetParent() != nullptr)
			{
				for (int j{}; j < m_Objects[i]->GetChildCount(); j++)
				{
					m_Objects[i]->GetChildAt(j)->SetParent(m_Objects[i]->GetParent(), true);
				}
			}
			else
			{
				// If object has no parent, set children to nullptr
				for (int j{}; j < m_Objects[i]->GetChildCount(); j++)
				{
					m_Objects[i]->GetChildAt(j)->SetParent(nullptr, true);
				}
			}

			// Remove object
			m_Objects[i].reset();
			Remove(m_Objects[i]);
		}
	}
}

void Scene::Render(const float deltaTime) const
{
	for (const auto& object : m_Objects)
	{
		object->Render(deltaTime);
	}
}

