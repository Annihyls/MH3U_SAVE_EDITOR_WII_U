#include "EqModifierWindow.hpp"
#include "OtherWindows/ArmorModifierWindow.hpp"
#include "OtherWindows/CharmModifierWindow.hpp"
#include "OtherWindows/WeaponModifierWindow.hpp"
#include <QLabel>
#include <QFormLayout>
#include <QLayoutItem>
#include <QLineEdit>
#include <QSpinBox>
#include <QCompleter>

EqModifierWindow::EqModifierWindow(SaveDataManager *sdm, Database db, int id_emplacement, QWidget *parent):
    QDialog(parent), m_sdm(sdm), m_db(db), m_id_emplacement(id_emplacement)
{
    m_mainVLayout = new QVBoxLayout(this);
    m_upVLayout = new QVBoxLayout();
    m_midVLayout = new QVBoxLayout();

    uint8_t eq = m_sdm->getTypeEquipment(m_id_emplacement);
    //si pas d'équipement
    if(eq == 0)
    {
        QLabel *no_data = new QLabel(this);
        no_data->setText("No equipment");
        m_upVLayout->addWidget(no_data);
    }
    else if(eq == 6)
    {
        charmDisplay();
    }
    else if(eq == 1 || eq == 2 || eq == 3 || eq == 4 || eq == 5)
    {
        armorDisplay(eq);
    }
    else
    {
        weaponDisplay(eq);
    }

    m_weaponTypeComBox = new QComboBox(this);
    for(QString &str : db.getDatabase(21))
    {
        m_weaponTypeComBox->addItem(str);
    }

    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow(tr("&New Equipment Type : "), m_weaponTypeComBox);
    connect(m_weaponTypeComBox, SIGNAL(currentIndexChanged(int)), this, SLOT(changeEquipmentType(int)));

    m_midVLayout->addLayout(formLayout);

    m_mainVLayout->addLayout(m_upVLayout);
    m_mainVLayout->addLayout(m_midVLayout);
    setLayout(m_mainVLayout);
    setMinimumWidth(240);
    setWindowTitle("Modifier + Weapon Type Editing");

}

EqModifierWindow::~EqModifierWindow()
{

}

void EqModifierWindow::charmDisplay()
{
    QFormLayout *tabFormLayout[9];
    QLabel *tabLabel[9];
    for(int i = 0; i<9; i++)
    {
        tabFormLayout[i] = new QFormLayout();
        tabLabel[i] = new QLabel(this);
        tabLabel[i]->setStyleSheet("QLabel { color : red; }");
    }

    tabLabel[0]->setText(m_db.getElement(ID_DB_CHARM, m_sdm->getIdEquipment(m_id_emplacement)));
    tabLabel[1]->setText(QString("%1").arg(m_sdm->getSlotOrUpgradeNumber(m_id_emplacement)));
    tabLabel[2]->setText(m_db.getElement(ID_DB_SKILL, m_sdm->getFirstSkillCharmID(m_id_emplacement)));

    uint8_t firstSkillPoint = m_sdm->getFirstSkillCharmPoint(m_id_emplacement);
    if(firstSkillPoint == 0)
    {
        tabLabel[3]->setText(QString(""));
    }
    else
    {
        tabLabel[3]->setText(QString("%1").arg(firstSkillPoint));
    }

    tabLabel[4]->setText(m_db.getElement(ID_DB_SKILL, m_sdm->getSecondSkillCharmID(m_id_emplacement)));

    uint8_t secondSkillPoint = m_sdm->getSecondSkillCharmPoint(m_id_emplacement);
    if(secondSkillPoint == 0)
    {
        tabLabel[5]->setText(QString(""));
    }
    else
    {
        tabLabel[5]->setText(QString("%1").arg(secondSkillPoint));
    }
    tabLabel[6]->setText(m_db.getElement(ID_DB_JWL, m_sdm->getFirstDeco(m_id_emplacement)));
    tabLabel[7]->setText(m_db.getElement(ID_DB_JWL, m_sdm->getSecondDeco(m_id_emplacement)));
    tabLabel[8]->setText(m_db.getElement(ID_DB_JWL, m_sdm->getThirdDeco(m_id_emplacement)));


    tabFormLayout[0]->addRow(tr("&Type of talisman : "), tabLabel[0]);
    tabFormLayout[1]->addRow(tr("&Slots : "), tabLabel[1]);
    tabFormLayout[2]->addRow(tr("&1st skill name : "), tabLabel[2]);
    tabFormLayout[3]->addRow(tr("&1st skill points : "), tabLabel[3]);
    tabFormLayout[4]->addRow(tr("&2nd skill name : "), tabLabel[4]);
    tabFormLayout[5]->addRow(tr("&2nd skill points : "), tabLabel[5]);
    tabFormLayout[6]->addRow(tr("&1st deco : "), tabLabel[6]);
    tabFormLayout[7]->addRow(tr("&2nd deco : "), tabLabel[7]);
    tabFormLayout[8]->addRow(tr("&3rd deco : "), tabLabel[8]);

    for(int i = 0; i<9; i++)
    {
        m_upVLayout->addLayout(tabFormLayout[i]);
    }

}

