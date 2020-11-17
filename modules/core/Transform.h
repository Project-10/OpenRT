// Affine transformation class
// Written by Dr. Sergey G. Kosov in 2019 for Project X
#pragma once

#include "types.h"

namespace rt {
	// ================================ Affine Transformation Class ================================
	/**
	* @brief Common Affine Transformation class
	* @details This class provides basic functionality for generating affine transformation matrix in homogeneous coordinates. In order to simplify the 3D transformation code, this class provides 
	* <a href="https://en.wikipedia.org/wiki/Fluent_interface" target="_blank">fluent interface</a>. Please see the example code below for more details.
	* @code
	* CTransform transform;
	* Mat t = transform.scale(2).rotate(Vec3f(0, 1, 0), 30).get();	// transformation matrix for scaling and rotating an object
	* solidCone.transform(t);										// apply transformation to to a solid
	* @endcode
	* Thus, every subsequent function adds new atomic transformation to the transofmation matrix of the class.
	* @author Dr. Sergey G. Kosov, sergey.kosov@project-10.de
	*/
	class CTransform {
	public:
		DllExport CTransform(void) = default;
		DllExport CTransform(const CTransform&) = delete;
		DllExport ~CTransform(void) = default;
		DllExport const CTransform& operator=(const CTransform&) = delete;
		
		/**
		* @brief Returns the transformation matrix
		* @returns The transformation matrix (size: 4 x 4; type: CV_32FC1)
		*/
		DllExport Mat 			get(void) const { return m_t; }
		
		/**
		* @brief Adds uniform scaling by factor \b s
		* @param s The scaling factor
		* @returns Common Transformation Class with modified transformation matrix
		*/
		DllExport CTransform 	scale(float s) const { return scale(Vec3f::all(s)); }
		/**
		* @brief Adds scaling by factors \b sx, \b sy and \b sz 
		* @param sx The scaling factor along x-axis
		* @param sy The scaling factor along y-axis
		* @param sz The scaling factor along z-axis
		* @returns Common Transformation Class with modified transformation matrix
		*/
		DllExport CTransform	scale(float sx, float sy, float sz) const { return scale(Vec3f(sx, sy, sz)); }
		/**
		* @brief Adds scaling by a vector \b S = (sx, sy, sz)
		* @param S The scaling vector
		* @returns Common Transformation Class with modified transformation matrix
		*/
		DllExport CTransform	scale(const Vec3f& S) const;
		
		/**
		* @brief Adds reflection relative to the X axis
		* @details This operation is analogous to CTransform::scale(-1, 1, 1);
		* @returns Common Transformation Class with modified transformation matrix
		*/
		DllExport CTransform	reflectX(void) const { return scale(Vec3f(-1, 1, 1)); }
		/**
		* @brief Adds reflection relative to the Y axis
		* @details This operation is analogous to CTransform::scale(1, -1, 1);
		* @returns Common Transformation Class with modified transformation matrix
		*/
		DllExport CTransform	reflectY(void) const { return scale(Vec3f(1, -1, 1)); }
		/**
		* @brief Adds reflection relative to the Z axis
		* @details This operation is analogous to CTransform::scale(1, 1, -1);
		* @returns Common Transformation Class with modified transformation matrix
		*/
		DllExport CTransform	reflectZ(void) const { return scale(Vec3f(1, 1, -1)); }
		/**
		* @brief Adds reflection relative to the origin of coordinates
		* @details This operation is analogous to CTransform::scale(-1, -1, -1);
		* @returns Common Transformation Class with modified transformation matrix
		*/
		DllExport CTransform	reflectO(void) const { return scale(Vec3f(-1, -1, -1)); }

		/**
		* @brief Adds translation along the coordinates axises by \b tx, \b ty and \b tz
		* @param tx Translation value along the X axis
		* @param ty Translation value along the Y axis
		* @param tz Translation value along the Z axis
		* @returns Common Transformation Class with modified transformation matrix
		*/
		DllExport CTransform	translate(float tx, float ty, float tz) const { return translate(Vec3f(tx, ty, tz)); }
		/**
		* @brief Adds translation along the coordinates axises by vector \b T = (tx, ty, tz)
		* @param T The translation vector
		* @returns Common Transformation Class with modified transformation matrix
		*/
		DllExport CTransform	translate(const Vec3f& T) const;

		/**
		* @brief Adds rotation around axis \b v by angle \b theta
		* @param k The rotation axis
		* @param theta The angle of rotation in \a degrees
		* @returns Common Transformation Class with modified transformation matrix
		*/
		DllExport CTransform	rotate(const Vec3f& k, float theta) const;
			
		/**
		* @brief Applies affine transormation matrix \b t to a point \b p
		* @details This method uses homogeneous coordinates
		* @param p The point in 3D space
		* @param t The transformation matrix (size: 4 x 4)
		* @returns The transformed point
		* @todo Check OpneCV affine3d class
		*/
		DllExport static Vec3f	point(const Vec3f& p, const Mat& t);
		/**
		* @brief Applies affine transormation matrix \b t to a vector \b v
		* @details This method uses homogeneous coordinates* 
		* @param v The vector in 3D space
		* @param t The transformation matrix (size: 4 x 4)
		* @returns The transformed vector
		* @todo Check OpneCV affine3d class
		*/
		DllExport static Vec3f	vector(const Vec3f& v, const Mat& t);
	
	
	private:
		/**
		* @brief Constructor
		* @param t Transformation matrix (size: 4 x 4, type: CV_32FC1)
		*/
		CTransform(const Mat& t) : m_t(t) {}
	
	
	private:
		Mat m_t = Mat::eye(4, 4, CV_32FC1);		///< The transformation matrix (size: 4 x 4)
	};
}
