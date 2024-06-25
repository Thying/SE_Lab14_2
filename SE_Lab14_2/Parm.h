#pragma once

#define PARM_IN "-in:"          // ключ для файла исходного кода 
#define PARM_OUT "-out:"        // ключ для файла объектного кода 
#define PARM_LOG "-log:"        // ключ для файла журнала 
#define PARM_MAX_SIZE 300        // максимальная длина строки параметра 
#define PARM_OUT_DEFAULT_EXT ".out"  // расширение файла объектного кода по умолчанию 
#define PARM_LOG_DEFAULT_EXT ".log"  // расширение файла протокола по умолчанию


namespace Parm {
    // обработка входных параметров

    struct PARM {
        // входные параметры
        char in[PARM_MAX_SIZE];    // -in: имя файла исходного кода
        char out[PARM_MAX_SIZE];    // -out: имя файла объектного кода
        char log[PARM_MAX_SIZE];    // -log: имя файла протокола
    };

    PARM getparm(int argc, char* argv[]);
    //int _tmain(int argc, _TCHAR* argv[])
    // сфрмировать struct PARM на основе параметров функции main
}