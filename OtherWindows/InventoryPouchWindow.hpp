#ifndef INVENTORYPOUCHWINDOW_H
#define INVENTORYPOUCHWINDOW_H

#include "../ReaderWriterClasses/SaveDataManager.hpp"
#include "../ReaderWriterClasses/Database.hpp"
#include <QObject>
#include <QMainWindow>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>

class InventoryPouchWindow : public QMainWindow
{
    Q_OBJECT

public:
    InventoryPouchWindow(SaveDataManager *sdm, QWidget *parent, SaveDataManager::ItemMode mode);
    ~InventoryPouchWindow();

public Q_SLOTS:
    void changeItem(int id_emplacement);

private:
    SaveDataManager *m_sdm;
    SaveDataManager::ItemMode m_mode;
    Database *m_db;

    QWidget *m_mainLayout;
    QVBoxLayout *m_vLayout;
    QTabWidget *m_panel;
    QPushButton *m_slotItem[4][8];
    int m_maxPanel;
};

#endif // INVENTORYPOUCHWINDOW_H
