#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <mutex>

class Logger {
public:
    // �̱��� ����
    static Logger& getInstance() {
        static Logger instance;
        return instance;
    }
    void myLog(const std::string& _msg) {
        std::lock_guard<std::mutex> lock(m_mutex);

        std::ofstream logFile("log.txt", std::ios::app);
        if (logFile.is_open()) {
            logFile << _msg << std::endl;
            logFile.close();
        }
        else {
            std::cerr << "Error: Unable to open log file." << std::endl;
        }
    }

    Logger(const Logger&) = delete;
    Logger& operator=(const Logger&) = delete;

private:
    Logger() {}
    ~Logger() {}

    std::mutex m_mutex; // ��Ƽ������ ȯ�濡�� �����ϰ� ����ϱ� ���� ���ؽ�
};