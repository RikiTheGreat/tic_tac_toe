#include "logger.h"

#include <QDebug>

void logger(QString const &msg, logger_level level) noexcept {
    // create a logger which prints on terminal and file
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::warn);
    console_sink->set_pattern("[multi_sink_example] [%^%l%$] %v");
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("../Logs/logs.txt");
    file_sink->set_level(spdlog::level::trace);
    spdlog::logger logger("ttt_logger", {console_sink, file_sink});

    switch (level) {
    case logger_level::WARN:
        logger.log(spdlog::level::warn, msg.toStdString());
        break;
    case logger_level::INFO:
        logger.log(spdlog::level::info, msg.toStdString());
        qInfo() << msg;
        break;
    case logger_level::ERROR:
        logger.log(spdlog::level::err, msg.toStdString());
        break;
    }
}
