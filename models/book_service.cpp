#include <TreeFrogModel>
#include "objects/book.h"
#include "book_service.h"
#include "book_validator.h"
#include "book_validator.h"
#include "database_exception.h"
#include "not_found_exception.h"
#include "validation_exception.h"
#include "nothing_updated_exception.h"


/**
 * Get the list of books.
 * A list of book entity is mapped to a list of book dto.
 *
 * @return QList a list of book dto
 */
QList<Book> BookService::list()
{
    return Book::getAll();
}

/**
 * Get a single book.
 *
 * @param id an id of a book
 * @throw ValidationException when the input id is negative
 * @throw NotFoundException when the book does not exist
 * @return QVariantMap a book dto
 */
Book BookService::detail(const int id)
{
    // make sure the id is good
    if (id <= 0) {
        throw ValidationException(
            QString("input id must be a positive number").arg(id));
    }

    // find the book
    Book book = Book::get(id);
    if (book.isNull()) {
        throw NotFoundException(QString("book id = %1 is not found").arg(id));
    }

    return book;
}

/**
 * Create a new book.
 *
 * @param createBookDto a create book dto
 * @throw ValidationException when the create-book dto is not valid
 * @return QVariantMap a book dto representing a book that is about to be created
 */
Book BookService::create(const QVariantMap &createBookDto)
{
    // validate the given dto
    BookValidator validator;
    if (!validator.validate(createBookDto)) {
        QStringList errors = validator.errorMessages();
        throw ValidationException(errors.at(0));
    }

    // create a new book
    return Book::create(createBookDto);
}


/**
 * Update an existing book.
 *
 * @param id an id of a book to update
 * @param updateBookDto an update-book dto
 * @throw ValidationException when the input id is negative
 * @throw NothingUpdatedExeption when nothing is updated
 * @throw ValidationException when the update-book dto is not valid
 * @throw DatabaseException when can not save the book
 * @return QVariantMap a book dto representing a book that is just updated
 */
Book BookService::update(const int id, const QVariantMap &updateBookDto)
{
    // make sure the given id is good
    if (id <= 0) {
        throw new ValidationException(
            QString("input id must be a postive number").arg(id));
    }

    auto title = updateBookDto.value("title");
    auto isbn = updateBookDto.value("isbn");

    // validate the dto
    BookValidator validator;
    if (!validator.validate(updateBookDto)) {
        QStringList errors = validator.errorMessages();
        throw ValidationException(errors.at(0));
    }

    // find the book
    auto book = Book::get(id);
    if (book.isNull()) {
        throw NotFoundException(QString("book id = %1 is not found").arg(id));
    }

    bool needToUpdate = false;

    // new title?
    if (book.title() != title.toString()) {
        book.setTitle(title.toString());
        needToUpdate = true;
    }

    // new isbn?
    if (book.isbn() != isbn.toString()) {
        book.setIsbn(isbn.toString());
        needToUpdate = true;
    }

    // need to update?
    if (!needToUpdate) {
        throw NothingUpdatedException();
    }

    // it is time to save
    if (!book.save()) {
        throw DatabaseException(
            QString("can not update book id = %1").arg(id));
    }

    return book;
}

/**
 * Remove a book.
 *
 * @param id an id of a book to delete
 * @throw ValidationException when the input id is negative
 * @throw DatabaseException when the book can not be removed
 * @return QVariantMap a book dto
 */
Book BookService::remove(const int id)
{
    // make sure the id is good
    if (id <= 0) {
        throw new ValidationException(
            QString("input id must be a positive number").arg(id));
    }

    // find the book
    auto book = Book::get(id);
    if (book.isNull()) {
        throw NotFoundException(QString("book id = %1 is not found").arg(id));
    }

    // remove the book
    if (!book.remove()) {
        throw DatabaseException(
            QString("book id = %1 can not be deleted").arg(id));
    }

    return book;
}
