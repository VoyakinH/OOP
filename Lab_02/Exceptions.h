#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include "ExceptionBase.hpp"

class MemoryException: public ExceptionBase {
public:
    MemoryException(std::string fileName, std::string className, int currentLine, const char *errorTime,
                    std::string information = "Ошибка работы с памятью."):
        ExceptionBase(fileName, className, currentLine, errorTime, information) { };
};

class DeletedObjectException: public ExceptionBase {
public:
    DeletedObjectException(std::string fileName, std::string className, int currentLine, const char *errorTime,
                           std::string information = "Объект не существует."):
        ExceptionBase(fileName, className, currentLine, errorTime, information) { };
};

class EmptyVectorException: public ExceptionBase {
public:
    EmptyVectorException(std::string fileName, std::string className, int currentLine, const char *errorTime,
                         std::string information = "Вектор пуст."):
        ExceptionBase(fileName, className, currentLine, errorTime, information) { };
};

class InvalidIndexException: public ExceptionBase {
public:
    InvalidIndexException(std::string fileName, std::string className, int currentLine, const char *errorTime,
                          std::string information = "Ошибка индексации."):
        ExceptionBase(fileName, className, currentLine, errorTime, information) { };
};

class ZeroDivisionException: public ExceptionBase {
public:
    ZeroDivisionException(std::string fileName, std::string className, int currentLine, const char *errorTime,
                          std::string information = "Деление на ноль."):
        ExceptionBase(fileName, className, currentLine, errorTime, information) { };
};

class InvalidCopyArrayPointer: public ExceptionBase {
public:
    InvalidCopyArrayPointer(std::string fileName, std::string className, int currentLine, const char *errorTime,
                            std::string information = "Исходный массив не существует."):
        ExceptionBase(fileName, className, currentLine, errorTime, information) { };
};

#endif // EXCEPTIONS_H
