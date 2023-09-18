#ifndef ITEMBOXWINDOW_HPP
#define ITEMBOXWINDOW_HPP

#include "../ReaderWriterClasses/SaveDataManager.hpp"
#include "../ReaderWriterClasses/Database.hpp"

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTabWidget>
#include <QGridLayout>
#include <QPushButton>
#include <QStringList>


class ItemBoxWindow : public QMainWindow
{
    Q_OBJECT

public:
    ItemBoxWindow(SaveDataManager *sdm, QStringList itemStringList, QWidget *parent = nullptr);
    ~ItemBoxWindow();

private Q_SLOTS:
    void changeItem(int id_emplacement);

private:
    SaveDataManager *m_sdm;
    QStringList m_itemStringList;

    QWidget *m_mainLayout;
    QTabWidget *m_panel;
    QGridLayout *m_mainGridLayout;
    QPushButton *m_item_emplacement[10][100];
};

#endif // ITEMBOXWINDOW_HPP
