//----------------------------------------------------------------------

#include <QGridLayout>
#include <QTreeView>
#include <QMenuBar>
#include <QFrame>
#include <QLabel>

#include "ModelTreeBatch.h"
#include "SharedData.h"
#include "ParseUtils.h"
#include "Batch.h"
#include "Alarm.h"

#include "MainWindow.h"

//----------------------------------------------------------------------
MainWindow::MainWindow ( QWidget *i_widgetParent ) : QMainWindow (i_widgetParent)
{
    setMenuBar (getMenuBar ());
    setCentralWidget (getCentralWidget ());
    setMinimumSize (800, 800.0 * 10.0 / 16.0);

    reloadData ();
}

//----------------------------------------------------------------------
MainWindow::~MainWindow ()
{
}

//----------------------------------------------------------------------
void MainWindow::slotFinished ( int i_exitCode, QProcess::ExitStatus i_exitStatus )
{
}

//----------------------------------------------------------------------
void MainWindow::slotTriggered ( bool i_checked )
{
    reloadData ();
}

//----------------------------------------------------------------------
QMenuBar *MainWindow::getMenuBar ()
{
    QMenuBar *menuBar = new QMenuBar;

    QMenu *menuFile = menuBar->addMenu ("File");

    menuFile->addAction ("Refresh", this, SLOT (slotTriggered (bool)), QKeySequence (Qt::Key_F5));

    return menuBar;
}

//----------------------------------------------------------------------
QWidget *MainWindow::getCentralWidget ()
{
    QFrame *frame = new QFrame;
    QGridLayout *layout = new QGridLayout;

    QTabWidget *tabWidget = new QTabWidget;
    tabWidget->addTab (m_treeBatches = new QTreeView, "Tabular form");
    tabWidget->addTab (m_teRawSource = new QTextEdit, "Raw source");

    m_teRawSource->setFont (QFont ("Courier"));
    m_teRawSource->setReadOnly (true);

    layout->addWidget (new QLabel ("Last DateTime"), 0, 0);
    layout->addWidget (m_leTimestamp = new QLineEdit (), 0, 1);
    layout->addWidget (new QLabel ("System Uptime (ms)"), 1, 0);
    layout->addWidget (m_leSystemUptimeMs = new QLineEdit (), 1, 1);
    layout->addWidget (new QLabel ("System Uptime"), 2, 0);
    layout->addWidget (m_leSystemUptime = new QLineEdit (), 2, 1);
    layout->addWidget (new QLabel ("Package"), 3, 0);
    layout->addWidget (m_leFilterPackage = new QLineEdit (), 3, 1);
    layout->addWidget (tabWidget, 4, 0, 1, 2);

    m_leFilterPackage->setText ("");

    m_treeBatches->setModel (m_modelBatches = new ModelTreeBatch);
    m_treeBatches->setColumnWidth (0, 240);
    m_treeBatches->setColumnWidth (1, 160);
    m_treeBatches->setColumnWidth (2, 120);
    m_treeBatches->setColumnWidth (3, 120);

    //m_treeBatches->expandAll ();

    m_leTimestamp->setEnabled (false);
    m_leSystemUptime->setEnabled (false);
    m_leSystemUptimeMs->setEnabled (false);

    frame->setLayout (layout);

    return frame;
}

//----------------------------------------------------------------------
void MainWindow::reloadData ()
{
    QProcess processDumpsysAlarm;

    processDumpsysAlarm.start ("adb shell dumpsys alarm");
    if (processDumpsysAlarm.waitForFinished () == false)
    {
        return;
    }

    QByteArray byteArray = processDumpsysAlarm.readAll ();

    m_teRawSource->setText (QString (byteArray));

    int offset = 0;

    QString timeInformation = ParseUtils::getTextBetween (byteArray, "nowRTC=", "mLastTimeChangeClockTime=", offset).trimmed ().replace (" ", "=");
    QStringList components = timeInformation.split ("=");

    SharedData *sharedData = SharedData::getInstance ();
    sharedData->setCurrentTimestamp (components [0].toULongLong ());
    sharedData->setDateTime (components [1] + " " + components [2]);
    sharedData->setUptimeMilliseconds (components [4].toULongLong ());

    qulonglong uptimeSeconds = sharedData->getUptimeMilliseconds () / 1000;
    qulonglong uptimeHours = uptimeSeconds / 3600;
    qulonglong uptimeMinutes = (uptimeSeconds % 3600) / 60;
    qulonglong uptimeSecs = uptimeSeconds % 60;

    m_leSystemUptimeMs->setText (QString ("%1").arg (sharedData->getUptimeMilliseconds ()));
    m_leSystemUptime->setText (QString ("%1:%2:%3").arg (uptimeHours).arg (uptimeMinutes).arg (uptimeSecs));
    m_leTimestamp->setText (sharedData->getDateTime ());

    int pendingAlarmBatches = ParseUtils::getNextNumberAfter (byteArray, "Pending alarm batches: ", offset);

    QList<Batch*> listBatches;
    while (true)
    {
        QString batchDefinition = ParseUtils::getTextBetween (byteArray, "Batch{", "}:", offset);
        if (batchDefinition.isEmpty () == true)
        {
            break;
        }

        offset += 3;

        Batch *batch = Batch::fromString (batchDefinition);
        if (batch == nullptr)
        {
            break;
        }

        int nextIndex = byteArray.indexOf ("Batch{", offset);
        QString alarmListDefinition = byteArray.mid (offset, nextIndex - offset).trimmed ();

        alarmListDefinition.replace ("ELAPSED_WAKEUP", "ELAPSED").replace ("RTC_WAKEUP", "ELAPSED").replace ("RTC", "ELAPSED");

        QStringList alarmList = alarmListDefinition.split ("ELAPSED", QString::SkipEmptyParts);

        for ( int i = 0; i < alarmList.count (); ++i )
        {
            Alarm *alarm = Alarm::fromString (alarmList [i]);
            if (m_leFilterPackage->text ().isEmpty () == false && alarm->getOwnerPackageName () != m_leFilterPackage->text ())
            {
                delete alarm;
                continue;
            }

            batch->appendAlarm (alarm);
        }

        listBatches.append (batch);

        if (listBatches.count () == pendingAlarmBatches)
        {
            break;
        }
    }

    m_modelBatches->setBatchList (listBatches);
}
