#ifndef COMMAND_H
#define COMMAND_H
#include <glm/glm.hpp>
#include <string>

namespace dae
{
	class GameObject;

	class Command
	{
	public:
		explicit Command();

		virtual ~Command();
		Command(const Command& other) = delete;
		Command(Command&& other) = delete;
		Command& operator=(const Command& other) = delete;
		Command& operator=(Command&& other) = delete;

		virtual void Execute(float) = 0;
	};
}
#endif // ! COMMAND_H
