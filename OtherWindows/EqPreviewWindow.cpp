#include "EqPreviewWindow.hpp"

EqPreviewWindow::EqPreviewWindow(SaveDataManager *sdm, Database *db[], int id_emplacement, QWidget *parent):
    QDialog(parent), m_sdm(sdm), m_db(db[NBR_OF_WEAP_TYPE]), m_id_emplacement(id_emplacement)
{
    m_mainVLayout = new QVBoxLayout(this);
    //faire le window preview eq
}

EqPreviewWindow::~EqPreviewWindow()
{

}
