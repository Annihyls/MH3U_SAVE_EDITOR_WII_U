#ifndef EQPREVIEWWINDOW_HPP
#define EQPREVIEWWINDOW_HPP

#include "../ReaderWriterClasses/SaveDataManager.hpp"
#include "../ReaderWriterClasses/Database.hpp"

#include <QDialog>
#include <QObject>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QComboBox>


class EqPreviewWindow : public QDialog
{
    Q_OBJECT
public:
    EqPreviewWindow(SaveDataManager *sdm, Database db, int id_emplacement, QWidget *parent = nullptr);
    ~EqPreviewWindow();

private:
    SaveDataManager *m_sdm;
    Database m_db;

    QVBoxLayout *m_mainVLayout;
    QHBoxLayout *m_upHLayout;
    QHBoxLayout *m_downHLayout;

    QComboBox *m_weaponTypeComBox;
    int m_id_emplacement;


    void charmDisplay();
    void armorDisplay();
    void weaponDisplay();
};

#endif // EQPREVIEWWINDOW_HPP
