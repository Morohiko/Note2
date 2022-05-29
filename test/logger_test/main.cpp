#include "log.h"
#include <iostream>

int main() {
    WLOG(LOG_ERROR, "log_error: aaa", 12);
    WLOG(LOG_DEBUG, "log_debug: aaa", 12);
    return 0;
}
