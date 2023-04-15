#pragma once
#include <TGlobal>

#define SUCCESS                     000
#define ERROR                       100
#define ERROR_VALIDATION            101
#define ERROR_NOT_FOUND             102
#define ERROR_DATABASE              103
#define ERROR_NOTHING_UPDATED       104

#define API_RESPONSE(X,Y) QVariantMap{{"status",X},{"message",Y}};
#define API_DATA_RESPONSE(X,Y,Z) QVariantMap{{"status",X},{"message",Y},{"data",Z}};
