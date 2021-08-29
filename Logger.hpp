
#ifndef CHESSTRAINER_LOGGER_
#define CHESSTRAINER_LOGGER_

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <memory>
#include <map>
#include <ctime>
#include <iomanip>
#include <mutex>
#include <thread>

namespace ChessTrainer::Logger {
    class InvalidPath : std::exception {
        public:
        explicit InvalidPath(const std::string& path) : path_(path) {};
        const char* what() const noexcept override {
            static std::string message = "Invalid path: " + this->path_;
            return (message.c_str());
        };

        private:
        std::string path_;
    };

    enum level_e : uint16_t {
        LOG_DEBUG_E = 0b00001u,
        LOG_INFO_E = 0b00010u,
        LOG_WARN_E = 0b01000u,
        LOG_ERROR_E = 0b10000u,
    };

    [[maybe_unused]] static const constexpr uint8_t g_AllLogLevel =
        LOG_DEBUG_E | LOG_INFO_E | LOG_WARN_E | LOG_ERROR_E;

    [[maybe_unused]] static const constexpr uint8_t g_ProdLogLevel =
        LOG_INFO_E | LOG_WARN_E | LOG_ERROR_E;
    /**
     * Log is a logger with different level:
     *  - DEBUG
     *  - INFO
     *  - WARNING
     *  - ERROR
     * It write the logs inside a file and in the C++ standard output with a timestamp
     */
    class Logger : public std::enable_shared_from_this<Logger> {
        public:
        using shared_log_t = std::shared_ptr<Logger>;
        /**
         * Open or create the log file
         * @param title The main title of the log
         * @param path Path to the log's file
         * @param logLevel The log level. You can use bitwise operator on it with the modes above, default: all logs level
         * @param openMode Open mode for the log's file, default: append s text to the end
         * @throws InvalidPath
         */
        explicit Logger(const std::string& title, const std::string& path,
                        bool silent = false,
                        uint8_t logLevel = LOG_DEBUG_E | LOG_INFO_E | LOG_WARN_E
                            |
                                LOG_ERROR_E,
                        std::ios_base::openmode open_mode = std::ios::app) :
            silent(silent),
            title_(title),
            path_(path),
            file_(path, open_mode),
            level_(static_cast<level_e>(logLevel)),
            open_mode_(open_mode) {
            if (!this->file_.is_open())
                throw InvalidPath(path);
            std::cout.setf(std::ios::unitbuf);
        }

        Logger(const Logger& log) : Logger(log.title_,
                                           log.path_,
                                           log.level_,
                                           log.open_mode_) {}

        ~Logger() {
            this->file_.close();
        };

        template <typename ...variadic>
        void Debug(variadic&& ... args) {
            return (this->Write(LOG_DEBUG_E, args...));
        }
        template <typename ...variadic>
        void Debug(variadic&& ... args) const {
            return (this->Write(LOG_DEBUG_E, args...));
        }

        template <typename ...variadic>
        void Warning(variadic&& ... args) {
            return (this->Write(LOG_WARN_E, args...));
        }
        template <typename ...variadic>
        void Warning(variadic&& ... args) const {
            return (this->Write(LOG_WARN_E, args...));
        }

        template <typename ...variadic>
        void Error(variadic&& ... args) {
            return (this->Write(LOG_ERROR_E, args...));
        }
        template <typename ...variadic>
        void Error(variadic&& ... args) const {
            return (this->Write(LOG_ERROR_E, args...));
        }

        template <typename ...variadic>
        void Info(variadic&& ... args) {
            return (this->Write(LOG_INFO_E, args...));
        }
        template <typename ...variadic>
        void Info(variadic&& ... args) const {
            return (this->Write(LOG_INFO_E, args...));
        }

        private:
        static std::string GetCurrentTime() {
            auto timer =
                std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
            std::ostringstream oss;
            oss << std::put_time(std::localtime(&timer), "%Y-%m-%d %H:%M:%S");
            return oss.str();
        }

        template <typename ...variadic>
        void Write(level_e level, variadic&& ... args) {
            if ((level & this->level_) == 0)
                return;
            std::unique_lock<std::mutex> lock(this->mutex_);
            std::string prefix("[" + Logger::GetCurrentTime() + "/" +
                this->title_ + "/" +
                map_.find(level)->second);
            if (!silent) {
                if (level != LOG_ERROR_E) {
                    std::cout << prefix + "/";
                    std::cout << std::this_thread::get_id();
                    std::cout << "] ";
                    (std::cout << ... << args) << std::endl;
                } else {
                    std::cerr << prefix + "/";
                    std::cerr << std::this_thread::get_id();
                    std::cerr << "] ";
                    (std::cerr << ... << args) << std::endl;
                }
            }
            this->file_ << prefix + "] ";
            (this->file_ << ... << args) << std::endl;
        }

        bool silent;
        std::string title_;
        std::string path_;
        std::ofstream file_;
        level_e level_;
        std::ios_base::openmode open_mode_;
        std::mutex mutex_;
        const std::map<uint8_t, std::string> map_ = {
            {LOG_DEBUG_E, "debug"},
            {LOG_INFO_E, "info"},
            {LOG_WARN_E, "warning"},
            {LOG_ERROR_E, "error"},
        };
    };
}

#endif //CHESSTRAINER_LOGGER_
