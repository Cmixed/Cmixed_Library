/**
 * @file zzj.hpp
 * @author Zee Cmixed (cmixed@foxmail.com)
 * @brief cmixed's private c++ library
 * @version 0.6
 * @date 2024-08-16
 *
 *
 * @copyright Abandon copy
 *
 * @note Log 	 (thread safe)
 * 		 Color
 */


#pragma once

#include <iostream>
#include <format>
#include <string>
#include <string_view>
#include <source_location>
#include <filesystem>
// #include <thread>
// #include <mutex>
// #include <complex>

#define _ZZJ_NAMESPACE_BEGIN namespace zzj {
#define _ZZJ_NAMESPACE_END   }

_ZZJ_NAMESPACE_BEGIN

/***************************************************************************************** */
// for control
/***************************************************************************************** */

struct ColorCtrlSettings
{
	bool is_ToDefault { true };
} ColorCtrl;

enum class ColorName {
		DEFAULT = 0,
		RED = 1,
		GREEN = 2,
		YELLOW = 3,
		BLUE = 4,
		MAGENTA = 5,
		CYAN = 6,
		WHITE = 7
};

// main LogCtrl
struct LogCtrlSettings
{
	bool is_Log { true };
	bool is_ToFile { false };

	// LogTerminalCtrl
	struct LogTerminalCtrlSettings
	{
		std::string g_initialMessage { "[Log]"};
		bool is_logMessage { true };
		bool is_logFilePath { false };
		bool is_logFileName { false };
		bool is_logFunctionName { true };
		bool is_logLineNumber { true };
		bool is_logColumnNumber { true };
	} LogTerminalCtrl;

	// LogFileCtrl
	struct LogFileCtrlSettings
	{
		std::string logFileName { "log.txt" };
		std::filesystem::path logFilePath { std::filesystem::current_path() / logFileName };
	} LogFileCtrl;
} LogCtrl;


/***************************************************************************************** */
// for class
/***************************************************************************************** */
class Color
{
private:
	ColorName m_colorName;
public:
// class functions
	Color() = default;
	Color(ColorName color);
	~Color();
// member functions
	void switchOutFrontColor(ColorName colorName);
	void display();
};

class Log
{
private:
// variables
	std::string m_outMessage;
	std::string_view m_message;
	std::source_location m_location;
	Color m_color;
	// inline static std::mutex ms_mutex;
// functions
public:
	Log(std::string_view message, ColorName displayColor,
			const std::source_location& location);
	~Log() = default;
// member functions
	void display();
};


/***************************************************************************************** */
// for coding
/***************************************************************************************** */

Log::Log(std::string_view message, ColorName displayColor = ColorName::YELLOW,
			const std::source_location& location = std::source_location::current() )
	: m_outMessage { LogCtrl.LogTerminalCtrl.g_initialMessage }, m_message { message },
		m_location { location }, m_color { displayColor }
{
	if (LogCtrl.is_Log) {
		if (LogCtrl.LogTerminalCtrl.is_logMessage) m_outMessage += std::format("[Msg:{}]", m_message);
		if (LogCtrl.LogTerminalCtrl.is_logFileName) m_outMessage += std::format("[File:{}]", m_location.file_name());
		if (LogCtrl.LogTerminalCtrl.is_logFunctionName) m_outMessage += std::format("[Func:{}]", m_location.function_name());
		if (LogCtrl.LogTerminalCtrl.is_logLineNumber) m_outMessage += std::format("[Line:{}]", m_location.line());
		if (LogCtrl.LogTerminalCtrl.is_logColumnNumber) m_outMessage += std::format("[Col:{}]", m_location.column());

		std::cout << std::format("{}\n", m_outMessage);
	}
}

void Log::display()
{
	m_color.display();
	std::cout << std::format("{}\n", m_outMessage);
}




Color::Color(ColorName colorName)
	: m_colorName { colorName }
{
	switchOutFrontColor(colorName);
}

Color::~Color()
{
	if (ColorCtrl.is_ToDefault) {
		switchOutFrontColor(ColorName::DEFAULT);
	}
}

void Color::display()
{
	Color tempColor { m_colorName };
}

void Color::switchOutFrontColor(ColorName colorName)
{
	using enum ColorName;

	switch (colorName) {
		case DEFAULT:	std::cout << "\033[0m";		break;
		case RED:		std::cout << "\033[31m";	break;
		case GREEN:		std::cout << "\033[32m";	break;
		case YELLOW:	std::cout << "\033[33m";	break;
		case BLUE:		std::cout << "\033[34m";	break;
		case MAGENTA:	std::cout << "\033[35m";	break;
		case CYAN:		std::cout << "\033[36m"; 	break;
		case WHITE:		std::cout << "\033[37m"; 	break;
		default:	std::cout << "{[Error]ColorName is not valid!}";	break;
	}
}


_ZZJ_NAMESPACE_END


// for global

zzj::Log operator"" _log(char const* str, size_t len)
{
	return zzj::Log { std::string(str, len) };
}