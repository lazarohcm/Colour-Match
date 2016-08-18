/*
	This class contains the bases to create a Colour Match Object, such as grid cells and the selection arrow
*/

#ifndef GRIDCELL_H
#define GRIDCELL_H

#include "Mesh.h"
#include "Direct3D.h"

class CMObject {
private:
	const char* meshPath;
	const char* texturePath;
	Mesh mesh;
	Matrix matrix;
	Vector3 position;
	/*
		Shader?
		Input?
		moveSpeed?
	*/

public:
	CMObject();
	const char* GetMeshPath() { return meshPath; };
	const char* GetTexturePath() { return texturePath; };
	//The meshs can be loaded and then finded in the Mesh map by name, as well as the textures
	Mesh getMesh() { return mesh;  }
	Matrix getMatrix() { return matrix; };
	void setMatrix(Matrix cubeMatrix);
	Vector3 getPosition() { return position; };
	void setPosition(Vector3 position);
	bool LoadTexture();
	bool LoadMesh();

	/*
		Add an:
		Update(float timestep);
		The matrix can be created inside the render function
		Render( Direct3D* renderer, Camera* cam);
	*/
};

#endif
