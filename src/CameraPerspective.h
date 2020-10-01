// Perspective Camera class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ICamera.h"
#include "ray.h"

// ================================ Perspective Camera Class ================================
/**
 * @brief Perspective Camera class
 * @ingroup moduleCamera
 * @author Sergey G. Kosov, sergey.kosov@project-10.de
 */
class CCameraPerspective : public ICamera
{
public:
	/**
	 * @brief Constructor
	 * @param resolution The image resolution in pixels
	 * @param pos Camera origin (center of projection)
	 * @param dir Normalized camera viewing direction
	 * @param up Normalized camera up-vector
	 * @param angle (Vertical) full opening angle of the viewing frustum in degrees
	 */
	CCameraPerspective(Size resolution, const Vec3f& pos, const Vec3f& dir, const Vec3f& up, float angle)
		: ICamera(resolution)
		, m_pos(pos)
		, m_dir(dir)
		, m_up(up)
	{
		// --- PUT YOUR CODE HERE ---
		m_zAxis = normalize(dir);
		m_xAxis = normalize(m_zAxis.cross(up));
		m_yAxis = normalize(m_zAxis.cross(m_xAxis));
		m_focus = 1 / tan((Pif * angle) / 180);
	}
	virtual ~CCameraPerspective(void) = default;

	virtual void InitRay(Ray& ray, int x, int y) override
	{
		// --- PUT YOUR CODE HERE ---
		/*for (int y = 0; y < getResolution().height; y++)
			for (int x = 0; x < getResolution().width; x++)
			{
				//Normalized device coordinates 0,1
				//+0.5 to center of pixel
				float ndcx= (x + 0.5) / getResolution().width;
				float ndcy= (y + 0.5) / getResolution().height;
				//Screen space coordinates -1, 1
				float sscx= 2 * ndcx-1 ;  
				float sscy= 2 * ndcy-1 ;
				//Generate direction
				float d = sscx*m_xAxis + sscy*m_yAxis + m_focus;
				//normalise
				d = d / |d|;
				//ray tracing and color assignment
				color= trace_ray(m_pos,d);
				img(y, x) = color;
			}*/
		//~~~~~~~~~~~~~~~~~
		Size res= getResolution();

		// Normalized device coordinates in [0, 1]
		float ndcx= static_cast<float>(x) / getResolution().width;
		float ndcy= static_cast<float>(y) / getResolution().height;

		// Screen-space coordinates in [-1, 1]
		float sscx= 2 * ndcx - 1;
		//float sscy = 2 * ndcy - 1;//can be better
		float sscy= 1- (2*ndcy) ;//new implementation

		// Define Camera coordinate system
		Vec3f zAxis= m_dir;
		Vec3f xAxis= normalize(zAxis.cross(m_up));
		Vec3f yAxis= normalize(zAxis.cross(xAxis));

		ray.org= m_pos;
		ray.dir= normalize(getAspectRatio() * sscx * xAxis + sscy * yAxis + m_focus * zAxis);
		ray.t= std::numeric_limits<float>::infinity();//hit distance
	}


private:
	// input values
	Vec3f m_pos;			///< Camera origin (center of projection)
	Vec3f m_dir;			///< Camera viewing direction
	Vec3f m_up;				///< Camera up-vector
	float m_focus;			///< The focal length

	// preprocessed values
	Vec3f m_xAxis;			///< Camera x-axis in WCS
	Vec3f m_yAxis;			///< Camera y-axis in WCS
	Vec3f m_zAxis;			///< Camera z-axis in WCS
};

