#include "EquipmentBoxWindow.hpp"
#include "EqModifierWindow.hpp"

#include <QSignalMapper>
#include <QIcon>

EquipmentBoxWindow::EquipmentBoxWindow(SaveDataManager *sdm, Database db, QWidget *parent) :
    QMainWindow(parent), m_sdm(sdm), m_db(db)
{
    m_mainLayout = new QWidget(this);

    m_panel = new QTabWidget(this);
    QWidget *wdg;
    QGridLayout *individualPanel;
    uint8_t id;
    QSignalMapper *signalMapper = new QSignalMapper(this);
    connect(signalMapper, &QSignalMapper::mappedInt, this, &EquipmentBoxWindow::changeEq);

    for(int i = 0; i < 10; i++)
    {
        wdg = new QWidget(this);
        m_panel->addTab(wdg, QString("Panel %1").arg(i+1));
        individualPanel = new QGridLayout(wdg);

        //200 car eq_box = 2000 car 2*64 bits = 1 équipent
        for(int j=0; j < 200; j++)
        {
            if((i * 100 + j)%2 == 0)
            {
                id = m_sdm->getTypeEquipment(i * 200 + j);
                m_eq_emplacement[i][j/2] = new QPushButton(wdg);
                m_eq_emplacement[i][j/2]->setIcon
                    (
                        QIcon
                        (
                            QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/res/equipment_icon/%1.ico").arg(id)
                            )
                        );
                m_eq_emplacement[i][j/2]->setFixedHeight(35);
                m_eq_emplacement[i][j/2]->setFixedWidth(45);

                individualPanel->addWidget(m_eq_emplacement[i][j/2], j / 20, j % 20);

                signalMapper->setMapping(m_eq_emplacement[i][j/2], i * 200 + j);
                connect(m_eq_emplacement[i][j/2], SIGNAL(clicked(bool)), signalMapper, SLOT(map()));
            }

        }

    }

    m_mainGridLayout = new QGridLayout(m_mainLayout);
    m_mainGridLayout->addWidget(m_panel);
    m_mainLayout->setLayout(m_mainGridLayout);

    setCentralWidget(m_mainLayout);
    setWindowTitle("Equipment Box Editor");
    setMinimumWidth(680);
    setWindowModality(Qt::WindowModal);
}

EquipmentBoxWindow::~EquipmentBoxWindow()
{
    this->m_sdm = NULL;
}

void EquipmentBoxWindow::changeEq(int id_emplacement)
{
    EqModifierWindow *eqPrev = new EqModifierWindow(m_sdm, m_db, id_emplacement, this);
    eqPrev->exec();
    delete eqPrev;
    uint8_t weaponType = m_sdm->getTypeEquipment(id_emplacement);
    m_eq_emplacement[id_emplacement/200][(id_emplacement/2)%100]->setIcon
        (
            QIcon
            (
                QString("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/res/equipment_icon/%1.ico").arg(weaponType)
                )
            );

}
