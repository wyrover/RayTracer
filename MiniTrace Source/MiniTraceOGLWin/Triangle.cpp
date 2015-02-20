/*---------------------------------------------------------------------
*
* Copyright © 2015  Minsi Chen
* E-mail: m.chen@derby.ac.uk
* 
* The source is written for the Graphics I and II modules. You are free
* to use and extend the functionality. The code provided here is functional
* however the author does not guarantee its performance.
---------------------------------------------------------------------*/
#include "Triangle.h"

Triangle::Triangle()
{
	m_vertices[0] = Vector3(-1.0, 0.0, -5.0);
	m_vertices[1] = Vector3(0.0, 1.0, -5.0);
	m_vertices[2] = Vector3(1.0, 0.0, -5.0);
	m_normal = Vector3(0.0, 0.0, 1.0);
	m_primtype = PRIMTYPE_Triangle;
}

Triangle::Triangle(Vector3 pos1, Vector3 pos2, Vector3 pos3)
{
	SetTriangle(pos1, pos2, pos3);

	m_primtype = PRIMTYPE_Triangle;
}


Triangle::~Triangle()
{
}

void Triangle::SetTriangle(Vector3 v0, Vector3 v1, Vector3 v2)
{
	m_vertices[0] = v0;
	m_vertices[1] = v1;
	m_vertices[2] = v2;

	//Calculate Normal
	Vector3 NormalA = m_vertices[1] - m_vertices[0];
	Vector3 NormalB = m_vertices[2] - m_vertices[0];
	Vector3 Norm = NormalA.CrossProduct(NormalB);
	Norm.Normalise();
	m_normal = Norm;
}


RayHitResult Triangle::IntersectByRay(Ray& ray)
{
	RayHitResult result = Ray::s_defaultHitResult;
	double t = FARFAR_AWAY;
	Vector3 intersection_point;
	
	// TODO: Calculate the intersection between in the input ray and this triangle
	// If you have implemented ray-plane intersection, you have done half the work for ray-triangle intersection.
	// The remaining test is to check if the intersection point is inside the triangle
	//
	// Similar to the plane case, you should check if the ray is parallel to the triangle
	// and check if the ray intersects the triangle from the front or the back

	if (m_normal.DotProduct(ray.GetRay()) < 0)
	{
		double temp = -((ray.GetRayStart().DotProduct(m_normal) + -(m_vertices[0].DotProduct(m_normal))) / (ray.GetRay().DotProduct(m_normal)));

		//Calculate the exact location of the intersection using the result of t
		intersection_point = ray.GetRayStart() + ray.GetRay()*temp;

		// http://www.blackpawn.com/texts/pointinpoly/

		Vector3 v0 = m_vertices[2] - m_vertices[0];
		Vector3 v1 = m_vertices[1] - m_vertices[0];
		Vector3 v2 = intersection_point - m_vertices[0];

		double dot00 = v0.DotProduct(v0);
		double dot01 = v0.DotProduct(v1);
		double dot02 = v0.DotProduct(v2);
		double dot11 = v1.DotProduct(v1);
		double dot12 = v1.DotProduct(v2);

		double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);

		float u = (dot11 * dot02 - dot01 * dot12) * invDenom;
		float v = (dot00 * dot12 - dot01 * dot02) * invDenom;

		if ((u >= 0) && (v >= 0) && (u + v < 1))
			t = temp;
	}

	if (t > 0 && t < FARFAR_AWAY) 
	{	//ray intersection
		result.t = t;
		result.normal = this->m_normal;
		result.point = intersection_point;
		result.data = this;
		return result;
	}
	
	return result;
}