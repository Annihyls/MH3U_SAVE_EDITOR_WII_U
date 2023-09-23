#include "EqPreviewWindow.hpp"
#include <QLabel>
#include <QFormLayout>

EqPreviewWindow::EqPreviewWindow(SaveDataManager *sdm, Database db, int id_emplacement, QWidget *parent):
    QDialog(parent), m_sdm(sdm), m_db(db), m_id_emplacement(id_emplacement)
{
    m_mainVLayout = new QVBoxLayout(this);
    m_upVLayout = new QVBoxLayout();
    m_downHLayout = new QHBoxLayout();

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

    m_downHLayout->addWidget(new QLabel("New Type : ", this));
    m_downHLayout->addWidget(m_weaponTypeComBox);
    m_mainVLayout->addLayout(m_upVLayout);
    m_mainVLayout->addLayout(m_downHLayout);
    setLayout(m_mainVLayout);
    setMinimumWidth(240);
    setWindowTitle("Preview + Weapon Type Editing");

}

EqPreviewWindow::~EqPreviewWindow()
{

}

void EqPreviewWindow::charmDisplay()
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


    tabFormLayout[0]->addRow(tr("&Type of charm : "), tabLabel[0]);
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

void EqPreviewWindow::armorDisplay(uint8_t type)
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

void EqPreviewWindow::weaponDisplay(uint8_t type)
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


