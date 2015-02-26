#pragma once
#include <Windows.h>
#include "Primitive.h"
#include "Triangle.h"

class Mesh : public Primitive
{
private:
	Triangle* m_triangles;
	unsigned m_triangleCount;

	void LoadMeshFromFile(LPCWSTR filename);

public:
	Mesh(LPCWSTR filename, Vector3 &pos);
	~Mesh();

	void SetPosition(Vector3 &pos);
	RayHitResult IntersectByRay(Ray& ray);
};

