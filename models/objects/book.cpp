#include <TreeFrogModel>
#include "book.h"
#include "sqlobjects/bookobject.h"


Book::Book() :
    TAbstractModel(),
    d(new BookObject())
{
    // set the initial parameters
}

Book::Book(const Book &other) :
    TAbstractModel(),
    d(other.d)
{ }

Book::Book(const BookObject &object) :
    TAbstractModel(),
    d(new BookObject(object))
{ }

Book::~Book()
{
    // If the reference count becomes 0,
    // the shared data object 'BookObject' is deleted.
}

int Book::id() const
{
    return d->id;
}

QString Book::title() const
{
    return d->title;
}

void Book::setTitle(const QString &title)
{
    d->title = title;
}

QString Book::isbn() const
{
    return d->isbn;
}

void Book::setIsbn(const QString &isbn)
{
    d->isbn = isbn;
}


Book &Book::operator=(const Book &other)
{
    d = other.d;  // increments the reference count of the data
    return *this;
}

Book Book::create(const QString &title, const QString &isbn)
{
    BookObject obj;
    obj.title = title;
    obj.isbn = isbn;
    if (!obj.create()) {
        return Book();
    }
    return Book(obj);
}

Book Book::create(const QVariantMap &values)
{
    Book model;
    model.setProperties(values);
    if (!model.d->create()) {
        model.d->clear();
    }
    return model;
}

Book Book::get(int id)
{
    TSqlORMapper<BookObject> mapper;
    return Book(mapper.findByPrimaryKey(id));
}

int Book::count()
{
    TSqlORMapper<BookObject> mapper;
    return mapper.findCount();
}

QList<Book> Book::getAll()
{
    return tfGetModelListByCriteria<Book, BookObject>(TCriteria());
}

QJsonArray Book::getAllJson(const QStringList &properties)
{
    return tfConvertToJsonArray(getAll(), properties);
}

TModelObject *Book::modelData()
{
    return d.data();
}

const TModelObject *Book::modelData() const
{
    return d.data();
}

QDataStream &operator<<(QDataStream &ds, const Book &model)
{
    auto varmap = model.toVariantMap();
    ds << varmap;
    return ds;
}

QDataStream &operator>>(QDataStream &ds, Book &model)
{
    QVariantMap varmap;
    ds >> varmap;
    model.setProperties(varmap);
    return ds;
}
