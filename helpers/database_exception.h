#pragma once
#include <TGlobal>


class T_HELPER_EXPORT DatabaseException : public std::runtime_error {
public:
    DatabaseException(const QString msg): runtime_error(msg.toStdString()) {};
    virtual ~DatabaseException() throw() {};
};
