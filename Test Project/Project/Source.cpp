#include <iostream>
#include "OBJFileReader.h"

int main()
{
	Triangle *mesh;
	int num = importOBJMesh(L"SimpleObject.obj", &mesh);

	for (int v = 0; v < num; v++)
	{
		for (int i = 0; i < 3; i++)
		{
			
		}

		mesh++;
	}

	return 0;
}