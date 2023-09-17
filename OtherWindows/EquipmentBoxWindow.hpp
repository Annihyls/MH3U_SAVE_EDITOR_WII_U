#ifndef EQUIPMENTBOXWINDOW_H
#define EQUIPMENTBOXWINDOW_H

#include "../ReaderWriterClasses/SaveDataManager.hpp"
#include "../ReaderWriterClasses/Database.hpp"

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QTabWidget>
#include <QGridLayout>
#include <QPushButton>

class EquipmentBoxWindow : public QMainWindow
{
    Q_OBJECT
public:
    EquipmentBoxWindow(SaveDataManager *sdm, Database *db, QWidget *parent = nullptr);
    ~EquipmentBoxWindow();

private Q_SLOTS:
    void changeEq(int id_emplacement);

private:
    SaveDataManager *m_sdm;
    Database *m_db;

    QWidget *m_mainLayout;
    QTabWidget *m_panel;
    QGridLayout *m_mainGridLayout;
    QPushButton *m_eq_emplacement[10][100];
};

#endif // EQUIPMENTBOXWINDOW_H
