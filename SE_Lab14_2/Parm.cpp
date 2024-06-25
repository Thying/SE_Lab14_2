#define _CRT_SECURE_NO_WARNINGS
#include "Parm.h"
#include "Error.h"
#include <cstring>

namespace Parm {
    PARM getparm(int argc, char* argv[]) {
        PARM parm = {}; // Инициализация структуры PARM

        // Проверьте, указан ли параметр -in:.
        bool inFound = false;
        for (int i = 1; i < argc; ++i) {
            if (std::strncmp(argv[i], PARM_IN, strlen(PARM_IN)) == 0) {
                inFound = true;
                // Извлеките значение параметра -in:
                std::strncpy(parm.in, argv[i] + strlen(PARM_IN), PARM_MAX_SIZE);
                break; // Прекратите поиск -in:
            }
        }

        if (!inFound) {
            // Выбросьте ошибку, если -in: не указан.
            throw ERROR_THROW(100);
        }

        // Установите значения по умолчанию для -out: и -log:, если они не указаны.
        std::strcpy(parm.out, parm.in);
        std::strcat(parm.out, PARM_OUT_DEFAULT_EXT);
        std::strcpy(parm.log, parm.in);
        std::strcat(parm.log, PARM_LOG_DEFAULT_EXT);

        // Разберите оставшиеся параметры (-out: и -log:)
        for (int i = 1; i < argc; ++i) {
            if (std::strncmp(argv[i], PARM_OUT, strlen(PARM_OUT)) == 0) {
                std::strncpy(parm.out, argv[i] + strlen(PARM_OUT), PARM_MAX_SIZE);
            }
            else if (std::strncmp(argv[i], PARM_LOG, strlen(PARM_LOG)) == 0) {
                std::strncpy(parm.log, argv[i] + strlen(PARM_LOG), PARM_MAX_SIZE);
            }
        }

        // Проверьте длину каждого входного параметра
        if (std::strlen(parm.in) > PARM_MAX_SIZE ||
            std::strlen(parm.out) > PARM_MAX_SIZE ||
            std::strlen(parm.log) > PARM_MAX_SIZE) {
            throw ERROR_THROW(104);
        }

        return parm;
    }
}
