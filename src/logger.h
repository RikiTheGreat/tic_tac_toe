#ifndef TIC_TAC_TOE_LOGGER_H
#define TIC_TAC_TOE_LOGGER_H

#include <spdlog/sinks/basic_file_sink.h>  // support for basic file logging
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

#include <string>

#include "base.h"
/**
 * @brief default logger for tictactoe project
 * @param level
 * @param msg
 */
void logger(QString const &msg, logger_level level = logger_level::INFO) noexcept;

#endif  // TIC_TAC_TOE_LOGGER_H
