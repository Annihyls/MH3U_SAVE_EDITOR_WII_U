#include "ItemModifierWindow.hpp"
#include <QCompleter>

ItemModifierWindow::ItemModifierWindow(SaveDataManager *sdm, QStringList itemStringList, SaveDataManager::ItemMode mode, int id_emplacement, QWidget *parent) :
    QDialog(parent), m_sdm(sdm), m_itemStringList(itemStringList), m_mode(mode), m_id_emplacement(id_emplacement)
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
}

void ItemModifierWindow::loadData()
{
    //contient un tableau dont case 0 = id, case 1 = quantité
    uint16_t *item = m_sdm->getItem(m_mode, m_id_emplacement);


    //pour l'autocomplétion quand on cherche un item
    QCompleter *qc = new QCompleter(m_itemStringList, this);
    qc->setCaseSensitivity(Qt::CaseInsensitive);
    qc->setFilterMode(Qt::MatchContains);

    m_id_item->setCompleter(qc);
    m_id_item->setText(m_itemStringList.at(item[0]));

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
    if(m_id_item->text().isEmpty())
    {
        m_sdm->setItem(m_mode, m_id_emplacement, 0, 0);
    }
    else
    {
        for(id = 0; id < m_itemStringList.size(); id++)
        {
            //si le nom renseigné correspond bien à une donnée dans la base de donnée
            if(m_itemStringList.at(id) == m_id_item->text())
            {
                //si on tente de mettre la quantité d'un objet à 0, on la force à 1
                if(m_quantityInput->value() == 0)
                {
                    m_sdm->setItem(m_mode, m_id_emplacement, id, 1);
                }
                else
                {
                    m_sdm->setItem(m_mode, m_id_emplacement, id, m_quantityInput->value());
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
