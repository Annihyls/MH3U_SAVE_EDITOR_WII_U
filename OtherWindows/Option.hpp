#ifndef OPTION_HPP
#define OPTION_HPP

#include <QDialog>
#include <QWidget>
#include <QObject>
#include <QVBoxLayout>
#include <QComboBox>
#include <QCloseEvent>

class Option : public QDialog
{
    Q_OBJECT
public:
    enum Lang{EN, FR};
    Option(Lang l, QWidget *parent);
    ~Option();

    Lang lang;

private:
    QComboBox *m_langCB;
    QVBoxLayout *m_mainLayout;

    void closeEvent(QCloseEvent *event);
    void saveLanguage();

};

#endif // OPTION_HPP
