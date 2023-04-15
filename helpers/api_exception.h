#pragma once
#include <TGlobal>

class T_HELPER_EXPORT ApiException : public std::runtime_error {
public:
    ApiException(const QString msg): runtime_error(msg.toStdString()) {};
    virtual ~ApiException() throw() {};
};
