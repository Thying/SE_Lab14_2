#pragma once

// Макросы для генерации объектов ERROR
#define ERROR_THROW(id) Error::geterror(id)
#define ERROR_THROW_IN(id, line, col) Error::geterrorin(id, line, col)

// Макросы для определения элементов таблицы ошибок
#define ERROR_ENTRY(id, m) {id, m, {-1, -1}}
#define ERROR_MAXSIZE_MESSAGE 200 // максимальная длина сообщения об ошибке
#define ERROR_ENTRY_NODEF(id) ERROR_ENTRY(id, "Неопределенная ошибка")
#define ERROR_ENTRY_NODEF10(id) \
    ERROR_ENTRY_NODEF(id+0), ERROR_ENTRY_NODEF(id+1), ERROR_ENTRY_NODEF(id+2), \
    ERROR_ENTRY_NODEF(id+3), ERROR_ENTRY_NODEF(id+4), ERROR_ENTRY_NODEF(id+5), \
    ERROR_ENTRY_NODEF(id+6), ERROR_ENTRY_NODEF(id+7), ERROR_ENTRY_NODEF(id+8), \
    ERROR_ENTRY_NODEF(id+9)
#define ERROR_ENTRY_NODEF100(id) \
    ERROR_ENTRY_NODEF10(id+ 0), ERROR_ENTRY_NODEF10(id+10), ERROR_ENTRY_NODEF10(id+20), \
    ERROR_ENTRY_NODEF10(id+30), ERROR_ENTRY_NODEF10(id+40), ERROR_ENTRY_NODEF10(id+50), \
    ERROR_ENTRY_NODEF10(id+60), ERROR_ENTRY_NODEF10(id+70), ERROR_ENTRY_NODEF10(id+80), \
    ERROR_ENTRY_NODEF10(id+90)

// Максимальное количество элементов в таблице ошибок
#define ERROR_MAX_ENTRY 1000

// Пространство имен для класса Error
namespace Error {

	// Структура для хранения информации об ошибке
	struct ERROR {
		int id;
		char message[ERROR_MAXSIZE_MESSAGE];
		struct IN {
			short line;
			short col;
		} inext;
	};

	// Функция для создания объекта ERROR
	ERROR geterror(int id);

	// Функция для создания объекта ERROR с информацией о строке и колонке
	ERROR geterrorin(int id, int line, int col);
}