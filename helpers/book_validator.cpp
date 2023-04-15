#include "book_validator.h"


BookValidator::BookValidator() : TFormValidator()
{
    setRule("title", Tf::Required, "title is required");
    setRule("title", Tf::MaxLength, 30, "title must be less than 30 characters long");
    setRule("isbn", Tf::Required, "isbn is required");
    setRule("isbn", Tf::MaxLength, 100, "isbn must be less than 100 characters long");
}
