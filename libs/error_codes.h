#ifndef ERROR_CODES_H
#define ERROR_CODES_H

typedef enum Error_code
{
    SUCCESS,
    WARNING_FILE_READ,
    ERROR_ALLOCATION,
    ERROR_FILE_OPEN,
    ERROR_FILE_READ,
    ERROR_FILE_WRITE,
    ERROR_IMPORT
} Error_code;

#endif // ERROR_CODES_H