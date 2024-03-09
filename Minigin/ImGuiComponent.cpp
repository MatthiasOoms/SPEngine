#include "ImGuiComponent.h"
#include "Renderer.h"

#include "imgui.h"
#include "imconfig.h"
#include "imgui_plot.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl3.h"

#include <chrono>
#include <numeric>

dae::ImGuiComponent::ImGuiComponent(GameObject* pOwner)
	: UpdateComponent(pOwner)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(Renderer::GetInstance().GetWindow(), SDL_GL_GetCurrentContext());
	ImGui_ImplOpenGL3_Init();

	// Plot step sizes
	for (int stepSize{ 1 }; stepSize <= m_MaxStepSize; stepSize *= 2)
	{
		m_Steps.push_back(float(stepSize));
	}
	for (size_t i{}; i < m_Steps.size(); ++i)
	{
		m_yDataIntegers.push_back(0);
		m_yDataObj.push_back(0);
		m_yDataObjAlt.push_back(0);
	}
}

dae::ImGuiComponent::~ImGuiComponent()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void dae::ImGuiComponent::Update(float)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	PlotIntegers();
	PlotObj();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void dae::ImGuiComponent::PlotIntegers()
{
	static int benchmarkCount = 10;
	ImGui::InputInt("# Samples", &benchmarkCount, 1, 10);

	// Get plot data
	if (ImGui::Button("Trash the cache!"))
	{
		// Plot data
		std::vector<int> intArr(m_ArrSize, int{});
		BenchmarkIntegers(intArr, benchmarkCount);
	}

	// Make plot
	ImGui::PlotConfig conf;
	conf.values.xs = m_Steps.data();
	conf.values.ys = m_yDataIntegers.data();
	conf.values.count = int(m_Steps.size());
	conf.values.color = ImColor{ 255, 0, 0 };
	conf.grid_x.show = false;
	conf.grid_y.show = true;
	conf.grid_y.size = 10'000.f;
	conf.scale.min = 0.f;
	conf.scale.max = 10'000.f;
	conf.tooltip.show = true;
	conf.tooltip.format = "x=%.2f, y=%.2f";
	conf.frame_size = ImVec2(200, 100);
	conf.line_thickness = 2.f;

	ImGui::Plot("IntPlot", conf);
}

void dae::ImGuiComponent::PlotObj()
{
	static int benchmarkCount = 100;
	ImGui::InputInt("# Samples", &benchmarkCount, 1, 10);

	// Get plot data
	if (ImGui::Button("Trash the cache with objects!"))
	{
		// Plot data
		std::vector<GameObject3D> objArr(m_ArrSize, GameObject3D{});
		BenchmarkObj(objArr, benchmarkCount);
	}
	ImGui::PlotConfig conf;
	conf.values.xs = m_Steps.data();
	conf.values.ys = m_yDataObj.data();
	conf.values.count = int(m_Steps.size());
	conf.values.color = ImColor{ 0, 255, 0 };
	conf.grid_x.show = false;
	conf.grid_y.show = true;
	conf.grid_y.size = 10'000.f;
	conf.scale.min = 0.f;
	conf.scale.max = 100'000.f;
	conf.tooltip.show = true;
	conf.tooltip.format = "x=%.2f, y=%.2f";
	conf.frame_size = ImVec2(200, 100);
	conf.line_thickness = 2.f;

	ImGui::Plot("ObjPlot", conf);

	if (ImGui::Button("Trash the cache with alternate objects!"))
	{
		// Plot data
		std::vector<GameObject3DAlt> objAltArr(m_ArrSize, GameObject3DAlt{});
		BenchmarkObjAlt(objAltArr, benchmarkCount);
	}
	conf.values.ys = m_yDataObjAlt.data();
	conf.values.color = ImColor(0, 0, 255);

	ImGui::Plot("ObjAltPlot", conf);

	// Combined
	ImGui::Text("Combined Graphs: ");
	const ImU32 colors[2] = { ImColor(0, 255, 0), ImColor(0, 0, 255) };

	const float* yData[] = { m_yDataObj.data(), m_yDataObjAlt.data() };
	ImGui::PlotConfig conf_Combined;
	conf_Combined.values.xs = m_Steps.data();
	conf_Combined.values.count = int(m_Steps.size());
	conf_Combined.values.ys_list = yData;
	conf_Combined.values.ys_count = 2;
	conf_Combined.values.colors = colors;
	conf_Combined.scale.min = 0.f;
	conf_Combined.scale.max = 100'000.f;
	conf_Combined.tooltip.show = true;
	conf_Combined.grid_x.show = false;
	conf_Combined.grid_y.show = true;
	conf_Combined.grid_y.size = 10'000.f;
	conf_Combined.tooltip.format = "x=%.2f, y=%.2f";
	conf_Combined.frame_size = ImVec2(200, 100);

	ImGui::Plot("CombinedPlot", conf_Combined);
}

