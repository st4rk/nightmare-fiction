#ifndef _SOUND_H_
#define _SOUND_H_

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>


/**
 * music chunk
 */
class musicChunk {
public:
	musicChunk(const std::string& dir);
	~musicChunk();

	Mix_Music* get();

private:
	Mix_Music *chunk;
};

/**
 * sound effects chunk
 */
class soundChunk {
public:
	soundChunk();
	soundChunk(const std::string& dir);
    ~soundChunk();

    bool load(const std::string& dir);

    Mix_Chunk *get();

private:
	Mix_Chunk *chunk;
};

/**
 * main sound unit
 */
class sound {
public:
	sound();
    ~sound();

    bool playSoundChunk(Mix_Chunk *chunk, int loop);
    bool playMusic(Mix_Music *chunk, int loop);

private:

};

#endif