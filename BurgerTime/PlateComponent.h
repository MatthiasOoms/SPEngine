#ifndef PLATECOMPONENT_H
#define PLATECOMPONENT_H
#include <Component.h>
#include <vector>
#include <string>

namespace dae
{
	class GameObject;

	class PlateComponent : public UpdateComponent
	{
	public:
		PlateComponent(GameObject* pOwner);
		virtual ~PlateComponent() = default;

		virtual void Update(float elapsedSec) override;

		void RegisterObjects();
		void RegisterObjects(std::string sceneName);

	private:
		std::vector<GameObject*> m_pIngredients;
	};
}

#endif // ! PLATECOMPONENT_H
