#ifndef ARMORMODIFIERWINDOW_HPP
#define ARMORMODIFIERWINDOW_HPP

#include "ReaderWriterClasses/SaveDataManager.hpp"
#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QCloseEvent>

class ArmorModifierWindow : public QDialog
{
    Q_OBJECT
public:
    ArmorModifierWindow(SaveDataManager *sdm,
                        uint8_t typeArmor,
                        int id_emplacement,
                        QStringList armorNameStringList,
                        QStringList jwlStringList,
                        QWidget *parent = nullptr);

private:
    SaveDataManager *m_sdm;
    QStringList m_armorNameStringList;
    QStringList m_jwlStringList;
    int m_id_emplacement;
    uint8_t m_typeArmor;

    QVBoxLayout  *m_vLayout;

    QLineEdit *m_nameArmor;
    QSpinBox *m_amelioration;
    QLineEdit *m_firstjwl;
    QLineEdit *m_secondjwl;
    QLineEdit *m_thirdjwl;

    void saveData();
    uint16_t checkJWL(QLineEdit *jwl);
    void closeEvent(QCloseEvent *event);
};

#endif // ARMORMODIFIERWINDOW_HPP
