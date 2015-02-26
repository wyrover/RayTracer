#include "Mesh.h"
#include "OBJFileReader.h"

Mesh::Mesh(LPCWSTR filename, Vector3 pos, Vector3 boundaryOffset, double width, double height, double depth)
{
	m_primtype = PRIMTYPE_Mesh;
	m_triangleCount = 0;

	LoadMeshFromFile(filename);
	SetPosition(pos);
	m_boundary = nullptr;
	m_boundary = new Box(pos + boundaryOffset, width, height, depth);
}

Mesh::~Mesh()
{
}

void Mesh::LoadMeshFromFile(LPCWSTR filename)
{
	m_triangleCount = importOBJMesh(filename, &m_triangles);
}

void Mesh::SetPosition(Vector3 pos)
{
	for (int i = 0; i < m_triangleCount; i++)
	{
		m_triangles[i].SetPosition(pos);
	}
}

RayHitResult Mesh::IntersectByRay(Ray &ray)
{
	RayHitResult result = Ray::s_defaultHitResult;
	RayHitResult boundaryCheck = Ray::s_defaultHitResult;

	if (m_boundary != nullptr)
		boundaryCheck = m_boundary->IntersectByRay(ray);

	if (boundaryCheck.t < FARFAR_AWAY || m_boundary == nullptr)
	{
		for (int i = 0; i < m_triangleCount; i++)
		{
			Primitive* prim = static_cast<Primitive*>(&m_triangles[i]);

			RayHitResult tempresult = prim->IntersectByRay(ray);

			if (tempresult.t < result.t)
			{
				tempresult.data = this;
				result = tempresult;
			}
		}
	}

	return result;
}