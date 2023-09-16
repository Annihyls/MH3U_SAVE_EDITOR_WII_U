#include "ItemModifierWindow.hpp"
#include <QCompleter>

ItemModifierWindow::ItemModifierWindow(SaveDataManager *sdm, Database *db, SaveDataManager::ItemMode mode, QWidget *parent, int id_emplacement) :
    QDialog(parent), m_sdm(sdm), m_db(db), m_mode(mode), m_id_emplacement(id_emplacement)
{
    m_mainLayout = new QVBoxLayout(this);
    m_quantityInput = new QSpinBox(this);
    m_id_item = new QLineEdit(this);

    m_mainLayout->addWidget(m_id_item);
    m_mainLayout->addWidget(m_quantityInput);

    setModal(true);
    setLayout(m_mainLayout);
    setWindowTitle(QString("Item Modifier"));

    loadData();
}

ItemModifierWindow::~ItemModifierWindow()
{
    this->m_sdm = NULL;
    this->m_db = NULL;
}

void ItemModifierWindow::loadData()
{
    QStringList item_list;
    QString str_temp;

    //contient un tableau dont case 0 = id, case 1 = quantité
    uint16_t *item = m_sdm->getItem(m_mode, m_id_emplacement);

    //pour que l'index 0 correspond à un emplacement vide dans la boite
    item_list.push_back("");

    for(int i=0; i < m_db->getSize(); i++)
    {
        str_temp = m_db->getElement(i);
        if(str_temp.startsWith("DUMMY"))
        {
            item_list.push_back("");
        }
        else
        {
            item_list.push_back(str_temp);
        }
    }

    //pour l'autocomplétion quand on cherche un item
    QCompleter *qc = new QCompleter(item_list, this);
    qc->setCaseSensitivity(Qt::CaseInsensitive);
    qc->setFilterMode(Qt::MatchContains);

    m_id_item->setCompleter(qc);
    m_id_item->setText(item_list[item[0]]);

    m_quantityInput->setMaximum(99);
    m_quantityInput->setValue(item[1]);

    delete item;
}

void ItemModifierWindow::saveData()
{
    /*
     * sauvegarde les données dans m_sdm
     */
    unsigned short id;

    //si chaine vide (ou on tente de créer un DUMMY OBJET), alors on créer un emplacement vide
    if(m_id_item->text().isEmpty() || m_id_item->text().startsWith("DUMMY"))
    {
        m_sdm->setItem(m_mode, m_id_emplacement, 0, 0);
    }
    else
    {
        for(id = 0; id < m_db->getSize(); id++)
        {
            //si le nom renseigné correspond bien à une donnée dans la base de donnée
            if(m_id_item->text().compare(m_db->getElement(id)) == 0)
            {
                //si on tente de mettre la quantité d'un objet à 0, on la force à 1
                if(m_quantityInput->value() == 0)
                {
                    m_sdm->setItem(m_mode, m_id_emplacement, id+1, 1);
                }
                else
                {
                    m_sdm->setItem(m_mode, m_id_emplacement, id+1, m_quantityInput->value());
                }
            }
        }
        //si la chaine ne correspond à aucun index, alors on ignore l'événement
    }
}

void ItemModifierWindow::closeEvent (QCloseEvent *event)
{

    saveData();
    event->accept();
}
