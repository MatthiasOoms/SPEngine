#ifndef COMPONENT_H
#define COMPONENT_H
#include <memory>

namespace dae
{
	class GameObject;

	class Component
	{
	public:
		Component(GameObject* pOwner);

		virtual ~Component() = default;
		Component(const Component& other) = delete;
		Component(Component&& other) = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) = delete;

		virtual void Update(float elapsedSec) = 0;
		virtual void Render(float elapsedSec) const = 0;

	protected:
		GameObject* GetOwner() const { return m_pOwner; }

	private:
		GameObject* m_pOwner;
	};

	class UpdateComponent : public Component
	{
	public:
		UpdateComponent(GameObject* pOwner);
		virtual ~UpdateComponent() = default;

		UpdateComponent(const UpdateComponent& other) = delete;
		UpdateComponent(UpdateComponent&& other) = delete;
		UpdateComponent& operator=(const UpdateComponent& other) = delete;
		UpdateComponent& operator=(UpdateComponent&& other) = delete;

		virtual void Update(float elapsedSec) override = 0;
		virtual void Render(float) const override {};
	};

	class RenderComponent : public Component
	{
	public:
		RenderComponent(GameObject* pOwner);
		virtual ~RenderComponent() = default;

		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;

		virtual void Update(float) override {};
		virtual void Render(float elapsedSec) const override = 0;
	};
};

#endif // ! COMPONENT_H
