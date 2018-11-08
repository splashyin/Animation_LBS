#pragma once
#include <GL/glew.h>
#include <glm\glm.hpp>
#include "Shader.h"
#include <vector>

using std::vector;

class Skeleton {
public:
	vector<glm::vec3> skeleton;

	Skeleton(vector<glm::vec3> Skeleton) {
		this->skeleton = Skeleton;

		setupSkeleton();
	}

	//render the Skeleton
	void Draw(Shader shader)
	{
		shader.use();

		glBindVertexArray(skeletonVAO);
		glDrawArrays(GL_LINES, 0, skeleton.size());
		glBindVertexArray(0);
	}

private:
	unsigned int skeletonVAO, VBO;
	void setupSkeleton()
	{
		glGenVertexArrays(1, &skeletonVAO);
		glBindVertexArray(skeletonVAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, skeleton.size() * sizeof(glm::vec3), &skeleton[0], GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
	}
};