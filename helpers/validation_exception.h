#pragma once
#include <TGlobal>

class T_HELPER_EXPORT ValidationException : public std::runtime_error {
public:
    ValidationException(const QString msg): runtime_error(msg.toStdString()) {};
    virtual ~ValidationException() throw() {};
};
