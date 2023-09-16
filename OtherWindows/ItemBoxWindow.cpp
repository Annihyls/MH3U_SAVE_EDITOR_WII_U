#include "ItemBoxWindow.hpp"
#include "OtherWindows/ItemModifierWindow.hpp"
#include <QSignalMapper>
#include <QDebug>
#include <QIcon>

ItemBoxWindow::ItemBoxWindow(SaveDataManager *sdm, QWidget *parent) : QMainWindow(parent), m_sdm(sdm)
{
    /*
     * Charge les données
     */
    m_db = new Database("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/data/en/item.txt");

    m_mainLayout = new QWidget(this);

    m_panel = new QTabWidget(this);
    QWidget *wdg;
    QGridLayout *individualPanel;
    uint16_t *item;
    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(signalMapper, &QSignalMapper::mappedInt, this, &ItemBoxWindow::changeItem);

    for(int i = 0; i < 10; i++)
    {
        wdg = new QWidget(this);
        m_panel->addTab(wdg, QString("Panel %1").arg(i+1));
        individualPanel = new QGridLayout(wdg);


        for(int j=0; j < 100; j++)
        {
            item = m_sdm->getItem(i * 100 + j);

            m_item_emplacement[i][j] = new QPushButton(QString("x%1").arg(item[1]), wdg);
            m_item_emplacement[i][j]->setIcon
            (
                QIcon
                (
                    QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/res/item_icon/%1.ico").arg(item[0])
                )
            );
            m_item_emplacement[i][j]->setFixedHeight(35);
            m_item_emplacement[i][j]->setFixedWidth(45);

            individualPanel->addWidget(m_item_emplacement[i][j], j / 10, j % 10);

            signalMapper->setMapping(m_item_emplacement[i][j], i * 100 + j);
            connect(m_item_emplacement[i][j], SIGNAL(clicked(bool)), signalMapper, SLOT(map()));

            delete item;
            item = NULL;
        }

    }

    m_mainGridLayout = new QGridLayout(m_mainLayout);
    m_mainGridLayout->addWidget(m_panel);
    m_mainLayout->setLayout(m_mainGridLayout);

    setCentralWidget(m_mainLayout);
    setWindowTitle("Item Box Editor");
    setMinimumWidth(680);
    setWindowModality(Qt::WindowModal);
}

ItemBoxWindow::~ItemBoxWindow()
{
    this->m_sdm = NULL;
    delete this->m_db;
}

void ItemBoxWindow::changeItem(int id_emplacement)
{
    ItemModifierWindow *set_item_dialog = new ItemModifierWindow(m_sdm, m_db, this, id_emplacement);
    set_item_dialog->exec();
    delete set_item_dialog;

    //REFRESH
    uint16_t *item = m_sdm->getItem(id_emplacement);
    m_item_emplacement[id_emplacement/100][id_emplacement%100]->setIcon
    (
        QIcon
        (
            QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/res/item_icon/%1.ico").arg(item[0])
        )
    );
    m_item_emplacement[id_emplacement/100][id_emplacement%100]->setText(QString("x%1").arg(item[1]));
    delete item;
}
