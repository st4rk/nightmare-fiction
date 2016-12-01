#include "sound.h"


/**
 * music chunk
 */
musicChunk::musicChunk(const std::string& dir) {
	chunk = Mix_LoadMUS(dir.c_str());

	if (chunk == nullptr) {
		std::cout << "Error while loading music :" << dir << std::endl;
	}

}

musicChunk::~musicChunk() {
	if (chunk != nullptr) {
		Mix_FreeMusic(chunk);
		chunk = nullptr;
	}
}

Mix_Music* musicChunk::get() { return chunk; }

/**
 * sound effects chunk
 */
soundChunk::soundChunk() {
	chunk = nullptr;
	
}

soundChunk::soundChunk(const std::string& dir) {
	chunk = Mix_LoadWAV(dir.c_str());

	if (chunk == nullptr) {
		std::cout << "Error while loading sfx : " << dir << std::endl;
	}
}

soundChunk::~soundChunk() {
	if (chunk != nullptr) {
		Mix_FreeChunk(chunk);
		chunk = nullptr;
	}
}

bool soundChunk::load(const std::string& dir) {
	chunk = Mix_LoadWAV(dir.c_str());

	if (chunk == nullptr) {
		std::cout << "Error while loading sfx : " << dir << std::endl;
		return false;
	}

	return true;
}

Mix_Chunk *soundChunk::get() { return chunk; }

/**
 * main sound unit
 */
sound::sound() {
	if (SDL_Init(SDL_INIT_AUDIO) < 0) {
		std::cout << "Error while initializing SDL Audio !" << std::endl;
		exit(0);
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
		std::cout << "Error while initializing Mix OpenAudio" << std::endl;
		exit(0);
	}
}

sound::~sound() {
	Mix_CloseAudio();
	SDL_Quit();
}


bool sound::playSoundChunk(Mix_Chunk *chunk, int loop) {
	if (Mix_PlayChannel(-1, chunk, loop) == -1) {
		std::cout << "Error while playing a sound chunk !" << std::endl;
		std::cout << "SDL_Mix error: " << Mix_GetError() << std::endl;
		return false;
	}
	return true;
}

bool sound::playMusic(Mix_Music *chunk, int loop) {
	if (Mix_PlayMusic(chunk, loop) == -1) {
		std::cout << "Error while playing a music chunk!" << std::endl;
		std::cout << "SDL_Mix error: " << Mix_GetError() << std::endl;
		return false;
	}

	return true;
}