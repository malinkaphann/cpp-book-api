#include "api_book_controller.h"
#include "book_service.h"
#include "status.h"
#include "not_found_exception.h"
#include "validation_exception.h"
#include "database_exception.h"
#include "nothing_updated_exception.h"

static BookService service;

void ApiBookController::index()
{
    // get the list of books
    QList<Book> books = service.list();

    // map from a list of models to a json array
    QJsonArray array;
    QListIterator<Book> i(books);
    while (i.hasNext()) {
        Book book = i.next();
        QJsonObject json;
        json.insert("title", book.title());
        json.insert("isbn", book.isbn());
        array.append(json);
    }

    // build the response
    QVariantMap response = API_DATA_RESPONSE(
        SUCCESS, "book list is fetched successfully", array);

    // send
    renderJson(response);
}

void ApiBookController::detail(const QString &id)
{
    QVariantMap response;

    // get the book
    Book book;
    try {
        book = service.detail(id.toInt());
    } catch (ValidationException &e) {
        setStatusCode(Tf::BadRequest);
        response = API_RESPONSE(ERROR_VALIDATION, e.what());
        return;
    } catch (NotFoundException &e) {
        setStatusCode(Tf::NotFound);
        response = API_RESPONSE(ERROR_NOT_FOUND, e.what());
        renderJson(response);
        return;
    }

    // build the book dto
    QJsonObject json;
    json.insert("title", book.title());
    json.insert("isbn", book.isbn());

    // build the rsponse
    response = API_DATA_RESPONSE(SUCCESS,
       QString("book id = %1 is fetched successfully").arg(id),
                                             json);

    renderJson(response);
}

void ApiBookController::create()
{
    QVariantMap response;

    // request create dto
    QVariantMap bookMap = request().jsonData().toVariant().toMap();

    Book book;
    try {
        book = service.create(bookMap);
    } catch(ValidationException &e) {
        setStatusCode(Tf::BadRequest);
        response = API_RESPONSE(ERROR_VALIDATION, e.what());
        renderJson(response);
        return;
    }

    // build the response
    QString msg =  QString("book title = %1 is created successfully").arg(book.title());
    response = API_RESPONSE(SUCCESS, msg);
    renderJson(response);
}

void ApiBookController::update(const QString &id)
{
    QVariantMap response;

    // request update dto
    QVariantMap bookMap = request().jsonData().toVariant().toMap();

    Book book;
    try {
        book = service.update(id.toInt(), bookMap);
    } catch (ValidationException &e) {
        setStatusCode(Tf::BadRequest);
        response = API_RESPONSE(ERROR_VALIDATION, e.what());
        renderJson(response);
        return;
    } catch (NotFoundException &e) {
        setStatusCode(Tf::NotFound);
        response = API_RESPONSE(ERROR_NOT_FOUND, e.what());
        renderJson(response);
        return;
    } catch (DatabaseException &e) {
        setStatusCode(Tf::InternalServerError);
        response = API_RESPONSE(ERROR_DATABASE, e.what());
        renderJson(response);
        return;
    } catch (NothingUpdatedException &e) {
        setStatusCode(Tf::OK);
        response = API_RESPONSE(ERROR_NOTHING_UPDATED, e.what());
        renderJson(response);
        return;
    }

    // build the response
    QString msg =  QString("book id = %1 is updated successfully").arg(id);
    response = API_RESPONSE(SUCCESS, msg);
    renderJson(response);
}

void ApiBookController::remove(const QString &id)
{
    QVariantMap response;

    // get the book
    Book book;
    try {
        book = service.remove(id.toInt());
    } catch (const ValidationException &e) {
        setStatusCode(Tf::BadRequest);
        response = API_RESPONSE(ERROR_VALIDATION, e.what());
        renderJson(response);
        return;
    } catch (const NotFoundException &e) {
        setStatusCode(Tf::NotFound);
        response = API_RESPONSE(ERROR_NOT_FOUND, e.what());
        renderJson(response);
        return;
    } catch (const DatabaseException &e) {
        setStatusCode(Tf::InternalServerError);
        response = API_RESPONSE(ERROR_DATABASE, e.what());
        renderJson(response);
        return;
    }


    // build the rsponse
    response = API_RESPONSE(SUCCESS,
        QString("book id = %1 is deleted successfully").arg(id));

    renderJson(response);
}

// Don't remove below this line
T_DEFINE_CONTROLLER(ApiBookController)
