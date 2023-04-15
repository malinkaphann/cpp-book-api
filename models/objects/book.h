#pragma once
#include <QStringList>
#include <QDateTime>
#include <QVariant>
#include <QSharedDataPointer>
#include <TGlobal>
#include <TAbstractModel>

class TModelObject;
class BookObject;
class QJsonArray;


class T_MODEL_EXPORT Book : public TAbstractModel {
public:
    Book();
    Book(const Book &other);
    Book(const BookObject &object);
    ~Book();

    int id() const;
    QString title() const;
    void setTitle(const QString &title);
    QString isbn() const;
    void setIsbn(const QString &isbn);
    Book &operator=(const Book &other);

    bool create() override { return TAbstractModel::create(); }
    bool update() override { return TAbstractModel::update(); }
    bool save()   override { return TAbstractModel::save(); }
    bool remove() override { return TAbstractModel::remove(); }

    static Book create(const QString &title, const QString &isbn);
    static Book create(const QVariantMap &values);
    static Book get(int id);
    static int count();
    static QList<Book> getAll();
    static QJsonArray getAllJson(const QStringList &properties = QStringList());

private:
    QSharedDataPointer<BookObject> d;

    TModelObject *modelData() override;
    const TModelObject *modelData() const override;
    friend T_MODEL_EXPORT QDataStream &operator<<(QDataStream &ds, const Book &model);
    friend T_MODEL_EXPORT QDataStream &operator>>(QDataStream &ds, Book &model);
};

Q_DECLARE_METATYPE(Book)
Q_DECLARE_METATYPE(QList<Book>)

