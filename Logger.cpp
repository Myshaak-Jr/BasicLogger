#include "Logger.h"
#include <chrono>
#include <ctime>
#include <vector>

std::string CurrentDateTimeToString() {
	std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string output(30, '\0');

	struct tm timeinfo;

	localtime_s(&timeinfo, &now);

	strftime(&output[0], output.size(), "%Y-%b-%d %H:%M:%S", &timeinfo);

	return output;
}


std::vector<LogEntry> Logger::messages;
