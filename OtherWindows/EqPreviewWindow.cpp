#include "EqPreviewWindow.hpp"

EqPreviewWindow::EqPreviewWindow(SaveDataManager *sdm, Database db, int id_emplacement, QWidget *parent):
    QDialog(parent), m_sdm(sdm), m_db(db), m_id_emplacement(id_emplacement)
{
    m_mainVLayout = new QVBoxLayout(this);
    m_upHLayout = new QHBoxLayout();
    m_downHLayout = new QHBoxLayout();

    uint8_t eq = m_sdm->getTypeEquipment(m_id_emplacement);
    //si pas d'équipement
    if(eq == 0)
    {
        //NO EQ DISPLAY
    }
    else if(eq == 6)
    {
        //CHARM DISPLAY
    }
    else if(eq == 1 || eq == 2 || eq == 3 || eq == 4 || eq == 5)
    {
        //armor display
    }
    else
    {
        //Weapon display
    }

    m_weaponTypeComBox = new QComboBox(this);

    for(QString &str : db.getDatabase(21))
    {
        if(str != "")
            m_weaponTypeComBox->addItem(str);
    }

    m_downHLayout->addWidget(m_weaponTypeComBox);
    m_mainVLayout->addLayout(m_upHLayout);
    m_mainVLayout->addLayout(m_downHLayout);
    setLayout(m_mainVLayout);
    setWindowTitle("Preview + Weapon Type Editing");

}

EqPreviewWindow::~EqPreviewWindow()
{

}

void EqPreviewWindow::charmDisplay()
{

}

void EqPreviewWindow::armorDisplay()
{

}

void EqPreviewWindow::weaponDisplay()
{

}


