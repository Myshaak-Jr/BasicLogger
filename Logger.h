#ifndef LOGGER_H
#define LOGGER_H

#include <string>
#include <vector>
#include <iostream>

enum LogType {
	LOG_INFO,
	LOG_DEBUG,
	LOG_WARNING,
	LOG_ERROR
};

struct LogEntry {
	LogType type;
	std::string message;
	std::string time;
};

std::string CurrentDateTimeToString();

class Logger {
private:
	static void print(const std::string msg, LogEntry& entry) {
		std::cout << msg;
		entry.message += msg;
	}
	static void print(const char* msg, LogEntry& entry) {
		std::cout << msg;
		entry.message += msg;
	}
	template <typename T> static void print(T msg, LogEntry& entry) {
		std::cout << msg;
		entry.message += std::to_string(msg);
	}

public:
	static std::vector<LogEntry> messages;
	
	template <typename ...TArgs> static void Log(TArgs&& ...args);
	template <typename ...TArgs> static void Debug(TArgs&& ...args);
	template <typename ...TArgs> static void Err(TArgs&& ...args);
};

template <typename ...TArgs>
static void Logger::Log(TArgs&& ...args) {
	std::string timeString = CurrentDateTimeToString();
	LogEntry logEntry;
	logEntry.type = LOG_INFO;
	logEntry.time = timeString;

	std::cout << "\033[1;32m" << "LOG: [" + CurrentDateTimeToString() + "]:";
	(print(args, logEntry), ...);
	std::cout << "\033[0m" << std::endl;

	messages.push_back(logEntry);
}

template <typename ...TArgs>
static void Logger::Debug(TArgs&& ...args) {
	std::string timeString = CurrentDateTimeToString();
	LogEntry logEntry;
	logEntry.type = LOG_DEBUG;
	logEntry.time = timeString;

	std::cout << "\033[2;37m" << "LOG: [" + CurrentDateTimeToString() + "]:";
	(print(args, logEntry), ...);
	std::cout << "\033[0m" << std::endl;

	messages.push_back(logEntry);
}

template <typename ...TArgs>
static void Logger::Err(TArgs&& ...args) {
	std::string timeString = CurrentDateTimeToString();
	LogEntry logEntry;
	logEntry.type = LOG_ERROR;
	logEntry.time = timeString;

	std::cout << "\033[1;31m" << "LOG: [" + CurrentDateTimeToString() + "]:";
	(print(args, logEntry), ...);
	std::cout << "\033[0m" << std::endl;

	messages.push_back(logEntry);
}

#endif