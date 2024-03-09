#pragma once
#include "Component.h"
#include <vector>

namespace dae
{
	struct Transforms
	{
		float matrix[16] =
		{
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	};

	class GameObject3D
	{
	public:
		Transforms transform;
		int ID;
	};

	class GameObject3DAlt
	{
	public:
		Transforms* transform;
		int ID;
	};

	class ImGuiComponent : public UpdateComponent
	{
	public:
		ImGuiComponent(GameObject* pOwner);
		virtual ~ImGuiComponent();

		void RenderUI(float elapsedSec) override;

		ImGuiComponent(const ImGuiComponent& other) = delete;
		ImGuiComponent(ImGuiComponent&& other) = delete;
		ImGuiComponent& operator=(const ImGuiComponent& other) = delete;
		ImGuiComponent& operator=(ImGuiComponent&& other) = delete;

		virtual void Update(float elapsedSec) override;

		void PlotIntegers();
		void PlotObj();

	private:
		void BenchmarkIntegers(std::vector<int> intVec, int benchmarks);
		void BenchmarkObj(std::vector<GameObject3D> objVec, int benchmarks);
		void BenchmarkObjAlt(std::vector<GameObject3DAlt> objAltVec, int benchmarks);

		const int m_ArrSize{ 10'000'000 };
		const int m_MaxStepSize{ 1024 };
		std::vector<float> m_Steps{};
		std::vector<float> m_yDataIntegers{};
		std::vector<float> m_yDataObj{};
		std::vector<float> m_yDataObjAlt{};
	};
}
