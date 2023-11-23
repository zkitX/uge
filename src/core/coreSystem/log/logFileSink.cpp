#include "build.h"

#include "logQueue.h"
#include "logFileSink.h"
#include "file/file.h"

namespace uge::log
{
    LogFileSink::LogFileSink()
        : m_file(nullptr)
    {
    }

    LogFileSink::~LogFileSink()
    {
        CloseFile();
    }

    void LogFileSink::SinkLog(const char *formattedMsg, const LogLine &logLine)
    {
        if (m_file != nullptr)
        {
            file::FilePrint(m_file, formattedMsg);
        }
    }

    void LogFileSink::Flush()
    {
        if (m_file != nullptr)
        {
            file::FileFlush(m_file);
        }
    }

    Bool LogFileSink::OpenFile(const char *filename, const char *mode)
    {
        Bool result = file::FileOpen(&m_file, filename, mode);
        return result;
    }

    Bool LogFileSink::CloseFile()
    {
        if (m_file != nullptr)
        {
            file::FileFlush(m_file);
            file::FileClose(m_file);
            m_file = nullptr;
        }
        return true;
    }
}