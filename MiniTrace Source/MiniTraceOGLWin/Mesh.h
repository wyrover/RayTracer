#pragma once
#include <Windows.h>
#include "Primitive.h"
#include "Box.h"

class Mesh : public Primitive
{
private:
	Triangle *m_triangles;
	unsigned m_triangleCount;
	
	Box *m_boundary;

	void LoadMeshFromFile(LPCWSTR filename);

public:
	Mesh(LPCWSTR filename, Vector3 pos);
	Mesh(LPCWSTR filename, Vector3 pos, Vector3 boundaryOffset, double width, double height, double depth);
	~Mesh();

	void SetPosition(Vector3 pos);
	RayHitResult IntersectByRay(Ray& ray);
};

