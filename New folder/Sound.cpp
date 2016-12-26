#include "Sound.h"
//!defaul constructor takes in the path of the asset and creates the effect
OneTimeEffect::OneTimeEffect(std::string path)
{
	this->_path = path;
	this->_effect = Mix_LoadWAV( _path.c_str() );
	if(this->_effect == nullptr)
	{
		//std::cout<<"Could not load sound effect "<<path.c_str()<<"\n"<<SDL_GetError()<<std::endl;
		//std::cout<<std::endl;
		//system("pause");
	}
}
//!sets the volume
void OneTimeEffect::setVolume(int volume)
{
	Mix_VolumeMusic(volume);
}
//!plays the sound effect once
void OneTimeEffect::play()
{
	Mix_PlayChannel(-1, this->_effect, 0 );
}
//!destroys the sound effect and frees up memory that was alloted for it
OneTimeEffect::~OneTimeEffect()
{
	if(this->_effect != nullptr)
	{
		Mix_FreeChunk(_effect);
		this->_effect = nullptr;
	}
}
//!defaul constructor takes in the path of the asset and creates the effect
ContinousEffect::ContinousEffect(std::string path)
{
	this->_path = path;
	this->_music = Mix_LoadMUS( _path.c_str() );
	if(this->_music == nullptr )
	{
		std::cout<<"Could not load music, "<<path.c_str()<<" "<<SDL_GetError()<<std::endl;
		system("pause");
	}
}



//!plays the music continously in infinite loops until it is stopped
void ContinousEffect::play()
{
	Mix_PlayMusic( this->_music, -1 );
}
//!plays the music continously in infinite loops until it is stopped, the play is faded in as per parameter passed in milliseconds
void ContinousEffect::fadeInPlay(int milliseconds)
{
	Mix_FadeInMusic(this->_music, -1, milliseconds);
}
//!stops music play in one shot
void ContinousEffect::stopPlay()
{
	Mix_HaltMusic();
}
//!sets volume
void ContinousEffect::setVolume(int volume)
{
	Mix_VolumeMusic(volume);
}

//!stops music play, fades it out as per parameter passed in milliseconds
void ContinousEffect::fadeOutStopPlay(int milliseconds)
{	 	
	while(!Mix_FadeOutMusic(milliseconds) && Mix_PlayingMusic()) 
	{
		SDL_Delay(100);
	}
}
//!destroys the sound effect and frees up memory that was alloted for it
ContinousEffect::~ContinousEffect()
{
	if(this->_music != nullptr)
	{
		Mix_FreeMusic(_music);
		this->_music = nullptr;
	}
}
	