#ifndef EQMODIFIERWINDOW_H
#define EQMODIFIERWINDOW_H

#include "../ReaderWriterClasses/SaveDataManager.hpp"
#include "../ReaderWriterClasses/Database.hpp"

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <QList>
#include <QLabel>


class EqModifierWindow : public QDialog
{
    Q_OBJECT
public:
    EqModifierWindow(SaveDataManager *sdm, Database db, int id_emplacement, QWidget *parent = nullptr);
    ~EqModifierWindow();

private Q_SLOTS:
    void changeEquipmentType(int index);

private:
    SaveDataManager *m_sdm;
    Database m_db;

    QVBoxLayout *m_mainVLayout;
    QVBoxLayout *m_upVLayout;
    QVBoxLayout *m_midVLayout;
    QVBoxLayout *m_downVLayout = nullptr;

    QComboBox *m_weaponTypeComBox;
    int m_id_emplacement;


    void charmDisplay();
    void armorDisplay(uint8_t type);
    void weaponDisplay(uint8_t type);

    void charmModifierDisplay();
    void armorModifierDisplay(uint8_t type);
    void weaponModifierDisplay(uint8_t type);
};

#endif // EQMODIFIERWINDOW_H
