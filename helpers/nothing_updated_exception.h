#pragma once
#include <TGlobal>


class T_HELPER_EXPORT NothingUpdatedException : public std::runtime_error {
public:
    NothingUpdatedException(): runtime_error("nothing is updated") {};
    virtual ~NothingUpdatedException() throw() {};
};
