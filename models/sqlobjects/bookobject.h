#pragma once
#include <TSqlObject>
#include <QSharedData>


class T_MODEL_EXPORT BookObject : public TSqlObject, public QSharedData {
public:
    int id {0};
    QString title;
    QString isbn;

    enum PropertyIndex {
        Id = 0,
        Title,
        Isbn,
    };

    int primaryKeyIndex() const override { return Id; }
    int autoValueIndex() const override { return Id; }
    QString tableName() const override { return QStringLiteral("book"); }

private:    /*** Don't modify below this line ***/
    Q_OBJECT
    Q_PROPERTY(int id READ getid WRITE setid)
    T_DEFINE_PROPERTY(int, id)
    Q_PROPERTY(QString title READ gettitle WRITE settitle)
    T_DEFINE_PROPERTY(QString, title)
    Q_PROPERTY(QString isbn READ getisbn WRITE setisbn)
    T_DEFINE_PROPERTY(QString, isbn)
};

