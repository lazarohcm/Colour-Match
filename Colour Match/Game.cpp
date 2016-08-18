/*	FIT2049 - Example Code
*	Game.cpp
*	Created by Elliott Wilson & Mike Yeates - 2016 - Monash University
*/

#include "Game.h"
#include "DirectXTK/CommonStates.h"

Game::Game()
{
	m_renderer = NULL;
	m_currentCam = NULL;
	m_input = NULL;
	m_unlitShader = NULL;
	m_texturedShader = NULL;
	m_cube = NULL;
	m_spriteBatch = NULL;
	m_arialFont = NULL;

	m_cubeMatrix = Matrix::Identity;

}

Game::~Game() {}

bool Game::Initialise(Direct3D* renderer, InputController* input)
{
	m_renderer = renderer;	
	m_input = input;

	if (!InitShaders())
		return false;

	if (!LoadTextures())
		return false;

	if (!LoadMeshes())
		return false;

	moveSpeed = 5.0f;
	cubePos = Vector3::Zero;

	LoadFonts();
	InitUI();

	m_currentCam = new Camera();

	return true;
}

bool Game::InitShaders()
{
	m_unlitShader = new Shader();
	if (!m_unlitShader->Initialise(m_renderer->GetDevice(), L"Assets/Shaders/VertexShader.vs", L"Assets/Shaders/VertexColourPixelShader.ps"))
	{
		return false;
	}

	m_texturedShader = new TexturedShader();
	if (!m_texturedShader->Initialise(m_renderer->GetDevice(), L"Assets/Shaders/VertexShader.vs", L"Assets/Shaders/TexturedPixelShader.ps"))
	{
		return false;
	}

	return true;
}

bool Game::LoadTextures()
{
	if (!Texture::LoadFromFile(L"Assets/Textures/Cube-Blue.png", "CubeBlue", m_renderer))
	{
		return false;
	}

	if (!Texture::LoadFromFile(L"Assets/Textures/Button.png", "ButtonWhite", m_renderer))
	{
		return false;
	}

	m_blueCubeTexture = Texture::GetTexture("CubeBlue");

	return true;
}

bool Game::LoadMeshes()
{
	if (!Mesh::LoadFromFile(L"Assets/Meshes/cube.obj", "GridCell", m_renderer))
	{
		return false;
	}

	//m_cube = Mesh::CreateTriangle(m_renderer, "Triangle");

	//m_cube = Mesh::CreateSquare2D(m_renderer, "Cube");

	m_cube = Mesh::CreateAbstractArt(m_renderer, "Abstract");

	return true;

}

void Game::LoadFonts()
{
	// There's a few different size fonts in there, you know
	m_arialFont = new SpriteFont(m_renderer->GetDevice(), L"Assets/Fonts/Arial-12pt.spritefont");
}

void Game::InitUI()
{
	m_spriteBatch = new SpriteBatch(m_renderer->GetDeviceContext());
}

void Game::Update(float timestep)
{
	m_input->BeginUpdate();
	
	m_currentCam->Update(timestep);

	if (m_input->GetKeyHold(VK_RIGHT)) {
		cubePos.x += moveSpeed * timestep;
	}
	else if (m_input->GetKeyHold(VK_LEFT)) {
		cubePos.x -= moveSpeed * timestep;
	}
	else if (m_input->GetKeyHold(VK_UP)) {
		cubePos.y += moveSpeed * timestep;
	}
	else if (m_input->GetKeyHold(VK_DOWN)) {
		cubePos.y -= moveSpeed * timestep;
	}
	else if (m_input->GetKeyHold(VK_RIGHT) && m_input->GetKeyHold(VK_UP)) {
		cubePos.x += moveSpeed / 2 * timestep;
		cubePos.y += moveSpeed / 2 * timestep;
	}
	m_cubeMatrix = Matrix::CreateTranslation(cubePos);

	m_input->EndUpdate();
}

void Game::Render()
{
	m_renderer->BeginScene(0.2f, 0.2f, 0.2f, 1.0f);

	// Render a mesh, using a matrix, taking into account the camera position / projection settings, using a shader, and optionally using a texture
	m_cube->Render(m_renderer, m_cubeMatrix, m_currentCam, m_unlitShader, NULL);

	// Here's an example of how to use our textured shader
	//m_cube->Render(m_renderer, m_cubeMatrix, m_currentCam, m_texturedShader, m_blueCubeTexture);

	DrawUI();

	m_renderer->EndScene();		

}

void Game::DrawUI()
{
	// Sprites and text (and buttons) will be explained in week 4

	// Sprites don't use a shader 
	m_renderer->SetCurrentShader(NULL);

	// Render Buttons and Fonts
	CommonStates states(m_renderer->GetDevice());
	m_spriteBatch->Begin(SpriteSortMode_Deferred, states.NonPremultiplied());

	// Do UI drawing in here

	m_spriteBatch->End();
}

void Game::Shutdown()
{
	if (m_currentCam)
	{
		delete m_currentCam;
		m_currentCam = NULL;
	}

	if (m_unlitShader)
	{
		m_unlitShader->Release();
		delete m_unlitShader;
		m_unlitShader = NULL;
	}

	if (m_texturedShader)
	{
		m_texturedShader->Release();
		delete m_texturedShader;
		m_texturedShader = NULL;
	}

	if (m_cube)
	{
		// Decrements reference count and deletes mesh if nothing else is using it
		Mesh::ReleaseMesh(m_cube);
	}

	if (m_blueCubeTexture)
	{
		Texture::ReleaseTexture(m_blueCubeTexture);
	}

}