#ifndef CHARACTERWINDOW_HPP
#define CHARACTERWINDOW_HPP

#include "../ReaderWriterClasses/SaveDataManager.hpp"
#include "../ReaderWriterClasses/Database.hpp"
#include <QObject>
#include <QMainWindow>
#include <QCloseEvent>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QStringList>

#define NUMBER_OF_BUTTON 9

class CharacterWindow : public QMainWindow
{
    Q_OBJECT

public:
    CharacterWindow(SaveDataManager *sdm,
                    QStringList listOfSex,
                    QStringList listOfFace,
                    QStringList listOfHair,
                    QStringList listOfVoice,
                    QWidget *parent = nullptr);
    ~CharacterWindow();

private:
    SaveDataManager *m_sdm;
    QStringList m_listOfSex;
    QStringList m_listOfFace;
    QStringList m_listOfHair;
    QStringList m_listOfVoice;

    QWidget *m_mainLayout;
    QVBoxLayout *m_vLayout;
    QHBoxLayout *m_hLayout[NUMBER_OF_BUTTON];
    QLabel *m_label[NUMBER_OF_BUTTON];

    QComboBox *m_sex;
    QComboBox *m_face;
    QComboBox *m_hair;
    QComboBox *m_voice;
    QLineEdit *m_nom;
    QSpinBox *m_HR;
    QSpinBox *m_argent;
    QSpinBox *m_ressource;
    QSpinBox *m_time_h;
    QSpinBox *m_time_m;

    void closeEvent(QCloseEvent *event);
    void loadData();
    void saveData();
};

#endif // CHARACTERWINDOW_HPP
