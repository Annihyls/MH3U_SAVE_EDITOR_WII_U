#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "OtherWindows/CharacterWindow.hpp"
#include "OtherWindows/ItemBoxWindow.hpp"
#include "OtherWindows/InventoryPouchWindow.hpp"
#include "ReaderWriterClasses/SaveDataManager.hpp"

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QList>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private Q_SLOTS:
    void lireDonnees();
    void ecrireDonnees();
    void characterWindow();
    void inventoryWindow();
    void itemBoxWindow();
    void pouchWindow();

private:
    SaveDataManager *m_sdm;

    QVBoxLayout *m_vLayoutLeft;
    QVBoxLayout *m_vLayoutRight;

    QHBoxLayout *m_hLayout;

    QWidget *m_mainWidget;

    QPushButton *m_load_file;
    QPushButton *m_save_file;
    QPushButton *m_character;
    QPushButton *m_item_box;
    QPushButton *m_inventory;
    QPushButton *m_pouch;

    CharacterWindow *m_cw;
    ItemBoxWindow *m_ibw;
    InventoryPouchWindow *m_iw;
    InventoryPouchWindow *m_pw;

};
#endif // MAINWINDOW_HPP
