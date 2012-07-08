#ifndef IS_FILE_HEADER
#define IS_FILE_HEADER

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

bool
is_file(const char *filename);
#endif
