#include "CharmModifierWindow.hpp"
#include <QCompleter>

CharmModifierWindow::CharmModifierWindow(SaveDataManager *sdm,
                                         int id_emplacement,
                                         QStringList charmStringList,
                                         QStringList skillStringList,
                                         QStringList jwlStringList, QWidget *parent) :

    QDialog(parent), m_sdm(sdm), m_charmStringList(charmStringList), m_skillStringList(skillStringList),
    m_jwlStringList(jwlStringList), m_id_emplacement(id_emplacement)
{
    m_vLayout = new QVBoxLayout(this);

    QFormLayout *tabFormLayout[9];
    QCompleter *skillsListCompleter = new QCompleter(skillStringList, this);
    QCompleter *jwlListCompleter = new QCompleter(jwlStringList, this);

    skillsListCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    skillsListCompleter->setFilterMode(Qt::MatchContains);

    jwlListCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    jwlListCompleter->setFilterMode(Qt::MatchContains);

    for(int i = 0; i<9; i++)
    {
        tabFormLayout[i] = new QFormLayout();
    }


    m_typeOfCharm = new QComboBox(this);
    for(QString &str : m_charmStringList)
    {
        m_typeOfCharm->addItem(str);
    }

    m_nbrSlot = new QSpinBox(this);
    m_nbrSlot->setMaximum(3);

    m_firstSkill = new QLineEdit(this);
    m_firstSkill->setCompleter(skillsListCompleter);

    m_firstSkillPoints = new QSpinBox(this);
    m_firstSkillPoints->setMaximum(127);

    m_secondSkill = new QLineEdit(this);
    m_secondSkill->setCompleter(skillsListCompleter);

    m_secondSkillPoints = new QSpinBox(this);
    m_secondSkillPoints->setMaximum(127);

    m_firstjwl = new QLineEdit(this);
    m_firstjwl->setCompleter(jwlListCompleter);

    m_secondjwl = new QLineEdit(this);
    m_secondjwl->setCompleter(jwlListCompleter);

    m_thirdjwl = new QLineEdit(this);
    m_thirdjwl->setCompleter(jwlListCompleter);

    tabFormLayout[0]->addRow(tr("&Type of talisman : "), m_typeOfCharm);
    tabFormLayout[1]->addRow(tr("&Slots : "), m_nbrSlot);
    tabFormLayout[2]->addRow(tr("&1st skill name : "), m_firstSkill);
    tabFormLayout[3]->addRow(tr("&1st skill points : "), m_firstSkillPoints);
    tabFormLayout[4]->addRow(tr("&2nd skill name : "), m_secondSkill);
    tabFormLayout[5]->addRow(tr("&2nd skill points : "), m_secondSkillPoints);
    tabFormLayout[6]->addRow(tr("&1st deco : "), m_firstjwl);
    tabFormLayout[7]->addRow(tr("&2nd deco : "), m_secondjwl);
    tabFormLayout[8]->addRow(tr("&3rd deco : "), m_thirdjwl);

    for(int i = 0; i<9; i++)
    {
        m_vLayout->addLayout(tabFormLayout[i]);
    }

    setWindowTitle("Talisman Modifier");
}

void CharmModifierWindow::saveData()
{
    /*
     * sauvegarde les données dans m_sdm
     */
    uint8_t *firstSkill;
    uint8_t *secondSkill;
    uint16_t jwl1;
    uint16_t jwl2;
    uint16_t jwl3;

    //si chaine vide, alors on créer un emplacement vide
    if(m_typeOfCharm->currentIndex() == 0)
    {
        m_sdm->setCharm(m_id_emplacement, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    }
    else
    {
        firstSkill = checkSkill(m_firstSkill, m_firstSkillPoints);   //[0] = skill id, [1] = nbrPoint
        secondSkill = checkSkill(m_secondSkill, m_secondSkillPoints);
        jwl1 = checkJWL(m_firstjwl);
        jwl2 = checkJWL(m_secondjwl);
        jwl3 = checkJWL(m_thirdjwl);
        m_sdm->setCharm(m_id_emplacement,
                        6,
                        m_nbrSlot->value(),
                        m_typeOfCharm->currentIndex(),
                        firstSkill[0],
                        firstSkill[1],
                        secondSkill[0],
                        secondSkill[1],
                        jwl1, jwl2, jwl3);

        delete[] firstSkill;
        delete[] secondSkill;
    }
}

uint16_t CharmModifierWindow::checkJWL(QLineEdit *jwl)
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

uint8_t* CharmModifierWindow::checkSkill(QLineEdit *skill, QSpinBox *points)
{
    uint8_t *id = new uint8_t[2];
    for(uint8_t i = 0; i < m_skillStringList.size(); i++)
    {
        //si le nom renseigné correspond bien à une donnée dans la base de donnée
        if(m_skillStringList.at(i) == skill->text() && !m_skillStringList.at(i).isEmpty())
        {
            //si on tente de mettre le nombre de points d'un talent à 0,
            if(points->value() == 0)
            {
                id[0] = i;
                id[1] = 1;
                return id;
            }
            else
            {
                id[0] = i;
                id[1] = points->value();
                return id;
            }
        }

    }
    //sinon pas de skill
    id[0] = 0;
    id[1] = 0;
    return id;
}

void CharmModifierWindow::closeEvent(QCloseEvent *event)
{
    saveData();
    event->accept();
}
