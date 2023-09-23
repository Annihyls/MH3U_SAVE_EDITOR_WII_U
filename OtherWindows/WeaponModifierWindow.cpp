#include "WeaponModifierWindow.hpp"
#include <QCompleter>

WeaponModifierWindow::WeaponModifierWindow(SaveDataManager *sdm,
                                           uint8_t typeWeapon,
                                           int id_emplacement,
                                           QStringList weaponNameStringList,
                                           QStringList jwlStringList,
                                           QWidget *parent) :
    QDialog(parent), m_sdm(sdm), m_weaponNameStringList(weaponNameStringList),
    m_jwlStringList(jwlStringList), m_id_emplacement(id_emplacement), m_typeWeapon(typeWeapon)
{
    m_vLayout = new QVBoxLayout(this);

    QFormLayout *tabFormLayout[4];
    QCompleter *weaponListCompleter = new QCompleter(m_weaponNameStringList, this);
    QCompleter *jwlListCompleter = new QCompleter(m_jwlStringList, this);

    weaponListCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    weaponListCompleter->setFilterMode(Qt::MatchContains);

    jwlListCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    jwlListCompleter->setFilterMode(Qt::MatchContains);

    for(int i = 0; i<4; i++)
    {
        tabFormLayout[i] = new QFormLayout();
    }

    m_nameWeapon = new QLineEdit(this);
    m_nameWeapon->setCompleter(weaponListCompleter);

    m_firstjwl = new QLineEdit(this);
    m_firstjwl->setCompleter(jwlListCompleter);

    m_secondjwl = new QLineEdit(this);
    m_secondjwl->setCompleter(jwlListCompleter);

    m_thirdjwl = new QLineEdit(this);
    m_thirdjwl->setCompleter(jwlListCompleter);

    tabFormLayout[0]->addRow(tr("&Weapon name : "), m_nameWeapon);
    tabFormLayout[1]->addRow(tr("&1st deco : "), m_firstjwl);
    tabFormLayout[2]->addRow(tr("&2nd deco : "), m_secondjwl);
    tabFormLayout[3]->addRow(tr("&3rd deco : "), m_thirdjwl);

    for(int i = 0; i<4; i++)
    {
        m_vLayout->addLayout(tabFormLayout[i]);
    }

    setWindowTitle("Weapon Modifier");
}

void WeaponModifierWindow::saveData()
{
    /*
     * sauvegarde les données dans m_sdm
     */
    uint16_t id;
    uint16_t jwl1;
    uint16_t jwl2;
    uint16_t jwl3;

    //si chaine vide, alors on créer un emplacement vide
    if(m_nameWeapon->text().isEmpty())
    {
        m_sdm->setWeapon(m_id_emplacement, 0, 0, 0, 0, 0);
    }
    else
    {
        for(id = 0; id < m_weaponNameStringList.size(); id++)
        {
            //si le nom renseigné correspond bien à une donnée dans la base de donnée
            if(m_weaponNameStringList.at(id) == m_nameWeapon->text())
            {
                jwl1 = checkJWL(m_firstjwl);
                jwl2 = checkJWL(m_secondjwl);
                jwl3 = checkJWL(m_thirdjwl);
                m_sdm->setWeapon(m_id_emplacement, m_typeWeapon, id, jwl1, jwl2, jwl3);
            }

        }
        //si la chaine ne correspond à aucun index, alors on ignore l'événement
    }
}

uint16_t WeaponModifierWindow::checkJWL(QLineEdit *jwl)
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

void WeaponModifierWindow::closeEvent(QCloseEvent *event)
{
    saveData();
    event->accept();
}
