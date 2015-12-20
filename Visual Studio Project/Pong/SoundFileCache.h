#pragma once


class SoundFileCache {
public:
	SoundFileCache();
	~SoundFileCache();

	sf::Sound GetSound(std::string) const;
	sf::Music* GetSong(std::string) const;

private:
	static std::map<std::string, sf::SoundBuffer*> _sounds;
	static std::map<std::string, sf::Music*> _music;

	// functor for deallocating both music and sound files
	template <typename T>
	struct Deallocator {
		void operator()(const std::pair<std::string, T> &p) {
			delete p.second;
		}
	};
};

class SoundNotFoundException : public std::runtime_error {
public:
	SoundNotFoundException(std::string const &msg):
		std::runtime_error(msg)
	{}
};

