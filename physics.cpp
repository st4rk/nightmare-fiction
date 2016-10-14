#include "physics.h"



namespace physics {
	
	namespace collision {
		bool rectangle(const float& x,  const float& y,  const float& z,
					   const float& x1, const float& y1, const float& z1,
					   const float& x2, const float& y2, const float& z2) {

			if ((x1 <= x) && (x <= x1+x2)) {
				if ((z1 <= z) && (z <= z1+z2)) {
					return true;
				}
			}

			return false;
		}

		bool ellipse(const float& x,  const float& y,  const float& z,
					 const float& x1, const float& y1, const float& z1,
					 const float& x2, const float& y2, const float& z2) {

			double rayX = (x2 - x1) / 2;
			double rayZ = (z2 - z1) / 2;
			double cX = x1 + rayX;
			double cZ = z1 + rayZ;

			double k = pow ((x - cX) / rayX, 2) + pow ((z - cZ) / rayZ, 2);

			if (k <= 1)
				return true;
		
			return false;
		}

		bool sameSide(const glm::vec3& pI,
					  const glm::vec3& p1,
					  const glm::vec3& p2,
					  const glm::vec3& p3) {
			
			glm::vec3 vec_1 = glm::cross(p3-p2, pI-p2);
			glm::vec3 vec_2 = glm::cross(p3-p2, p1-p2);

			if (glm::dot(vec_1, vec_2) >= 0)
				return true;
			else
				return false;

		}



		bool triangle(const glm::vec3& pI,
					  const glm::vec3& p1,
					  const glm::vec3& p2,
					  const glm::vec3& p3) {

			if (sameSide(pI, p1, p2, p3) && sameSide(pI,p2,p1,p3) &&
				sameSide(pI, p3, p1, p2))
				return true;
			else
				return false;

		}

		
	}
}