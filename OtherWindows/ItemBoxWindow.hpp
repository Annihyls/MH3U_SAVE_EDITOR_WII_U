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


class ItemBoxWindow : public QMainWindow
{
    Q_OBJECT

public:
    ItemBoxWindow(SaveDataManager *sdm, QWidget *parent);
    ~ItemBoxWindow();

public Q_SLOTS:
    void changeItem(int id_emplacement);

private:
    SaveDataManager *m_sdm;
    Database *m_db;

    QWidget *m_mainLayout;
    QTabWidget *m_panel;
    QGridLayout *m_mainGridLayout;
    QPushButton *m_item_emplacement[10][100];
};

#endif // ITEMBOXWINDOW_HPP
