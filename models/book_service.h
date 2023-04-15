#pragma once
#include <TGlobal>
#include "objects/book.h"

class THttpRequest;

class T_MODEL_EXPORT BookService {
public:
    QList<Book> list();
    Book detail(const int id);
    Book create(const QVariantMap &createBookDto);
    Book update(const int id, const QVariantMap &updateBookDto);
    Book remove(const int id);
};
