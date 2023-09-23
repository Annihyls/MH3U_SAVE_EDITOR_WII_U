#include "ArmorModifierWindow.hpp"
#include <QCompleter>

ArmorModifierWindow::ArmorModifierWindow(SaveDataManager *sdm,
                                         uint8_t typeArmor,
                                         int id_emplacement,
                                         QStringList armorNameStringList,
                                         QStringList jwlStringList,
                                         QWidget *parent) :
    QDialog(parent), m_sdm(sdm), m_armorNameStringList(armorNameStringList),
    m_jwlStringList(jwlStringList), m_id_emplacement(id_emplacement), m_typeArmor(typeArmor)
{
    m_vLayout = new QVBoxLayout(this);

    QFormLayout *tabFormLayout[5];
    QCompleter *armorListCompleter = new QCompleter(m_armorNameStringList, this);
    QCompleter *jwlListCompleter = new QCompleter(m_jwlStringList, this);

    armorListCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    armorListCompleter->setFilterMode(Qt::MatchContains);

    jwlListCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    jwlListCompleter->setFilterMode(Qt::MatchContains);

    for(int i = 0; i<5; i++)
    {
        tabFormLayout[i] = new QFormLayout();
    }

    m_nameArmor = new QLineEdit(this);
    m_nameArmor->setCompleter(armorListCompleter);

    m_amelioration = new QSpinBox(this);
    m_amelioration->setMaximum(26);

    m_firstjwl = new QLineEdit(this);
    m_firstjwl->setCompleter(jwlListCompleter);

    m_secondjwl = new QLineEdit(this);
    m_secondjwl->setCompleter(jwlListCompleter);

    m_thirdjwl = new QLineEdit(this);
    m_thirdjwl->setCompleter(jwlListCompleter);

    tabFormLayout[0]->addRow(tr("&Armor name : "), m_nameArmor);
    tabFormLayout[1]->addRow(tr("&Amelioration level : "), m_amelioration);
    tabFormLayout[2]->addRow(tr("&1st deco : "), m_firstjwl);
    tabFormLayout[3]->addRow(tr("&2nd deco : "), m_secondjwl);
    tabFormLayout[4]->addRow(tr("&3rd deco : "), m_thirdjwl);

    for(int i = 0; i<5; i++)
    {
        m_vLayout->addLayout(tabFormLayout[i]);
    }

    setWindowTitle("Armor Modifier");

}

void ArmorModifierWindow::saveData()
{
    /*
     * sauvegarde les données dans m_sdm
     */
    uint16_t id;
    uint16_t jwl1;
    uint16_t jwl2;
    uint16_t jwl3;

    //si chaine vide, alors on créer un emplacement vide
    if(m_nameArmor->text().isEmpty())
    {
        m_sdm->setArmor(m_id_emplacement, 0, 0, 0, 0, 0, 0);
    }
    else
    {
        for(id = 0; id < m_armorNameStringList.size(); id++)
        {
            //si le nom renseigné correspond bien à une donnée dans la base de donnée
            if(m_armorNameStringList.at(id) == m_nameArmor->text())
            {
                jwl1 = checkJWL(m_firstjwl);
                jwl2 = checkJWL(m_secondjwl);
                jwl3 = checkJWL(m_thirdjwl);
                m_sdm->setArmor(m_id_emplacement, m_typeArmor, m_amelioration->value(), id, jwl1, jwl2, jwl3);
            }

        }
        //si la chaine ne correspond à aucun index, alors on ignore l'événement
    }
}

uint16_t ArmorModifierWindow::checkJWL(QLineEdit *jwl)
{
    uint16_t id;

    for(id = 0; id < m_jwlStringList.size(); id++)
    {
        //si le nom renseigné correspond bien à une donnée dans la base de donnée
        if(m_jwlStringList.at(id) == jwl->text())
        {
            return id;
        }

    }
    //sinon pas de joyaux
    return 0;
}

void ArmorModifierWindow::closeEvent(QCloseEvent *event)
{
    saveData();
    event->accept();
}
