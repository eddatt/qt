#pragma once
#include <QString>
class Item
{
public:
    Item(const QString &name);
    ~Item();

    inline QString name()const {
        return m_name;
    }

private:
    QString m_name;
};

