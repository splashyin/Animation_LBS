#pragma once
#include <GL/glew.h>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtc\type_ptr.hpp>



class dual_quat {
public:
	glm::quat ordinary, dual;	//the two quaternion ordinary and its dual

	//a simple function that create a dual quaternion from the given 
	//orientation (q0) and translation (t)
	void QuatTrans2UDQ(const glm::quat& q0, const glm::vec3& t) {
		ordinary = q0;
		dual.w = -0.5f * (t.x * q0.x + t.y * q0.y + t.z * q0.z);
		dual.x = 0.5f * (t.x * q0.w + t.y * q0.z - t.z * q0.y);
		dual.y = 0.5f * (-t.x * q0.z + t.y * q0.w + t.z * q0.x);
		dual.z = 0.5f * (t.x * q0.y - t.y * q0.x + t.z * q0.w);
	}

	//converts the dual quaternion to a matrix
	void UDQToMatrix(glm::mat4& m) {
		float len2 = glm::dot(ordinary, ordinary);
		float w = ordinary.w, x = ordinary.x, y = ordinary.y, z = ordinary.z;
		float t0 = dual.w, t1 = dual.x, t2 = dual.y, t3 = dual.z;
		m[0][0] = w * w + x * x - y * y - z * z;
		m[1][0] = 2 * x * y - 2 * w * z;
		m[2][0] = 2 * x * z + 2 * w * y;
		m[0][1] = 2 * x * y + 2 * w * z;
		m[1][1] = w * w + y * y - x * x - z * z;
		m[2][1] = 2 * y * z - 2 * w * x;
		m[0][2] = 2 * x * z - 2 * w * y;
		m[1][2] = 2 * y * z + 2 * w * x;
		m[2][2] = w * w + z * z - x * x - y * y;

		m[3][0] = -2 * t0 * x + 2 * w * t1 - 2 * t2 * z + 2 * y * t3;
		m[3][1] = -2 * t0 * y + 2 * t1 * z - 2 * x * t3 + 2 * w * t2;
		m[3][2] = -2 * t0 * z + 2 * x * t2 + 2 * w * t3 - 2 * t1 * y;

		m[0][3] = 0;
		m[1][3] = 0;
		m[2][3] = 0;
		m[3][3] = len2;
		m /= len2;
	}

};
