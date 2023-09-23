#include "MainWindow.hpp"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
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

    m_eq_box = new QPushButton(QString("Equipment Box"), m_mainWidget);
    m_eq_box->setEnabled(false);
    m_vLayoutLeft->addWidget(m_eq_box);
    connect(m_eq_box, SIGNAL(clicked(bool)), this, SLOT(eqBoxWindow()));

    //Boutons à droite
    m_load_file = new QPushButton("Load file", m_mainWidget);
    m_load_file->setIcon(QIcon("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/res/load.ico"));
    connect(m_load_file, SIGNAL(clicked(bool)), this, SLOT(lireDonnees()));
    m_vLayoutRight->addWidget(m_load_file);

    m_save_file = new QPushButton("Save file", m_mainWidget);
    m_save_file->setIcon(QIcon("C:/Users/vince/Desktop/QTtest/MH3U_SE_WII_U/res/save.ico"));
    m_save_file->setEnabled(false);
    connect(m_save_file, SIGNAL(clicked(bool)), this, SLOT(ecrireDonnees()));
    m_vLayoutRight->addWidget(m_save_file);


    m_option = new QPushButton(QString("Option"), m_mainWidget);
    m_vLayoutRight->addWidget(m_option);
    connect(m_option, SIGNAL(clicked(bool)), this, SLOT(optionWindow()));

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
    QString file_path = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("user file(user1;user2;user3)"));
    if(!file_path.isEmpty())
    {
        delete m_sdm;
        m_sdm = new SaveDataManager();
        m_sdm->lire_donnees(file_path.toStdString());

        loadWindowsAndDatabases();

        //on autorise l'accès aux bouttons
        m_character->setEnabled(true);
        m_inventory->setEnabled(true);
        m_eq_box->setEnabled(true);
        m_pouch->setEnabled(true);
        m_item_box->setEnabled(true);
        m_save_file->setEnabled(true);
    }

}

void MainWindow::ecrireDonnees()
{
    QString file_path = QFileDialog::getSaveFileName(this, tr("Save File"), "", tr("user file(*)"));
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

void MainWindow::optionWindow()
{
    m_ow = new Option(m_lang, this);
    m_ow->move(this->pos());
    m_ow->activateWindow();
    m_ow->exec();
    m_lang = m_ow->lang;
    loadWindowsAndDatabases();
    delete m_ow;
}

void MainWindow::eqBoxWindow()
{
    m_ebw->move(this->pos());
    m_ebw->activateWindow();
    m_ebw->show();
}

void MainWindow::loadWindowsAndDatabases()
{
    QString langue;
    switch(m_lang)
    {
    case Option::Lang::FR:
        langue = "fr";
        m_character->setText("Personnage");
        m_inventory->setText("Bourse Épéiste");
        m_pouch->setText("Bourse Artilleur");
        m_item_box->setText("Boite à objet");
        m_eq_box->setText("Boite d'équipement");
        m_save_file->setText("Sauvegarder Fichier");
        m_load_file->setText("Charger Fichier");
        break;
    case Option::Lang::EN:
        langue = "en";
        m_character->setText("Character");
        m_inventory->setText("Inventory");
        m_pouch->setText("Pouch");
        m_item_box->setText("Item Box");
        m_eq_box->setText("Equipment Box");
        m_save_file->setText("Save file");
        m_load_file->setText("Load file");
        break;
    }

    //cette section pré-charge les fenêtres
    //m_sdm ne doit pas être null !!!
    if(m_sdm != nullptr)
    {
        delete m_cw;
        delete m_ibw;
        delete m_iw;
        delete m_pw;
        delete m_ebw;
        delete m_db;

        m_db = new Database(langue);

        m_cw = new CharacterWindow(m_sdm,
                                   m_db->getDatabase(ID_DB_SEX),
                                   m_db->getDatabase(ID_DB_FACE),
                                   m_db->getDatabase(ID_DB_HAIR),
                                   m_db->getDatabase(ID_DB_VOICE),
                                   this);
        m_ibw = new ItemBoxWindow(m_sdm, m_db->getDatabase(ID_DB_ITEM), this);
        m_iw = new InventoryPouchWindow(m_sdm, m_db->getDatabase(ID_DB_ITEM), SaveDataManager::ItemMode::INVENTORY, this);
        m_pw = new InventoryPouchWindow(m_sdm, m_db->getDatabase(ID_DB_ITEM), SaveDataManager::ItemMode::POUCH, this);
        m_ebw = new EquipmentBoxWindow(m_sdm, *m_db, this);
    }
}
