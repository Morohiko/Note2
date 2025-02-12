#include <iostream>

#include "dummy.h"
#include "note.h"
#include "config.h"
#include "log.h"

int main() {
    Dummy dummy;
    dummy.setCallbacks(Note::setFilenameHandler, Note::performReadByDateHandler,
                       Note::performReadAllDateHandler, Note::performWriteToFileHandler);
    LOG_INFO("hello from dummy");
    return STATUS_SUCCESS;
}