#include "physics.h"



namespace physics {
	namespace interpolation {
	    float lerpAngle(float start, float end, float a) {
	    	/* get absolute value from the difference between angles */
	        float diff = std::abs(end - start);

	        	/* check if the difference is big than 180º */
		        if (diff > 180.0f) {
		        	/*
		        	 * if end is big than start, add one
		        	 * else, add one to end 
		        	 */

		            end > start ? start += 360.0f : end += 360.0f;
		        }

	        /* lerp */
	        float value = (start + ((end - start) * a));

	        /* check if the value is in the rage of 360 */
	        if (value >= 0.0f && value <= 360.0f)
	            return value;

	        /* otherwise, module of angle */
	        return (fmod(value, 360.0f));
	    }
	}
	namespace collision {
		bool rectangle(const glm::vec3& p1,
					   const glm::vec3& p2,
					   const glm::vec3& p3) {

			if ((p2.x <= p1.x) && (p1.x <= p2.x+p3.x)) {
				if ((p2.z <= p1.z) && (p1.z <= p2.z+p3.z)) {
					return true;
				}
			}

			return false;
		}

		bool rectangle(const glm::vec3& p1,
					   const glm::vec3& p2,
					   const glm::vec3& p3,
					   glm::vec3& norm) {

			if ((p2.x <= p1.x) && (p1.x <= p2.x+p3.x)) {
				if ((p2.z <= p1.z) && (p1.z <= p2.z+p3.z)) {
					return true;
				}
			}

			return false;
		}

		bool ellipse(const glm::vec3& p1,
					 const glm::vec3& p2,
					 const glm::vec3& p3)  {

			double rayX = (p3.x - p2.x) / 2;
			double rayZ = (p3.z - p2.z) / 2;
			double cX = p2.x + rayX;
			double cZ = p2.z + rayZ;

			double k = pow ((p1.x - cX) / rayX, 2) + pow ((p1.z - cZ) / rayZ, 2);

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

		bool rectangle2(const glm::vec3& p1,
			    const glm::vec3& p2,
			    const glm::vec3& p3,
			    const glm::vec3& p4,
			    glm::vec3& norm) {


			if ( (p1.x < (p3.x + p4.x)) &&
				 ((p1.x + p2.x) > p3.x) &&
				 (p1.z < (p3.z + p4.z)) &&
				 ((p2.z + p1.z) > p3.z)) {

				float hx = (p2.x + p4.x) * ((p1.x+p2.x)/2 - (p3.x+p4.x)/2);
				float wy = (p2.z + p4.z) * ((p1.z+p2.z)/2 - (p3.z+p4.z)/2);

				if (wy > hx) {
					if (wy > -hx) {
						std::cout << "left" << std::endl;
						norm = glm::vec3(0.0f, 0.0f, 1.0f);
					} else {
						std::cout << "top" << std::endl;
						norm = glm::vec3(-1.0f, 0.0f, 0.0f);
					}
				} else {
					if (wy > -hx) {
						std::cout << "right" << std::endl;
						norm = glm::vec3(1.0f, 0.0f, 0.0f);
					} else {
						std::cout << "bottom" << std::endl;
						norm = glm::vec3(0.0f, 0.0f, -1.0f);
					}
				}

				return true;
			}

			return false;
		}


		
	}
}