#ifndef CHARMMODIFIERWINDOW_H
#define CHARMMODIFIERWINDOW_H

#include "ReaderWriterClasses/SaveDataManager.hpp"
#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QComboBox>
#include <QCloseEvent>

class CharmModifierWindow : public QDialog
{
    Q_OBJECT
public:
    CharmModifierWindow(SaveDataManager *sdm,
                        int id_emplacement,
                        QStringList charmStringList,
                        QStringList skillStringList,
                        QStringList jwlStringList,
                        QWidget *parent = nullptr);

private:

    SaveDataManager *m_sdm;
    QStringList m_charmStringList;
    QStringList m_skillStringList;
    QStringList m_jwlStringList;
    int m_id_emplacement;

    QVBoxLayout  *m_vLayout;

    QComboBox *m_typeOfCharm;
    QSpinBox *m_nbrSlot;
    QLineEdit *m_firstSkill;
    QSpinBox *m_firstSkillPoints;
    QLineEdit *m_secondSkill;
    QSpinBox *m_secondSkillPoints;
    QLineEdit *m_firstjwl;
    QLineEdit *m_secondjwl;
    QLineEdit *m_thirdjwl;

    void saveData();
    uint8_t* checkSkill(QLineEdit *skill, QSpinBox *points);
    uint16_t checkJWL(QLineEdit *jwl);
    void closeEvent(QCloseEvent *event);

};

#endif // CHARMMODIFIERWINDOW_H
