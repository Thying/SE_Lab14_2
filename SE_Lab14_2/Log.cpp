#include "Error.h"   //��������� ������
#include "Parm.h"    //��������� ����������
#include "Log.h"   //������ � ����������
#include "In.h"   // ���� ��������� �����
#include <stdarg.h>
#include <fstream>
#include <iostream>
#include <cwchar>
#include <stdexcept>

namespace Log {

    // ������� ��� ��������� ������� LOG
    LOG getlog(wchar_t logfile[]) {
        LOG log = { { L'\0' }, nullptr };
        wcscpy_s(log.logfile, PARM_MAX_SIZE, logfile);

        // ������� ������� ���� ��� ������
        log.stream = new std::ofstream(log.logfile, std::ios::out | std::ios::binary);

        // �������� ��������� �������� �����
        if (!log.stream->is_open()) {
            // ������������� ���������� ��� ������ �������� �����
            throw std::runtime_error("������ �������� ����� ��� ������ ����.");
        }

        return log;
    }

    void WriteLine(LOG log, char* c, ...) {
        va_list args;
        va_start(args, c);

        std::string output = c;
        while (*c != '\0') {
            output += va_arg(args, char*);
            c++;
        }

        *log.stream << output << std::endl;

        va_end(args);
    }

    void WriteLine(LOG log, wchar_t* wc, ...) {
        va_list args;
        va_start(args, wc);

        std::wstring output = wc;
        while (*wc != L'\0') {
            output += va_arg(args, wchar_t*);
            wc++;
        }

        // �������������� wstring � string
        std::string output_str;
        output_str.resize(output.size());
        std::copy(output.begin(), output.end(), output_str.begin());

        *log.stream << output_str << std::endl;

        va_end(args);
    }

    void WriteLog(LOG log) {
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "��� ���������:" << std::endl;
        *log.stream << "-------------------------" << std::endl;
    }

    void WriteParm(LOG log, Parm::PARM parm) {
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "������� ���������:" << std::endl;
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "������� ����: " << parm.in << std::endl;
        *log.stream << "�������� ����: " << parm.out << std::endl;
        *log.stream << "���� �����: " << parm.log << std::endl;
        *log.stream << "-------------------------" << std::endl;
    }

    void WriteIn(LOG& log, const In::IN& in) {
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "������� �����:" << std::endl;
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "������:" << in.size << std::endl;
        *log.stream << "��� ������:" << in.code << std::endl;
        *log.stream << "-------------------------" << std::endl;
    }

    void WriteError(LOG log, Error::ERROR error) {
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "������:" << std::endl;
        *log.stream << "-------------------------" << std::endl;
        *log.stream << "��� ������:" << error.id << std::endl;
        *log.stream << "���������:" << error.message << std::endl;
        if (error.inext.line != -1 && error.inext.col != -1) {
            *log.stream << "������: " << error.inext.line << ", �������: " << error.inext.col << std::endl;
        }
        *log.stream << "-------------------------" << std::endl;
    }

    void Close(LOG log) {
        if (log.stream != nullptr) {
            log.stream->close();
            // ������� ����� ������ ���� �� ��� ������ � ������� 'new'
            if (log.stream != &std::cout && log.stream != &std::cerr) {
                delete log.stream;
            }
        }
    }

} // namespace Log
