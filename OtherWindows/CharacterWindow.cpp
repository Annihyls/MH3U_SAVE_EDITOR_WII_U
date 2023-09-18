#include "CharacterWindow.hpp"
#include <QMessageBox>

CharacterWindow::CharacterWindow(SaveDataManager *sdm, QStringList listOfSex, QWidget *parent) :
    QMainWindow(parent), m_sdm(sdm), m_listOfSex(listOfSex)
{
    m_mainLayout = new QWidget(this);
    m_vLayout = new QVBoxLayout(m_mainLayout);
    for(int i=0; i<NUMBER_OF_BUTTON; i++)
    {
        m_hLayout[i] = new QHBoxLayout();
        m_vLayout->addLayout(m_hLayout[i]);
    }

    m_label[0] = new QLabel("Sex :", this);
    m_label[1] = new QLabel("Name :", this);
    m_label[2] = new QLabel("HR :", this);
    m_label[3] = new QLabel("Money :", this);
    m_label[4] = new QLabel("Moga Points :", this);
    m_label[5] = new QLabel("Play Time :", this);
    QLabel *hour = new QLabel("h", this);
    QLabel *min = new QLabel("min", this);

    loadData();

    for(int i=0; i<NUMBER_OF_BUTTON; i++)
    {
        m_hLayout[i]->addWidget(m_label[i]);
    }

    m_hLayout[0]->addWidget(m_sex);
    m_hLayout[1]->addWidget(m_nom);
    m_hLayout[2]->addWidget(m_HR);
    m_hLayout[3]->addWidget(m_argent);
    m_hLayout[4]->addWidget(m_ressource);
    m_hLayout[5]->addWidget(m_time_h);
    m_hLayout[5]->addWidget(hour);
    m_hLayout[5]->addWidget(m_time_m);
    m_hLayout[5]->addWidget(min);

    setWindowTitle("Character Modifier");
    setCentralWidget(m_mainLayout);
    setMinimumWidth(320);
    setWindowModality(Qt::WindowModal);
}

CharacterWindow::~CharacterWindow()
{
    this->m_sdm = NULL;

    for(int i=0; i<NUMBER_OF_BUTTON; i++)
    {
        delete this->m_hLayout[i];
    }
}

void CharacterWindow::loadData()
{
    /************************SEX BUTTON************************/
    m_sex = new QComboBox(this);

    //j'ajoute les données du .txt (male et femelle ici) dans le QComboBox
    while(!m_listOfSex.empty())
    {
        if(m_listOfSex.first() != "")
        {
            m_sex->addItem(m_listOfSex.first());
        }
        m_listOfSex.removeFirst();
    }

    m_sex->setCurrentIndex(m_sdm->getSex()); //0 si homme, 1 si femme
    /********************************************************/

    /************************NAME LINEEDIT**********************/
    m_nom = new QLineEdit(this);

    QString name_str;
    for(int i=0; i<SIZE_NAME; i++)
    {
        name_str.append((char)m_sdm->getName()[i]);
    }
    m_nom->setMaxLength(SIZE_NAME);
    m_nom->setText(name_str);
    /**********************************************************/

    /************************HR SPINBOX***********************/
    m_HR = new QSpinBox(this);
    m_HR->setMaximum(999);
    m_HR->setValue(m_sdm->getHR());
    /*********************************************************/

    /************************MONEY SPINBOX***********************/
    m_argent = new QSpinBox(this);
    m_argent->setMaximum(9999999);
    m_argent->setValue(m_sdm->getArgent());
    /************************************************************/

    /************************MOGA POINT SPINBOX***********************/
    m_ressource = new QSpinBox(this);
    m_ressource->setMaximum(999999);
    m_ressource->setValue(m_sdm->getRessource());
    /*****************************************************************/

    /************************TIME SPINBOX***********************/
    //heures
    m_time_h = new QSpinBox(this);
    m_time_h->setMaximum(999);
    m_time_h->setValue(m_sdm->getTime()/3600);
    //minutes
    m_time_m = new QSpinBox(this);
    m_time_m->setMaximum(59);
    m_time_m->setValue((m_sdm->getTime()%3600)/60);
    /***********************************************************/
}

void CharacterWindow::saveData()
{
    //save
    m_sdm->setSex(m_sex->currentIndex());
    m_sdm->setName(m_nom->text().toStdString());
    m_sdm->setHR(m_HR->value());
    m_sdm->setArgent(m_argent->value());
    m_sdm->setRessource(m_ressource->value());
    m_sdm->setTime(m_time_h->value() * 3600 + m_time_m->value() * 60);
}

void CharacterWindow::closeEvent (QCloseEvent *event)
{
    saveData();
    event->accept();
}