void EqModifierWindow::armorDisplay(uint8_t type)
{
    QFormLayout *tabFormLayout[5];
    QLabel *tabLabel[5];
    for(int i = 0; i<5; i++)
    {
        tabFormLayout[i] = new QFormLayout();
        tabLabel[i] = new QLabel(this);
        tabLabel[i]->setStyleSheet("QLabel { color : red; }");
    }

    tabLabel[0]->setText(m_db.getElement(type, m_sdm->getIdEquipment(m_id_emplacement)));
    tabLabel[1]->setText(QString("%1").arg(m_sdm->getSlotOrUpgradeNumber(m_id_emplacement)));
    tabLabel[2]->setText(m_db.getElement(ID_DB_JWL, m_sdm->getFirstDeco(m_id_emplacement)));
    tabLabel[3]->setText(m_db.getElement(ID_DB_JWL, m_sdm->getSecondDeco(m_id_emplacement)));
    tabLabel[4]->setText(m_db.getElement(ID_DB_JWL, m_sdm->getThirdDeco(m_id_emplacement)));


    tabFormLayout[0]->addRow(tr("&Name of armor : "), tabLabel[0]);
    tabFormLayout[1]->addRow(tr("&Amelioration : "), tabLabel[1]);
    tabFormLayout[2]->addRow(tr("&1st deco : "), tabLabel[2]);
    tabFormLayout[3]->addRow(tr("&2nd deco : "), tabLabel[3]);
    tabFormLayout[4]->addRow(tr("&3rd deco : "), tabLabel[4]);

    for(int i = 0; i<5; i++)
    {
        m_upVLayout->addLayout(tabFormLayout[i]);
    }
}

void EqModifierWindow::weaponDisplay(uint8_t type)
{
    QFormLayout *tabFormLayout[4];
    QLabel *tabLabel[4];
    for(int i = 0; i<4; i++)
    {
        tabFormLayout[i] = new QFormLayout();
        tabLabel[i] = new QLabel(this);
        tabLabel[i]->setStyleSheet("QLabel { color : red; }");
    }

    tabLabel[0]->setText(m_db.getElement(type, m_sdm->getIdEquipment(m_id_emplacement)));
    tabLabel[1]->setText(m_db.getElement(ID_DB_JWL, m_sdm->getFirstDeco(m_id_emplacement)));
    tabLabel[2]->setText(m_db.getElement(ID_DB_JWL, m_sdm->getSecondDeco(m_id_emplacement)));
    tabLabel[3]->setText(m_db.getElement(ID_DB_JWL, m_sdm->getThirdDeco(m_id_emplacement)));


    tabFormLayout[0]->addRow(tr("&Name of weapon : "), tabLabel[0]);
    tabFormLayout[1]->addRow(tr("&1st deco : "), tabLabel[1]);
    tabFormLayout[2]->addRow(tr("&2nd deco : "), tabLabel[2]);
    tabFormLayout[3]->addRow(tr("&3rd deco : "), tabLabel[3]);

    for(int i = 0; i<4; i++)
    {
        m_upVLayout->addLayout(tabFormLayout[i]);
    }
}

void EqModifierWindow::changeEquipmentType(int index)
{
    if(index == 0 || index == 12)
    {

    }
    else if(index == 6)
    {
        charmModifierDisplay();
    }
    else if(index == 1 || index == 2 || index == 3 || index == 4 || index == 5)
    {
        armorModifierDisplay(index);
    }
    else
    {
        weaponModifierDisplay(index);
    }
    this->close();
}

void EqModifierWindow::charmModifierDisplay()
{
    CharmModifierWindow *cmw =
        new CharmModifierWindow(m_sdm, m_id_emplacement, m_db.getDatabase(ID_DB_CHARM), m_db.getDatabase(ID_DB_SKILL), m_db.getDatabase(ID_DB_JWL), this);
    cmw->exec();
    delete cmw;
}

void EqModifierWindow::armorModifierDisplay(uint8_t type)
{
    ArmorModifierWindow *amw =
        new ArmorModifierWindow(m_sdm, type, m_id_emplacement, m_db.getDatabase(type), m_db.getDatabase(ID_DB_JWL), this);
    amw->exec();
    delete amw;
}
void EqModifierWindow::weaponModifierDisplay(uint8_t type)
{
    WeaponModifierWindow *wmw =
        new WeaponModifierWindow(m_sdm, type, m_id_emplacement, m_db.getDatabase(type), m_db.getDatabase(ID_DB_JWL), this);
    wmw->exec();
    delete wmw;
}

    /*
     * pour effacer les widgets présent dans un
     * layout (parce que quand un BoxLayout est
     * détruit, ses enfants ne le sont pas)
     */
/*
void EqModifierWindow::clearLayout(QLayout *layout) {
    if (layout == NULL)
        return;
    while(layout->count()) {
        QLayoutItem* pItem = layout->takeAt(0);
        if (QWidget* pWidget = pItem->widget())
        {
            pWidget->deleteLater();
        }
        else if (QLayout* pChildLayout = pItem->layout())
        {
            clearLayout(pChildLayout);
            pChildLayout->deleteLater();
        }
    }
}
*/
