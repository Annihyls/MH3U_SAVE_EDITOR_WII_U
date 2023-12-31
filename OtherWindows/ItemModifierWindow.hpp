#ifndef ITEMMODIFIERWINDOW_HPP
#define ITEMMODIFIERWINDOW_HPP

#include "../ReaderWriterClasses/SaveDataManager.hpp"
#include "../ReaderWriterClasses/Database.hpp"

#include <QDialog>
#include <QObject>
#include <QCloseEvent>
#include <QVBoxLayout>
#include <QSpinBox>
#include <QLineEdit>
#include <QStringList>

class ItemModifierWindow : public QDialog
{
    Q_OBJECT

public:
    ItemModifierWindow(SaveDataManager *sdm, QStringList itemStringList, SaveDataManager::ItemMode mode, int id_emplacement, QWidget *parent = nullptr);
    ~ItemModifierWindow();

private:
    SaveDataManager *m_sdm;
    QStringList m_itemStringList;
    SaveDataManager::ItemMode m_mode;

    QVBoxLayout *m_mainLayout;
    QSpinBox *m_quantityInput;
    QLineEdit *m_id_item;
    int m_id_emplacement;

    void closeEvent(QCloseEvent *event);
    void loadData();
    void saveData();

};

#endif // ITEMMODIFIERWINDOW_HPP
