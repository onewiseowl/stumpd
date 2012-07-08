
#include <stumpd/utilities/split.hpp>
#include <string>

std::vector < std::string > stumpd::utilities::split(const char *str, char c = ' ')
{
    std::vector < std::string > result;
    const char *begin;

    while (1) {
        begin = str;
	while (*str != c && *str)
	    str++;

	result.push_back(std::string(begin, str));
	fprintf(stdout, "Pushed back: %s\n", std::string(begin, str).c_str());

	if (0 == *str++)
        {
	  break;
        } else {
          while(*str == c && *str)
            str++;
        }
    }

    begin = NULL;
    return result;
}
