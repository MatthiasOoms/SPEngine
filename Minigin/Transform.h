#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <glm/glm.hpp>

namespace dae
{
	class GameObject;

	class Transform final
	{
	public:
		Transform(GameObject* pOwner);
		
		~Transform();
		Transform(const Transform& other) = delete;
		Transform(Transform&& other) = delete;
		Transform& operator=(const Transform& other) = delete;
		Transform& operator=(Transform&& other) = delete;

		const glm::vec3& GetLocalPosition() const { return m_LocalPosition; }
		const glm::vec3& GetWorldPosition() const { return m_WorldPosition; }
		void SetLocalPosition(float x, float y, float z);
		void SetWorldPosition(float x, float y, float z);

		void SetDimensions(glm::ivec2 dimensions);
		void SetWidth(int width);
		void SetHeight(int height);
		glm::ivec2 GetDimensions() const;
		int GetWidth() const;
		int GetHeight() const;

	private:
		glm::vec3 m_LocalPosition;
		glm::vec3 m_WorldPosition;
		glm::ivec2 m_Dimensions;
		GameObject* m_pOwner;
	};
}

#endif // ! TRANSFORM_H
