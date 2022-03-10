#include <iostream>

#include "dummy.h"
#include "note.h"
#include "config.h"

int main() {
    Dummy dummy;
    dummy.setCallbacks(Note::setFilenameHandler, Note::performReadByDateHandler,
                       Note::performReadAllDateHandler, Note::performWriteToFileHandler);
    std::wcout << LOG_INFO << "hello from dummy" << std::endl;
    return STATUS_SUCCESS;
}