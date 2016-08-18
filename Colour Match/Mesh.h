/*	FIT2049 - Example Code
*	Mesh.h
*	Created by Elliott Wilson & Mike Yeates - 2016 - Monash University
*	This class represents an indexed Mesh of 3D Vertices.
*	It is capable of loading triangulated OBJ files as well as creating simple primitives
*	It also manages a collection of loaded meshes so we can fetch them statically from any object
*/

#ifndef MESH_H
#define MESH_H

#include "Direct3D.h"
#include "DirectXTK/SimpleMath.h"
#include "Camera.h"
#include "Texture.h"

class Mesh
{
private:
	struct Vertex			//This struct represents a single vertex of our mesh
	{
		Vector3 position;	//It is made up of a position
		Color colour;		//A colour
		Vector3 normal;		//A normal, which defines which way the face is "facing", these are important for lighting calculations
		Vector2 texCoord;	//and a texture coordinate, these are used to determine which part of a texture belongs to this vertex
	};

	Mesh::Mesh(Direct3D* direct3D, const char* identifier, int numVertices, int numIndices, Vertex* vertexData, unsigned long* indexData, D3D11_PRIMITIVE_TOPOLOGY topology);

	// Not using filename to identify a mesh so we can easily rename and not have to change lots in our code
	// Note these must be unique as we use them as keys in our map
	const char* m_identifier;

	int m_vertexCount;				//We store a count of all of the vertices
	int m_indexCount;				//As well as a count of all of the indices
	ID3D11Buffer* m_vertexBuffer;	//We use Direct3D Buffers to store the verts...
	ID3D11Buffer* m_indexBuffer;	//... and the indices in graphics memory

	D3D11_PRIMITIVE_TOPOLOGY m_topology; // How will Direct3D interpret the indices for this mesh (basically list or strip)

	// Each mesh keeps track of how many things are using it in our code
	// Each time something is done with the mesh, it should call ReleaseMesh to decrement this reference counter
	// When the reference counter hits 0 (nothing is using it) the mesh is deleted
	int m_referenceCount;
	void AddRef() { m_referenceCount++; }
	void RemoveRef() { m_referenceCount--; }
	int GetRefCount() { return m_referenceCount; }

	// Static manager helpers
	// We keep track of every mesh created so we can fetch meshes anywhere in our game
	typedef std::map<std::string, Mesh*> MeshMap;
	static MeshMap meshMap;

	bool InitialiseBuffers(Direct3D* direct3D, Vertex* vertexData, unsigned long* indexData);	//This method takes vertex and index data and creates the Direct3D buffers
	
public:
	~Mesh();

	void Render(Direct3D* direct3D, Matrix world, Camera* cam, Shader* shader, Texture* texture);		//Renders the mesh data according to the mesh shader and the world matrix supplied

	//Accessors
	int GetVertexCount() { return m_vertexCount; }
	int GetIndexCount() { return m_indexCount; }
	const char* GetIdentifier() { return m_identifier; }

	// Static manager helpers
	static bool LoadFromFile(LPCWSTR filename, const char* identifier, Direct3D* direct3D);

	static Mesh* CreateTriangle(Direct3D* direct3D, const char* identifier);
	static Mesh* CreateSquare2D(Direct3D* direct3D, const char* identifier);
	static Mesh* CreateAbstractArt(Direct3D* direct3D, const char* identifier);

	static Mesh* GetMesh(const char* identifier);
	static void ReleaseMesh(Mesh* mesh);
	
};

#endif