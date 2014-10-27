
#include <iostream>

#include "lightsky/utils/assert.h"

namespace ls {

void utils::runtime_assert(bool condition, error_t type, const char* const msg) {
	if (condition) {
        return;
    }

	const char* const errorString[] = {"ALERT: ", "WARNING: ", "ERROR: "};
	std::ostream& stream = (type > utils::ALERT) ? std::cerr : std::cout;
	
	stream << errorString[type] << msg << std::endl;

	if (type == utils::ERROR) {
        throw utils::ERROR;
    }
}

} // end ls namespace
