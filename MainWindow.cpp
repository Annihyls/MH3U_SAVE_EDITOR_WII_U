#include "MainWindow.hpp"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    m_sdm = new SaveDataManager();

    m_mainWidget = new QWidget(this);

    m_vLayoutLeft = new QVBoxLayout();
    m_vLayoutRight = new QVBoxLayout();

    m_hLayout = new QHBoxLayout(m_mainWidget);

    m_hLayout->addLayout(m_vLayoutLeft);
    m_hLayout->addLayout(m_vLayoutRight);

    //Bouttons à gauche
    m_character = new QPushButton(QString("Character"), m_mainWidget);
    m_character->setEnabled(false);
    m_vLayoutLeft->addWidget(m_character);
    connect(m_character, SIGNAL(clicked(bool)), this, SLOT(characterWindow()));

    m_inventory = new QPushButton(QString("Inventory"), m_mainWidget);
    m_inventory->setEnabled(false);
    m_vLayoutLeft->addWidget(m_inventory);
    connect(m_inventory, SIGNAL(clicked(bool)), this, SLOT(inventoryWindow()));

    m_pouch = new QPushButton(QString("Pouch"), m_mainWidget);
    m_pouch->setEnabled(false);
    m_vLayoutLeft->addWidget(m_pouch);
    connect(m_pouch, SIGNAL(clicked(bool)), this, SLOT(pouchWindow()));

    m_item_box = new QPushButton(QString("Item Box"), m_mainWidget);
    m_item_box->setEnabled(false);
    m_vLayoutLeft->addWidget(m_item_box);
    connect(m_item_box, SIGNAL(clicked(bool)), this, SLOT(itemBoxWindow()));

    //Boutons à droite
    m_load_file = new QPushButton("Load file", m_mainWidget);
    m_save_file = new QPushButton("Save file", m_mainWidget);
    m_save_file->setEnabled(false);
    m_vLayoutRight->addWidget(m_load_file);
    m_vLayoutRight->addWidget(m_save_file);
    connect(m_load_file, SIGNAL(clicked(bool)), this, SLOT(lireDonnees()));
    connect(m_save_file, SIGNAL(clicked(bool)), this, SLOT(ecrireDonnees()));

    setCentralWidget(m_mainWidget);
    setMinimumWidth(320);
    setMinimumHeight(120);
    setWindowIcon(QIcon("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/res/appico.ico"));

}

MainWindow::~MainWindow()
{
    delete m_sdm;
}

void MainWindow::lireDonnees()
{
    QString file_path = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("user (*)"));
    if(!file_path.isEmpty())
    {
        m_sdm->lire_donnees(file_path.toStdString());
        //Une fois un fichier chargé, on peut le modifier

        //cette section pré-charge les fenêtres
        m_cw = new CharacterWindow(m_sdm, this);
        m_ibw = new ItemBoxWindow(m_sdm, this);
        m_iw = new InventoryPouchWindow(m_sdm, this, SaveDataManager::ItemMode::INVENTORY);
        m_pw = new InventoryPouchWindow(m_sdm, this, SaveDataManager::ItemMode::POUCH);

        //on autorise l'accès aux bouttons
        m_character->setEnabled(true);
        m_inventory->setEnabled(true);
        m_pouch->setEnabled(true);
        m_item_box->setEnabled(true);
        m_save_file->setEnabled(true);

    }

}

void MainWindow::ecrireDonnees()
{
    QString file_path = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("user (*)"));
    if(!file_path.isEmpty())
    {
        m_sdm->ecrire_donnees(file_path.toStdString());
    }
}

void MainWindow::characterWindow()
{
    m_cw->move(this->pos());
    m_cw->activateWindow();
    m_cw->show();
}

void MainWindow::itemBoxWindow()
{
    m_ibw->move(this->pos());
    m_ibw->activateWindow();
    m_ibw->show();
}

void MainWindow::inventoryWindow()
{
    m_iw->move(this->pos());
    m_iw->activateWindow();
    m_iw->show();
}

void MainWindow::pouchWindow()
{
    m_pw->move(this->pos());
    m_pw->activateWindow();
    m_pw->show();
}
