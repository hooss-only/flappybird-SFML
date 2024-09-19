#include <stdlib.h>
#include <iostream>
#include <string>
#include <filesystem>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

#ifdef __linux__
#include <unistd.h>
#endif

#include <SFML/Graphics.hpp>

std::string get_executable_path() {
	char result[1024];

#ifdef _WIN32
	GetModuleFileName(NULL, result, sizeof(result));

#elif __APPLE__
	uint32_t size = sizeof(result);
	if (_NSGetExecutablePath(result, &size) != 0) {
		std::cerr << "Buffer too small; need size " << size << std::endl;
		return "";
	}

#elif __linux__
	size_t count = readlink("/proc/self/exe", result, sizeof(result));
	if (count == -1) {
		std::cerr << "Error reading symbolic link" << std::endl;
		return "";
	}

#else
	#error "Unsupported platform"
#endif

	return std::string(result);
}

std::string get_dir() {
	std::string exe_path = get_executable_path();
	return std::filesystem::path(exe_path).parent_path().string();
}

void load_texture(sf::Texture* texture, std::string image_path) {
	image_path = get_dir() + "/Resources/" + image_path;
	if (!texture->loadFromFile(image_path)) {
		std::cerr << "Error Loading " << image_path << std::endl;
		exit(1);
	}
}
