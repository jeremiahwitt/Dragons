/**
*@file Sound.h
*@brief Provides the methods required to implement the sound engine!
*/
#if !defined (SOUND_H)
#define SOUND_H
#include "sdl_initialize.h"

/**
*@class Sound
*@brief Gives ability to play sound during the game
*/
class Sound
{
protected:
	std::string _path;

public:
	Sound(){};
	virtual void play() = 0;
};

/**
*@class OneTimeEffect
*@brief Class for implementing a one-off sound that only occurs once
*/
class OneTimeEffect : public Sound
{
private:
	Mix_Chunk* _effect;

public:
	OneTimeEffect(std::string path);
	void setVolume(int);
	void play();
	~OneTimeEffect();
};

/**
*@class ContinuousEffect
*@brief Provides the ability to play a sound continuously while the program is running
*/
class ContinousEffect : public Sound
{
private:
	Mix_Music* _music;

public:
	ContinousEffect(std::string path);
	void play();
	void fadeInPlay(int milliseconds);
	void setVolume(int);
	void stopPlay();
	void fadeOutStopPlay(int milliseconds);
	~ContinousEffect();
};

#endif