#include "stdafx.h"
#include "SFMLSoundProvider.h"


SFMLSoundProvider::SFMLSoundProvider() :
_currentSongName("")
{
}

void SFMLSoundProvider::PlaySound(std::string filename) {
	int availChannel = -1;
	for (int i = 0; i < MAX_SOUND_CHANNELS; i++) {
		if (_currentSounds[i].getStatus() != sf::Sound::Playing) {
			availChannel = i;
			break;
		}
	}
	// If a channel is not in use, play using that channel
	if (availChannel != -1) {
		try {
			_currentSounds[availChannel] = _soundFileCache.GetSound(filename);
			_currentSounds[availChannel].play();
		}
		catch (SoundNotFoundException&) {
			// Sound Not found
			return;
		}
	}
}

void SFMLSoundProvider::PlaySong(std::string filename, bool looping) {
	sf::Music *currentSong;
	try {
		currentSong = _soundFileCache.GetSong(filename);
	}
	catch (SoundNotFoundException&) {
		return;
	}
	if (_currentSongName != "") {
		try {
			sf::Music *priorSong = _soundFileCache.GetSong(_currentSongName);
			if (priorSong->getStatus() != sf::Sound::Stopped) {
				priorSong->stop();
			}
		}
		catch (SoundNotFoundException&) {
			//previous song not found
		}
	}
	_currentSongName = filename;
	currentSong->setLoop(looping);
	currentSong->play();
}

void SFMLSoundProvider::StopAllSounds() {
	for (int i = 0; i < MAX_SOUND_CHANNELS; i++) {
		_currentSounds[i].stop();
	}
	if (_currentSongName != "") {
		sf::Music *currentSong = _soundFileCache.GetSong(_currentSongName);
		if (currentSong->getStatus() == sf::Sound::Playing) {
			currentSong->stop();
		}
	}
}

bool SFMLSoundProvider::IsSoundPlaying() {
	for (int i = 0; i < MAX_SOUND_CHANNELS; i++) {
		if (_currentSounds[i].getStatus() == sf::Sound::Playing) {
			return true;
		}
	}
	return false;
}

bool SFMLSoundProvider::IsSongPlaying() {
	if (_currentSongName != "") {
		return _soundFileCache.GetSong(_currentSongName)->getStatus() ==
			sf::Music::Playing;
	}
	return false;
}