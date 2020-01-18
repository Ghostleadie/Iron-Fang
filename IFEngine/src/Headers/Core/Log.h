/*!
* \file log.h
* \brief header file for the logging fuctions in the engine
*
* This will be used for all outputs into the terminal as spdlog provideds a nicer looking output than std::cout.
*/

#pragma once
#include "Base.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

/*!
* \namespace IronFang
* \brief This is the standard namespace for the engine.
*/


namespace IronFang 
{
	/*!
	* \class Log
	* \brief The log class is for output in the terminal for error or information that is need/asked for
	*/
	class Log {
	public:
		/*!
		* \fn Init
		* \brief This function initalizes the logger.
		*
		* This function sets the pattern for the loggers (how the output looks in the terminal), it also sets the 
		*/
		static void Init();
		inline static sharedP<spdlog::logger>& GetEngineLogger() { return s_EngineLogger; }
		inline static sharedP<spdlog::logger>& GetGameLogger() { return s_GameLogger; }

	private:
		static sharedP<spdlog::logger> s_EngineLogger;
		static sharedP<spdlog::logger> s_GameLogger;
	};
}