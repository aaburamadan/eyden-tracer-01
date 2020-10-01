// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "IPrim.h"
#include "ray.h"

// ================================ Sphere Primitive Class ================================
/**
 * @brief Sphere Geaometrical Primitive class
 * @ingroup modulePrimitive
 * @author Sergey G. Kosov, sergey.kosov@project-10.de
 */
class CPrimSphere : public IPrim
{
public:
	/**
	 * @brief Constructor
		 * @param origin Position of the center of the sphere
		 * @param radius Radius of the sphere
	 */
	CPrimSphere(Vec3f origin, float radius)
		: IPrim()
		, m_origin(origin)
		, m_radius(radius)
	{}
	virtual ~CPrimSphere(void) = default;

	virtual bool intersect(Ray &ray) const override
	{
		// --- PUT YOUR CODE HERE ---

		float a= ray.dir.dot(ray.dir);
		Vec3f diff = ray.org - m_origin;
		float b= 2* ray.dir.dot(diff);
		float c= diff.dot(diff) - m_radius * m_radius;

		//abc formula for finding root t_1,2
		float inRoot = b * b - 4 * a * c;//discriminant
		if (inRoot < 0)//negative means no real values (imaginary)
			return false;

		float root= sqrtf(inRoot);//root

		float dist= (-b - root)/(2*a);
		if(dist > ray.t)
			return false;

		if(dist < Epsilon)//smallest root
		{
			dist= (-b + root)/(2*a);
			if(dist < Epsilon || dist > ray.t)
				return false;
		}

		ray.t= dist;

		return true;

	}
	
	
private:
	Vec3f m_origin;	///< Position of the center of the sphere
	float m_radius;	///< Radius of the sphere
};

