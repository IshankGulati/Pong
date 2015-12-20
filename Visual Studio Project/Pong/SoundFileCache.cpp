#include "stdafx.h"
#include "SoundFileCache.h"

SoundFileCache::SoundFileCache(){}

SoundFileCache::~SoundFileCache() {
	std::for_each(_sounds.begin(), _sounds.end(), Deallocator<sf::SoundBuffer*>());
	std::for_each(_music.begin(), _music.end(), Deallocator<sf::Music*>());
}

sf::Sound SoundFileCache::GetSound(std::string soundName) const {
	std::map<std::string, sf::SoundBuffer*>::iterator itr;
	itr = _sounds.find(soundName);
	// If not found, try to load from disk
	// If sound not on disk, throw an exception
	if (itr == _sounds.end()) {
		sf::SoundBuffer *soundBuffer = new sf::SoundBuffer();
		if (!soundBuffer->loadFromFile(soundName)) {
			delete soundBuffer;
			throw SoundNotFoundException(soundName +
				"was not found in call to SoundFileCache::GetSound");
		}
		_sounds.insert(std::make_pair(soundName, soundBuffer));

		sf::Sound sound;
		sound.setBuffer(*soundBuffer);
		return sound;
	}
	else {
		sf::Sound sound;
		sound.setBuffer(*itr->second);
		return sound;
	}
}

sf::Music* SoundFileCache::GetSong(std::string soundName) const
{
	std::map<std::string, sf::Music *>::iterator itr = _music.find(soundName);
	// If not found, try to load from disk
	// If sound not on disk, throw an exception
	if (itr == _music.end())
	{
		sf::Music * song = new sf::Music();
		if (!song->openFromFile(soundName))
		{
			delete song;
			throw SoundNotFoundException(
				soundName + " was not found in call to SoundFileCache::GetSong");
		}
		else
		{
			std::map<std::string, sf::Music *>::iterator res;
			res = _music.insert(std::make_pair(soundName, song)).first;
			return res->second;
		}
	}
	else
	{
		return itr->second;
	}
}

std::map<std::string, sf::SoundBuffer*> SoundFileCache::_sounds;
std::map<std::string, sf::Music*> SoundFileCache::_music;