/*	FIT2049 - Example Code
*	Texture.cpp
*	Created by Elliott Wilson & Mike Yeates - 2016 - Monash University
*	Implementation of Texture.h
*/

#include "Texture.h"
#include "DirectXTK/WICTextureLoader.h"

using namespace DirectX;

Texture::TextureMap Texture::textureMap;

Texture::Texture(LPCWSTR filename, const char* identifier, ID3D11Resource* texture, ID3D11ShaderResourceView* textureView)
{
	m_referenceCount = 0;
	m_filename = filename;
	m_identifier = identifier;
	m_texture = texture;
	m_textureView = textureView;
}

Texture::~Texture()
{
	if (m_texture)
	{
		m_texture->Release();
		m_texture = NULL;
	}

	if (m_textureView)
	{
		m_textureView->Release();
		m_textureView = NULL;
	}
}

bool Texture::LoadFromFile(LPCWSTR filename, const char* identifier, Direct3D* direct3D)
{
	//This method uses the CreateWICTextureFromFile function. This function comes from the DirectXToolKit library
	ID3D11Resource* texture;
	ID3D11ShaderResourceView* textureView;

	HRESULT result = CreateWICTextureFromFile(direct3D->GetDevice(), filename, &texture, &textureView);

	if (FAILED(result))
	{
		return false;
	}

	textureMap[identifier] = new Texture(filename, identifier, texture, textureView);

	return true;
}


Texture* Texture::GetTexture(const char* identifier)
{
	TextureMap::const_iterator searchResult = textureMap.find(identifier);

	if (searchResult != textureMap.end())
	{
		searchResult->second->AddRef();
		return searchResult->second;
	}

	return NULL;
}

void Texture::ReleaseTexture(Texture* texture)
{
	if (texture)
	{
		texture->RemoveRef();
		if (texture->GetRefCount() <= 0)
		{
			TextureMap::const_iterator searchResult = textureMap.find(texture->GetIdentifier());
			if (searchResult != textureMap.end())
			{
				textureMap.erase(searchResult);
			}
			delete texture;
			texture = NULL;

		}
	}
}

