#ifndef EQPREVIEWWINDOW_HPP
#define EQPREVIEWWINDOW_HPP

#include "../ReaderWriterClasses/SaveDataManager.hpp"
#include "../ReaderWriterClasses/Database.hpp"
#include "EquipmentBoxWindow.hpp"

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>


class EqPreviewWindow : public QDialog
{
    Q_OBJECT
public:
    EqPreviewWindow(SaveDataManager *sdm, Database *db[], int id_emplacement, QWidget *parent = nullptr);
    ~EqPreviewWindow();

private:
    SaveDataManager *m_sdm;
    Database *m_db[NBR_OF_WEAP_TYPE];

    QVBoxLayout *m_mainVLayout;
    int m_id_emplacement;



};

#endif // EQPREVIEWWINDOW_HPP
