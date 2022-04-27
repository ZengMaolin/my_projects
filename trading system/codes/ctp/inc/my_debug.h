#pragma once

#include <QObject>

class my_debug : public QObject
{
    Q_OBJECT

public:
    my_debug(QObject *parent);
    ~my_debug();
};
