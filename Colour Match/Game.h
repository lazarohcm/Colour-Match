/*	FIT2049 - Example Code
*	Game.h
*	Created by Elliott Wilson & Mike Yeates - 2016 - Monash University
*	This class is the heart of our game and is also where our game logic will reside
*	It contains the overall Update and Render method for the whole game
*	You should eventually split some game logic into other objects which Game will manage
*	Watch the size of this class - it can grow out of control very fast!
*/

#ifndef GAME_H
#define GAME_H

#include "Direct3D.h"
#include "InputController.h"
#include "Mesh.h"
#include "Camera.h"
#include "Button.h"
#include "TexturedShader.h"
#include "DirectXTK/SpriteBatch.h"
#include "DirectXTK/SpriteFont.h"

class Game
{
private:
	Camera* m_currentCam;		
	Direct3D* m_renderer;
	InputController* m_input;

	// These are to draw sprites and text over our game. We'll talk about this next week.
	SpriteBatch* m_spriteBatch;
	SpriteFont* m_arialFont;
	
	Shader* m_unlitShader;
	Shader* m_texturedShader;

	Texture* m_blueCubeTexture;

	Mesh* m_cube;
	Matrix m_cubeMatrix;

	float moveSpeed;
	Vector3 cubePos;

	// Splitting initialisation up into several steps
	bool InitShaders();
	bool LoadTextures();
	bool LoadMeshes();
	void LoadFonts();
	void InitUI();

	void DrawUI();

public:
	Game();	
	~Game();

	bool Initialise(Direct3D* renderer, InputController* input); //The initialise method loads all of the content for the game (meshes, textures, etc.)

	void Update(float timestep);	//The overall Update method for the game. All gameplay logic will be done somewhere within this method
	void Render();					//The overall Render method for the game. Here all of the meshes that need to be drawn will be drawn

	void Shutdown(); //Cleanup everything we initialised
};

#endif