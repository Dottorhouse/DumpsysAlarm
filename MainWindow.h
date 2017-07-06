//----------------------------------------------------------------------

#pragma once

//----------------------------------------------------------------------

#include <QMainWindow>
#include <QTreeView>
#include <QTextEdit>
#include <QLineEdit>
#include <QProcess>

//----------------------------------------------------------------------

class ModelTreeBatch;

//----------------------------------------------------------------------
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    MainWindow ( QWidget *i_widgetParent = nullptr );

    ~MainWindow ();

private slots:

    void slotFinished ( int i_exitCode, QProcess::ExitStatus i_exitStatus );

    void slotTriggered ( bool i_checked );

private:

    QMenuBar *getMenuBar ();

    QWidget *getCentralWidget ();

    void reloadData ();

    QProcess *m_processDumpsysAlarm;

    QLineEdit *m_leTimestamp;
    QLineEdit *m_leSystemUptimeMs;
    QLineEdit *m_leSystemUptime;
    QLineEdit *m_leFilterPackage;
    QTreeView *m_treeBatches;
    QTextEdit *m_teRawSource;

    ModelTreeBatch *m_modelBatches;

};
