#include <iostream>

#include "dummy.h"
#include "note.h"
#include "config.h"
#include "log.h"

int main() {
    LOG_INFO("hello from dummy");
    Dummy dummy;
    return STATUS_SUCCESS;
}