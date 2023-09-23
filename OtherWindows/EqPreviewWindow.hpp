#ifndef EQPREVIEWWINDOW_HPP
#define EQPREVIEWWINDOW_HPP

#include "../ReaderWriterClasses/SaveDataManager.hpp"
#include "../ReaderWriterClasses/Database.hpp"

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>
#include <QList>
#include <QLabel>


class EqPreviewWindow : public QDialog
{
    Q_OBJECT
public:
    EqPreviewWindow(SaveDataManager *sdm, Database db, int id_emplacement, QWidget *parent = nullptr);
    ~EqPreviewWindow();

private:
    SaveDataManager *m_sdm;
    Database m_db;

    QVBoxLayout *m_mainVLayout;
    QVBoxLayout *m_upVLayout;
    QHBoxLayout *m_downHLayout;

    QComboBox *m_weaponTypeComBox;
    int m_id_emplacement;


    void charmDisplay();
    void armorDisplay(uint8_t type);
    void weaponDisplay(uint8_t type);
};

#endif // EQPREVIEWWINDOW_HPP
