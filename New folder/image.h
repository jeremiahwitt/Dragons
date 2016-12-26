/**
*@file image.h
*@brief Provides access to SDL_Image class, used for loading images and making textures out of them
*/
#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <cstring>
/*!
*this class is designed to abstract the process of loading and image
*and making a texture out of it for a window renderer
*/
class SDL_Image
{
private:
	SDL_Surface* _source;
	SDL_Texture* _image_texture;
	std::string _path;
	int _width;
	int _height;

public:
	SDL_Image(std::string path);
	void setupImageOnTargetWindowRenderer(SDL_Renderer* window_renderer);
	int getImageHeight();
	int getImageWidth();
	SDL_Texture* getImageTexture();
	void destroyImage();
	~SDL_Image();
};