#pragma once
#include <TGlobal>

class T_HELPER_EXPORT NotFoundException : public std::runtime_error {
public:
    NotFoundException(const QString msg): runtime_error(msg.toStdString()) {};
    virtual ~NotFoundException() throw() {};
};
