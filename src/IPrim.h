// Geaometrical Primitives base abstract class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "types.h"

struct Ray;
// ================================ Primitive Interface Class ================================
/**
 * @brief Geometrical Primitives (Prims) base abstract class
 * @ingroup modulePrimitive
 * @author Sergey G. Kosov, sergey.kosov@project-10.de
 */
class IPrim
{
public:
	/**
	* @brief Constructor
	*/
	IPrim(void) = default;
	IPrim(const IPrim&) = delete;
	virtual ~IPrim(void) = default;
	const IPrim& operator=(const IPrim&) = delete;

	/**
	 * @brief Checks for intersection between ray \b ray and the primitive
	 * @details If a valid intersection has been found with the primitive, it sets Ray::t to the distance to this intersection
	 * point (if current t < ray.t) and sets Ray::hit to point to the current primitive
	 * @param[in,out] ray The ray (Ref. @ref Ray for details)
	 * @retval true If and only if a valid intersection has been found in the interval (epsilon; Ray::t)
	 * @retval false Otherwise
	 */
	virtual bool	intersect(Ray& ray) const = 0;
};
