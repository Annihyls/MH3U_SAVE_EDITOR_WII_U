#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include "OtherWindows/CharacterWindow.hpp"
#include "OtherWindows/ItemBoxWindow.hpp"
#include "OtherWindows/InventoryPouchWindow.hpp"
#include "OtherWindows/EquipmentBoxWindow.hpp"
#include "ReaderWriterClasses/SaveDataManager.hpp"
#include "OtherWindows/Option.hpp"

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
    void optionWindow();
    void eqBoxWindow();

private:
    SaveDataManager *m_sdm = nullptr;
    Database *m_db = nullptr;

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
    QPushButton *m_option;
    QPushButton *m_eq_box;

    CharacterWindow *m_cw = nullptr;
    ItemBoxWindow *m_ibw = nullptr;
    InventoryPouchWindow *m_iw = nullptr;
    InventoryPouchWindow *m_pw = nullptr;
    Option *m_ow;
    EquipmentBoxWindow *m_ebw = nullptr;

    Option::Lang m_lang = Option::Lang::EN;

    void loadWindowsAndDatabases();

};
#endif // MAINWINDOW_HPP
