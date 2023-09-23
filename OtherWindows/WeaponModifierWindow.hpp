#ifndef WEAPONMODIFIERWINDOW_HPP
#define WEAPONMODIFIERWINDOW_HPP

#include "ReaderWriterClasses/SaveDataManager.hpp"
#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QCloseEvent>

class WeaponModifierWindow : public QDialog
{
    Q_OBJECT
public:
    WeaponModifierWindow(SaveDataManager *sdm,
                         uint8_t typeWeapon,
                         int id_emplacement,
                         QStringList weaponNameStringList,
                         QStringList jwlStringList,
                         QWidget *parent = nullptr);

private:
    SaveDataManager *m_sdm;
    QStringList m_weaponNameStringList;
    QStringList m_jwlStringList;
    int m_id_emplacement;
    uint8_t m_typeWeapon;

    QVBoxLayout  *m_vLayout;

    QLineEdit *m_nameWeapon;
    QLineEdit *m_firstjwl;
    QLineEdit *m_secondjwl;
    QLineEdit *m_thirdjwl;

    void saveData();
    uint16_t checkJWL(QLineEdit *jwl);
    void closeEvent(QCloseEvent *event);
};

#endif // WEAPONMODIFIERWINDOW_HPP
