#ifndef PLATECOMPONENT_H
#define PLATECOMPONENT_H
#include <Component.h>

namespace dae
{
	class GameObject;

	class PlateComponent : public UpdateComponent
	{
	public:
		PlateComponent(GameObject* pOwner);
		virtual ~PlateComponent() = default;

		virtual void Update(float elapsedSec) override;
	};
}

#endif // ! PLATECOMPONENT_H
