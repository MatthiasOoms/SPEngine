#ifndef FPSCOMPONENT_H
#define FPSCOMPONENT_H
#include "Component.h"

namespace dae
{
    class TextComponent;

    class FPSComponent final : public UpdateComponent
    {
    public:
        FPSComponent(GameObject* pOwner);
        virtual ~FPSComponent() {};

        FPSComponent(const FPSComponent& other) = delete;
        FPSComponent(FPSComponent&& other) = delete;
        FPSComponent& operator=(const FPSComponent& other) = delete;
        FPSComponent& operator=(FPSComponent&& other) = delete;

        virtual void Update(float elapsedSec);

    private:
        TextComponent* m_pTextComponent;
    };
}

#endif // ! FPSCOMPONENT_H
