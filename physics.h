#ifndef _PHYSICS_H_
#define _PHYSICS_H_

#include <iostream>
#include <vector>
#include <cmath>
#include <glm/glm.hpp>

namespace physics {

	namespace collision {
		bool rectangle(const float& x,  const float& y,  const float& z,
					   const float& x1, const float& y1, const float& z1,
					   const float& x2, const float& y2, const float& z2);

		
		bool ellipse(const float& x,  const float& y,  const float& z,
					 const float& x1, const float& y1, const float& z1,
					 const float& x2, const float& y2, const float& z2);

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