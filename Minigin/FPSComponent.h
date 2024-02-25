#pragma once
#include "Component.h"
#include <string>
#include <memory>

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
        std::shared_ptr<TextComponent> m_pTextComponent;
    };
}