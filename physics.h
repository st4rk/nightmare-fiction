#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <glm/glm.hpp>

typedef struct Point {
	int X;
	int Y;
} Point;


namespace physics {

	namespace interpolation {
		float lerpAngle(float start, float end, float a);
	}

	namespace collision {
		bool rectangle(const glm::vec3& p1,
					   const glm::vec3& p2,
					   const glm::vec3& p3);

		
		bool ellipse(const glm::vec3& p1,
					 const glm::vec3& p2,
					 const glm::vec3& p3);

		bool triangle(const glm::vec3& pI,
					  const glm::vec3& p1,
					  const glm::vec3& p2,
					  const glm::vec3& p3);


		bool sameSide(const glm::vec3& pI,
					  const glm::vec3& p1,
					  const glm::vec3& p2,
					  const glm::vec3& p3);

	}
}


#endif