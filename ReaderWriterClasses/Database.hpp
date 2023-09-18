#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <Qstring>
#include <QList>
#include <QStringList>

class Database
{
public:
    Database(QString langue);
    ~Database();
    QString getElement(int id_database, int element);
    QStringList getDatabase(int id_database);

private:
    QList<QStringList> m_listOfQStringList;
    QStringList lireDonnees(std::string file_path);
};

#endif // DATABASE_HPP
