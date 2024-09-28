#include <SFML/Audio.hpp>
#include <stdlib.h>
#include <iostream>

void load_audio(sf::SoundBuffer* sound_buffer, std::string sound_path) {
	sound_path = "Resources/" + sound_path;
	if (!sound_buffer->loadFromFile(sound_path)) {
		std::cerr << "Error Loading " << sound_path << std::endl;
		exit(1);
	}
}
