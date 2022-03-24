#include "log.h"
#include <iostream>

int main() {
    LOG(LOG_ERROR, "log_error: aaa", 12);
    LOG(LOG_DEBUG, "log_debug: aaa", 12);
    return 0;
}
