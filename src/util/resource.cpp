#include <filesystem>
#include <iostream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <mach-o/dyld.h>
#endif

#ifdef __linux__
#include <unistd.h>
#endif

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
	ssize_t count = readlink("/proc/self/exe", result, sizeof(result));
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

std::string get_resource_dir() {
	return get_dir() + "/Resources/";
}
