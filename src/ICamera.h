// Camera Abstract Interface class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "types.h"

struct Ray;
// ================================ Camera Interface Class ================================
/**
	* @brief Basic camera abstract interface class
	* @ingroup moduleCamera
	* @author Sergey G. Kosov, sergey.kosov@project-10.de
	*/
class ICamera
{
public:
	/**
		* @brief Constructor
		* @param resolution The resolution of the camera in pixels
		*/
	ICamera(Size resolution)
		: m_resolution(resolution)
		, m_aspectRatio(static_cast<float>(resolution.width) / resolution.height)
	{}
	ICamera(const ICamera&) = delete;
	virtual ~ICamera(void) = default;
	const ICamera& operator=(const ICamera&) = delete;

	/**
		* @brief Initializes a ray \b ray passing trough a screen pixel with coordinates \b x anf \b y
		* @details This function initializes the ray pointing from the camera origin to the pixel
		* on the camera screen defyned by the coodrinates \b (x,y). The pixel coordinates need to lie
		* in the ranges of camera resolution.
		* @param[out] ray Reference to the @ref Ray structure to be filled
		* @param[in] x The x-coordinate of the pixel lying on the camera screen
		* @param[in] y The y-coordinate of the pixel lying on the camera screen
		*/
	virtual void InitRay(Ray& ray, int x, int y) = 0;

	/**
		* @brief Retuns the camera resolution in pixels
		* @return The camera resolution in pixels
		*/
	Size getResolution(void) const { return m_resolution; }
	/**
		* @brief Returns the camera aspect ratio
		* @return The camera aspect ratio
		*/
	float getAspectRatio(void) const { return m_aspectRatio; }


private:
	const Size	m_resolution;	///< Camera image resolution in pixels
	const float	m_aspectRatio;	///< Camera image aspect ratio
};

using ptr_camera_t = std::shared_ptr<ICamera>;

