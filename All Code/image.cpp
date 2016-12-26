#include "image.h"

//!constructor loads image from path and creates the texture for the reference window
SDL_Image::SDL_Image(std::string path)
{
	//set path and all other pointer to null
	_path = path;
	_source = nullptr;
	_image_texture = nullptr;
}

//!sets a texture on a target window renderer
void SDL_Image::setupImageOnTargetWindowRenderer(SDL_Renderer* window_renderer)
{
	//load image from file
	_source = IMG_Load(_path.c_str());
	if(_source == nullptr)
	{
		std::cout<<"Could not load image from path, "<<_path<<"."<<std::endl;
		system("pause");
		exit(-1);
	}
	_width = _source->w;
	_height = _source->h;

	//create texture from the image
	_image_texture = SDL_CreateTextureFromSurface(window_renderer, _source);
	if(_image_texture == nullptr)
	{
		std::cout<<"Failed to create texture from image in path, "<<_path<<"."<<std::endl;
		system("pause");
		exit(-1);
	}
}

//!access image texture
SDL_Texture* SDL_Image::getImageTexture()
{
	if(_image_texture == nullptr)
		std::cout<<"warning image from "<<_path<<" does not have a texture, returning null texture."<<std::endl;
	return _image_texture;
}

//!access image height
int SDL_Image::getImageHeight()
{
	return _height;
}

//!access image width
int SDL_Image::getImageWidth()
{
	return _width;
}

//!destroy the image setup
void SDL_Image::destroyImage()
{
	if(_image_texture != nullptr)
		SDL_DestroyTexture(_image_texture);
	if(_source != nullptr)
		SDL_FreeSurface(_source);

	_source = nullptr;
	_image_texture = nullptr;
}

//!destructor simply invokes the destryo image function
SDL_Image::~SDL_Image()
{
	destroyImage();
}