void dae::ImGuiComponent::BenchmarkIntegers(std::vector<int> intVec, int benchmarks)
{
	int currentStep{};
	for (int stepSize{ 1 }; stepSize <= m_MaxStepSize; stepSize *= 2)
	{
		if (m_yDataIntegers.size() < m_Steps.size())
		{
			m_yDataIntegers.push_back(0);
		}
		std::vector<long long> elapsedTimes(benchmarks);

		// Fill array with durations
		for (size_t i{}; i < benchmarks; i++)
		{
			// Get start
			auto start = std::chrono::high_resolution_clock::now();
			// Do something
			for (int idx{}; idx < m_ArrSize; idx += stepSize)
			{
				intVec[idx] *= 2;
			}
			// Get end
			auto end = std::chrono::high_resolution_clock::now();

			// Calculate duration
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			elapsedTimes[i] = elapsedTime;
		}

		// Remove lowest
		auto min = std::min_element(elapsedTimes.begin(), elapsedTimes.end());
		elapsedTimes.erase(min);
		// Remove highest
		auto max = std::max_element(elapsedTimes.begin(), elapsedTimes.end());
		elapsedTimes.erase(max);
		// Get average
		auto avgTime = std::accumulate(elapsedTimes.begin(), elapsedTimes.end(), 0.0) / elapsedTimes.size();

		m_yDataIntegers[currentStep] = float(avgTime);
		++currentStep;
	}
}

void dae::ImGuiComponent::BenchmarkObj(std::vector<GameObject3D> objVec, int benchmarks)
{
	int currentStep{};
	for (int stepSize{ 1 }; stepSize <= m_MaxStepSize; stepSize *= 2)
	{
		if (m_yDataObj.size() < m_Steps.size())
		{
			m_yDataObj.push_back(0);
		}
		std::vector<long long> elapsedTimes(benchmarks);

		// Fill array with durations
		for (size_t i{}; i < benchmarks; i++)
		{
			// Get start
			auto start = std::chrono::high_resolution_clock::now();
			// Do something
			for (int idx{}; idx < m_ArrSize; idx += stepSize)
			{
				objVec[idx].ID *= 2;
			}
			// Get end
			auto end = std::chrono::high_resolution_clock::now();

			// Calculate duration
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			elapsedTimes[i] = elapsedTime;
		}

		// Remove lowest
		auto min = std::min_element(elapsedTimes.begin(), elapsedTimes.end());
		elapsedTimes.erase(min);
		// Remove highest
		auto max = std::max_element(elapsedTimes.begin(), elapsedTimes.end());
		elapsedTimes.erase(max);
		// Get average
		auto avgTime = std::accumulate(elapsedTimes.begin(), elapsedTimes.end(), 0.0) / elapsedTimes.size();

		m_yDataObj[currentStep] = float(avgTime);
		++currentStep;
	}
}

void dae::ImGuiComponent::BenchmarkObjAlt(std::vector<GameObject3DAlt> objAltVec, int benchmarks)
{
	int currentStep{};
	for (int stepSize{ 1 }; stepSize <= m_MaxStepSize; stepSize *= 2)
	{
		if (m_yDataObjAlt.size() < m_Steps.size())
		{
			m_yDataObjAlt.push_back(0);
		}
		std::vector<long long> elapsedTimes(benchmarks);

		// Fill array with durations
		for (size_t i{}; i < benchmarks; i++)
		{
			// Get start
			auto start = std::chrono::high_resolution_clock::now();
			// Do something
			for (int idx{}; idx < m_ArrSize; idx += stepSize)
			{
				objAltVec[idx].ID *= 2;
			}
			// Get end
			auto end = std::chrono::high_resolution_clock::now();

			// Calculate duration
			auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
			elapsedTimes[i] = elapsedTime;
		}

		// Remove lowest
		auto min = std::min_element(elapsedTimes.begin(), elapsedTimes.end());
		elapsedTimes.erase(min);
		// Remove highest
		auto max = std::max_element(elapsedTimes.begin(), elapsedTimes.end());
		elapsedTimes.erase(max);
		// Get average
		auto avgTime = std::accumulate(elapsedTimes.begin(), elapsedTimes.end(), 0.0) / elapsedTimes.size();

		m_yDataObjAlt[currentStep] = float(avgTime);
		++currentStep;
	}
}
