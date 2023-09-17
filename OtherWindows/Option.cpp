#include "Option.hpp"

Option::Option(Lang l, QWidget *parent) : QDialog(parent), lang(l)
{
    m_mainLayout = new QVBoxLayout(this);
    m_langCB = new QComboBox(this);
    m_langCB->addItem("English");
    m_langCB->addItem("Français");
    m_langCB->setCurrentIndex(l);

    m_mainLayout->addWidget(m_langCB);
    setLayout(m_mainLayout);
    setModal(true);
    setMinimumWidth(180);
    setWindowTitle(QString("Change Language"));
}

Option::~Option()
{}

void Option::closeEvent(QCloseEvent *event)
{
    saveLanguage();
    event->accept();
}

void Option::saveLanguage()
{
    switch(m_langCB->currentIndex())
    {
    case 0:
        lang = Lang::EN;
        break;
    default:
        lang = Lang::FR;
        break;
    }
}
