#include "InventoryPouchWindow.hpp"
#include "OtherWindows/ItemModifierWindow.hpp"
#include <QLabel>
#include <QSignalMapper>


InventoryPouchWindow::InventoryPouchWindow(SaveDataManager *sdm, Database *db, QWidget *parent, SaveDataManager::ItemMode mode) :
    QMainWindow(parent), m_sdm(sdm), m_mode(mode), m_db(db)
{
    m_mainLayout = new QWidget(this);
    m_panel = new QTabWidget(this);
    m_vLayout = new QVBoxLayout(m_mainLayout);

    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(signalMapper, &QSignalMapper::mappedInt, this, &InventoryPouchWindow::changeItem);

    switch(m_mode)
    {
    case(SaveDataManager::ItemMode::INVENTORY):
        m_maxPanel = 3;
        setWindowTitle("Inventory Editor");
        break;
    default:
        m_maxPanel = 4;
        setWindowTitle("Pouch Editor");
        break;
    }

    QWidget *wdg;
    QVBoxLayout *individualVLayout;
    uint16_t *item;

    for(int i=0; i<m_maxPanel; i++)
    {
        wdg = new QWidget(this);
        m_panel->addTab(wdg, QString("Panel %1").arg(i+1));
        individualVLayout = new QVBoxLayout(wdg);

        for(int j=0; j<8; j++)
        {
        item = m_sdm->getItem(m_mode, i * 8 + j);
        m_slotItem[i][j] = new QPushButton(QString("x%1").arg(item[1]), wdg);
        m_slotItem[i][j]->setIcon
            (
                QIcon
                (
                    QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/res/item_icon/%1.ico").arg(item[0])
                    )
                );

        individualVLayout->addWidget(m_slotItem[i][j]);
        signalMapper->setMapping(m_slotItem[i][j], i * 8 + j);
        connect(m_slotItem[i][j], SIGNAL(clicked(bool)), signalMapper, SLOT(map()));

        delete item;
        item = NULL;
        }
    }

    m_vLayout->addWidget(m_panel);
    setMinimumWidth(320);
    setCentralWidget(m_mainLayout);
    setWindowModality(Qt::WindowModal);

}

InventoryPouchWindow::~InventoryPouchWindow()
{
    this->m_sdm = NULL;
    this->m_db = NULL;
}

void InventoryPouchWindow::changeItem(int id_emplacement)
{
    ItemModifierWindow *set_item_dialog = new ItemModifierWindow(m_sdm, m_db, m_mode, this, id_emplacement);
    set_item_dialog->exec();
    delete set_item_dialog;

    //REFRESH
    uint16_t *item = m_sdm->getItem(m_mode, id_emplacement);
    m_slotItem[id_emplacement/8][id_emplacement%8]->setIcon
        (
            QIcon
            (
                QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/res/item_icon/%1.ico").arg(item[0])
                )
            );
    m_slotItem[id_emplacement/8][id_emplacement%8]->setText(QString("x%1").arg(item[1]));
    delete item;
}
