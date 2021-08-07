#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:


    void on_treeWidget_itemClicked(QTreeWidgetItem *item, int column);

    void on_actionAdd_triggered();

    void show_list();

    void on_Cancel_clicked();

    void on_Save_clicked();

    void on_isMan_clicked();

    void on_isWoman_clicked();

    void on_TourOfParticipant_editingFinished();

    void on_actionEdit_triggered();

    void on_Update_clicked();

    void on_actionDelete_triggered();

    void on_actionSave_triggered();

    void on_actionOpen_triggered();

    void on_actionTutor_s_achievments_triggered();

    void on_endTutName_clicked();

    void on_actionRating_of_the_presenters_triggered();

    void on_actionSeason_s_winner_triggered();

    void on_seasonInputDone_clicked();

    void on_actionTour_s_participants_triggered();

    void on_OK1_clicked();

    void on_OK2_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
