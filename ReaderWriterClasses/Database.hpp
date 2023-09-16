#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <string>
#include <Qstring>

class Database
{
public:
    Database(std::string file_path);
    ~Database();
    QString getElement(int i);
    int getSize();

private:
    QString *m_strTab;
    int m_length;
};

#endif // DATABASE_HPP
