#pragma once
#include "applicationcontroller.h"


class T_CONTROLLER_EXPORT ApiBookController : public ApplicationController {
    Q_OBJECT
public slots:
    void index();
    void detail(const QString &id);
    void create();
    void update(const QString &id);
    void remove(const QString &id);
};
