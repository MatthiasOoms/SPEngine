#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::shared_ptr<GameObject> object)
{
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(std::shared_ptr<GameObject> object)
{
	m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), object), m_objects.end());
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update(const float deltaTime)
{
	for(size_t i{}; i < m_objects.size(); ++i)
	{
		m_objects[i]->Update(deltaTime);
	}

	// Remove dead objects
	for (int i{ static_cast<int>(m_objects.size() - 1) }; i >= 0; i--)
	{
		if (m_objects[i]->IsDead())
		{
			// If object has parent, set parent of children
			if (m_objects[i]->GetParent() != nullptr)
			{
				for (int j{}; j < m_objects[i]->GetChildCount(); j++)
				{
					m_objects[i]->GetChildAt(j)->SetParent(m_objects[i]->GetParent(), true);
				}
			}
			else
			{
				// If object has no parent, set children to nullptr
				for (int j{}; j < m_objects[i]->GetChildCount(); j++)
				{
					m_objects[i]->GetChildAt(j)->SetParent(nullptr, true);
				}
			}

			// Remove object
			m_objects[i].reset();
			Remove(m_objects[i]);
		}
	}
}

void Scene::Render(const float deltaTime) const
{
	for (const auto& object : m_objects)
	{
		object->Render(deltaTime);
	}
}

