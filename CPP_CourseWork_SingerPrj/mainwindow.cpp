#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "functions.h"

void** start=InitArray();

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setgolos(start);
    ui->stackedWidget->setVisible(0);
    ui->Cancel->setVisible(0);
    ui->Update->setVisible(0);
    ui->Save->setVisible(0);
    ui->treeWidget->setHeaderHidden(1);
    show_list();
}

MainWindow::~MainWindow()
{
    delete ui;
}

int get_item_level(QTreeWidgetItem *item);

void MainWindow::on_treeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    on_Cancel_clicked();
    if(get_item_level(item)==0){
        ui->stackedWidget->setCurrentIndex(0);
        int pos;bool ok;
        FindElListGolos(start,item->text(column),pos,ok);
        ui->CountryName->setText(((golos*)start[pos])->country);
        ui->CountryName->setReadOnly(1);
        ui->ChannelName->setText(((golos*)start[pos])->channel);
        ui->ChannelName->setReadOnly(1);
    }
    else if(get_item_level(item)==1){
        void **next=((golos*)start[0])->sublevel;
        ui->stackedWidget->setCurrentIndex(1);
        int pos;bool ok;
        FindElListSeason(next,item->text(column).toInt(),pos,ok);
        ui->YearOfSeason->setText(QString::number(((season*)next[pos])->year));
        ui->YearOfSeason->setReadOnly(1);
        ui->Presenter1->setText(((season*)next[pos])->pres1);
        ui->Presenter1->setReadOnly(1);
        ui->Presenter2->setText(((season*)next[pos])->pres2);
        ui->Presenter2->setReadOnly(1);
        ui->NumberOfTours->setText(QString::number(((season*)next[pos])->count_tours));
        ui->NumberOfTours->setReadOnly(1);
    }
    else if(get_item_level(item)==2){
        ui->stackedWidget->setCurrentIndex(2);
        QString season_name=item->parent()->text(0);
        int pos;bool ok;
        FindElListSeason(((golos*)start[0])->sublevel,season_name.toInt(),pos,ok);
        void** start_season=((golos*)start[0])->sublevel;
        void** start_tutor=((season*)start_season[pos])->sublevel;
        FindElListTutor(start_tutor,item->text(0),pos,ok);
        ui->NameOfTutor->setText(((tutor*)start_tutor[pos])->name);
        ui->NameOfTutor->setReadOnly(1);
        ui->YearOfBirth->setText(QString::number(((tutor*)start_tutor[pos])->year));
        ui->YearOfBirth->setReadOnly(1);
        if(((tutor*)start_tutor[pos])->is_man==1){
            ui->isMan->setChecked(1);
            ui->isWoman->setChecked(0);
        }
        else{
            ui->isMan->setChecked(0);
            ui->isWoman->setChecked(1);
        }
    }
    else if(get_item_level(item)==3){
        ui->stackedWidget->setCurrentIndex(3);
        QString tutor_name=item->parent()->text(0);
        int season_name=item->parent()->parent()->text(0).toInt();
        int pos;bool ok;
        FindElListSeason(((golos*)start[0])->sublevel,season_name,pos,ok);
        void** start_season=((golos*)start[0])->sublevel;
        void** start_tutor=((season*)start_season[pos])->sublevel;
        int pos_new;
        FindElListTutor(start_tutor,tutor_name,pos_new,ok);
        void** start_part=(((tutor*)start_tutor[pos_new])->sublevel);
        int true_pos;
        FindElListParticipant(start_part,item->text(0),true_pos,ok);
        ui->NameOfPart->setText(((part*)start_part[true_pos])->name);
        ui->NameOfPart->setReadOnly(1);
        ui->PlaceOfResidence->setText(((part*)start_part[true_pos])->place);
        ui->PlaceOfResidence->setReadOnly(1);
        ui->YearOfBirthPart->setText(QString::number(((part*)start_part[true_pos])->year));
        ui->YearOfBirthPart->setReadOnly(1);
        ui->TourOfParticipant->setText(QString::number(((part*)start_part[true_pos])->tour));
        ui->TourOfParticipant->setReadOnly(1);
        if(((part*)start_part[true_pos])->win_place!=0){
            ui->part_place->setText(QString::number(((part*)start_part[true_pos])->win_place));
            ui->part_place->setVisible(1);
            ui->part_place->setReadOnly(1);
        }
        else ui->part_place->setText("0");
    }
    ui->stackedWidget->setVisible(1);


}



void MainWindow::on_actionAdd_triggered()
{

    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    int level=get_item_level(item);
    if(level==0){
        ui->Cancel->setVisible(1);
        ui->Save->setVisible(1);
        ui->stackedWidget->setCurrentIndex(1);
        ui->YearOfSeason->clear();
        ui->YearOfSeason->setReadOnly(0);
        ui->Presenter1->clear();
        ui->Presenter1->setReadOnly(0);
        ui->Presenter2->clear();
        ui->Presenter2->setReadOnly(0);
        ui->NumberOfTours->clear();
        ui->NumberOfTours->setReadOnly(0);
    }
    else if(level==1){
        ui->Cancel->setVisible(1);
        ui->Save->setVisible(1);
        ui->stackedWidget->setCurrentIndex(2);
        ui->NameOfTutor->clear();
        ui->NameOfTutor->setReadOnly(0);
        ui->YearOfBirth->clear();
        ui->YearOfBirth->setReadOnly(0);
        ui->isMan->setChecked(1);
        ui->isWoman->setChecked(0);
    }
    else if(level==2){
        ui->Cancel->setVisible(1);
        ui->Save->setVisible(1);
        ui->stackedWidget->setCurrentIndex(3);
        ui->NameOfPart->clear();
        ui->NameOfPart->setReadOnly(0);
        ui->YearOfBirthPart->clear();
        ui->YearOfBirthPart->setReadOnly(0);
        ui->TourOfParticipant->clear();
        ui->TourOfParticipant->setReadOnly(0);
        ui->part_place->setVisible(0);
        ui->part_place->clear();
        ui->part_place->setReadOnly(0);
        ui->PlaceOfResidence->setReadOnly(0);
        ui->PlaceOfResidence->clear();
    }

}


int get_item_level(QTreeWidgetItem *item){
    if(!item->parent())return 0;
    else if(!item->parent()->parent())return 1;
    else if(!item->parent()->parent()->parent())return 2;
    else if(!item->parent()->parent()->parent()->parent())return 3;
}

void MainWindow::show_list(){
    ui->treeWidget->clear();
    for(int i = 0;i<((int*)start)[POS_CNT];i++){
        void** start_season=((golos*)start[i])->sublevel;
        QTreeWidgetItem* a=new QTreeWidgetItem;
        a->setText(0,((golos*)start[i])->country);


        for(int j = 0;j<((int*)start_season)[POS_CNT];j++){
            void** start_tutor=((season*)start_season[j])->sublevel;
            QTreeWidgetItem* b=new QTreeWidgetItem;
            b->setText(0,QString::number(((season*)start_season[j])->year));


            for(int k = 0;k < ((int*)start_tutor)[POS_CNT];k++){
                void** start_participant=((tutor*)start_tutor[k])->sublevel;
                QTreeWidgetItem* c=new QTreeWidgetItem;
                c->setText(0,((tutor*)start_tutor[k])->name);


                for(int l = 0;l < ((int*)start_participant)[POS_CNT];l++){
                    QTreeWidgetItem* d=new QTreeWidgetItem;
                    d->setText(0,((part*)start_participant[l])->name);
                    c->addChild(d);
                }
                b->addChild(c);
            }
            a->addChild(b);
        }
        ui->treeWidget->addTopLevelItem(a);
    }
}

void MainWindow::on_Cancel_clicked()
{
    ui->stackedWidget->setVisible(0);
    ui->Cancel->setVisible(0);
    ui->Save->setVisible(0);
    ui->Update->setVisible(0);
    ui->treeWidget->expandAll();
}

void MainWindow::on_Save_clicked()
{
    if(ui->stackedWidget->currentIndex()==1){
        if(ui->YearOfSeason->text()=="" || ui->Presenter1->text()=="" || ui->Presenter2->text()=="" || ui->NumberOfTours->text()==""){
            QMessageBox().warning(this,"Warning","All lines must be filled!");
            on_Cancel_clicked();
            return;
        }
        bool ok;
        int pos;
        void* pnew=new season;
        QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
        if (!re.exactMatch(ui->YearOfSeason->text()) || !re.exactMatch(ui->NumberOfTours->text())){
            QMessageBox().warning(this,"Warning","Your input data is incorrect!");
            on_Cancel_clicked();
            return;
        }
        ((season*)pnew)->year=ui->YearOfSeason->text().toInt();
        ((season*)pnew)->pres1=ui->Presenter1->text();
        ((season*)pnew)->pres2=ui->Presenter2->text();
        ((season*)pnew)->count_tours=ui->NumberOfTours->text().toInt();
        ((season*)pnew)->sublevel=InitArray();
        FindElListSeason(((golos*)start[0])->sublevel,(((season*)pnew)->year),pos,ok);
        if(ok){
            QMessageBox().warning(this,"Warning","This season is already exist!");
            on_Cancel_clicked();
            return;
        }

        addToSort(((golos*)start[0])->sublevel,pnew,pos);
        show_list();
        on_Cancel_clicked();
    }
    else if(ui->stackedWidget->currentIndex()==2){
        if(ui->YearOfBirth->text()=="" || ui->NameOfTutor->text()==""){
            QMessageBox().warning(this,"Warning","All lines must be filled!");
            on_Cancel_clicked();
            return;
        }
        bool ok;
        int pos;
        void* pnew=new tutor;
        QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
        if (!re.exactMatch(ui->YearOfBirth->text())){
            QMessageBox().warning(this,"Warning","Your input data is incorrect!");
            on_Cancel_clicked();
            return;
        }
        QTreeWidgetItem *item = ui->treeWidget->currentItem();
        int YearOfseason=item->text(0).toInt();
        ((tutor*)pnew)->year=ui->YearOfBirth->text().toInt();
        ((tutor*)pnew)->name=ui->NameOfTutor->text();
        if(ui->isMan->isChecked()==1)
            ((tutor*)pnew)->is_man=1;
        else ((tutor*)pnew)->is_man=0;
        ((tutor*)pnew)->sublevel=InitArray();
        FindElListSeason(((golos*)start[0])->sublevel,YearOfseason,pos,ok);
        int newpos;
        FindElListTutor(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel,((tutor*)pnew)->name,newpos,ok);
        if(ok){
            QMessageBox().warning(this,"Warning","This tutor is already exist!");
            on_Cancel_clicked();
            return;
        }
        void** check=((season*)(((golos*)start[0])->sublevel)[pos])->sublevel;
        if(((int*)check)[POS_CNT]==4){
            QMessageBox().warning(this,"Warning","!n every season there were only 4 tutors!");
            on_Cancel_clicked();
            return;
        }
        addToSort(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel,pnew,newpos);
        show_list();
        on_Cancel_clicked();
    }
    else if(ui->stackedWidget->currentIndex()==3){
        QTreeWidgetItem *item = ui->treeWidget->currentItem();
        int grand=item->parent()->text(0).toInt();
        bool ok;
        int pos;
        FindElListSeason(((golos*)start[0])->sublevel,grand,pos,ok);
        if(ui->TourOfParticipant->text().toInt(0) == ((season*)(((golos*)start[0])->sublevel)[pos])->count_tours && (ui->part_place->text().toInt()!=1 && ui->part_place->text().toInt()!=2)){
            QMessageBox().warning(this,"Warning","In this tour you have places 1 or 2!");
            on_Cancel_clicked();
            return;
        }
        if(((ui->TourOfParticipant->text().toInt(0)) == ((((season*)(((golos*)start[0])->sublevel)[pos])->count_tours) - 1 ) )&& (ui->part_place->text().toInt()!=3 && ui->part_place->text().toInt()!=4)){
            QMessageBox().warning(this,"Warning","In this tour you have places 3 or 4!");
            on_Cancel_clicked();
            return;
        }
        if(ui->TourOfParticipant->text().toInt(0) > ((season*)(((golos*)start[0])->sublevel)[pos])->count_tours){
            QMessageBox().warning(this,"Warning","In this season you have less tours!");
            on_Cancel_clicked();
            return;
        }
        if(ui->YearOfBirthPart->text()=="" || ui->NameOfPart->text()==""|| ui->TourOfParticipant->text()==""){
            QMessageBox().warning(this,"Warning","All lines must be filled!");
            on_Cancel_clicked();
            return;
        }
        QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
        if (!re.exactMatch(ui->YearOfBirthPart->text()) || !re.exactMatch(ui->part_place->text())){
            QMessageBox().warning(this,"Warning","Your input data is incorrect!");
            on_Cancel_clicked();
            return;
        }
        QString par=item->text(0);
        int pos_tut;
        FindElListTutor(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel,par,pos_tut,ok);
        int true_pos;
        FindElListParticipant(((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[pos_tut])->sublevel,ui->NameOfPart->text(),true_pos,ok);
        if(ok){
            QMessageBox().warning(this,"Warning","This participant is already exist!");
            on_Cancel_clicked();
            return;
        }
        void* pnew=new part;
        ((part*)pnew)->name=ui->NameOfPart->text();
        ((part*)pnew)->year=ui->YearOfBirthPart->text().toInt();
        ((part*)pnew)->place=ui->PlaceOfResidence->text();
        ((part*)pnew)->tour=ui->TourOfParticipant->text().toInt();
        ((part*)pnew)->win_place=ui->part_place->text().toInt();
        for(int j=0;j<((int*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel))[POS_CNT];j++){
            for(int i=0;i<((int*)(((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[j])->sublevel))[POS_CNT];i++){
                if(((part*)(((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[j])->sublevel)[i])->win_place==ui->part_place->text().toInt(0) && ui->part_place->text().toInt(0)!=0){
                    QMessageBox().warning(this,"Warning","In season this place is exists!");
                    on_Cancel_clicked();
                    return;
                }
            }
        }
        addToSort(((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[pos_tut])->sublevel,pnew,true_pos);
        show_list();
        on_Cancel_clicked();
    }
    return;
}


void MainWindow::on_isMan_clicked()
{
    ui->isWoman->setChecked(0);
}

void MainWindow::on_isWoman_clicked()
{
    ui->isMan->setChecked(0);
}

void MainWindow::on_TourOfParticipant_editingFinished()
{
    QTreeWidgetItem *item = ui->treeWidget->currentItem();
    QString grand=item->parent()->text(0);
    if(get_item_level(item)==2)grand=item->parent()->text(0);
    else if(get_item_level(item)==3)grand=item->parent()->parent()->text(0);
    bool ok;
    int pos;
    FindElListSeason(((golos*)start[0])->sublevel,grand.toInt(),pos,ok);
    if(ui->TourOfParticipant->text().toInt(0) == ((season*)(((golos*)start[0])->sublevel)[pos])->count_tours  || (ui->TourOfParticipant->text().toInt(0) == ((season*)(((golos*)start[0])->sublevel)[pos])->count_tours - 1) && ui->TourOfParticipant->text()!=""){
        ui->part_place->setVisible(1);
    }
    else {
        ui->part_place->setText("0");
        ui->part_place->setVisible(0);

    }
}

void MainWindow::on_actionEdit_triggered()
{   QTreeWidgetItem* item=ui->treeWidget->currentItem();
    int level=get_item_level(item);
    if(level==0){
        ui->Cancel->setVisible(1);
        ui->Update->setVisible(1);
        ui->stackedWidget->setCurrentIndex(0);
        ui->stackedWidget->setVisible(1);
        ui->CountryName->setReadOnly(0);
        ui->ChannelName->setReadOnly(0);
    }
    else if(level==1){
        ui->Cancel->setVisible(1);
        ui->Update->setVisible(1);
        ui->stackedWidget->setCurrentIndex(1);
        ui->stackedWidget->setVisible(1);
        ui->YearOfSeason->setReadOnly(0);
        ui->Presenter1->setReadOnly(0);
        ui->Presenter2->setReadOnly(0);
        ui->NumberOfTours->setReadOnly(0);
    }
    else if(level==2){
        ui->Cancel->setVisible(1);
        ui->Update->setVisible(1);
        ui->stackedWidget->setCurrentIndex(2);
        ui->stackedWidget->setVisible(1);
        ui->NameOfTutor->setReadOnly(0);
        ui->YearOfBirth->setReadOnly(0);
    }
    else if(level==3){
        ui->Cancel->setVisible(1);
        ui->Update->setVisible(1);
        ui->stackedWidget->setCurrentIndex(3);
        ui->stackedWidget->setVisible(1);
        ui->NameOfPart->setReadOnly(0);
        ui->YearOfBirthPart->setReadOnly(0);
        ui->PlaceOfResidence->setReadOnly(0);
        ui->TourOfParticipant->setReadOnly(0);
        ui->part_place->setVisible(0);
        ui->part_place->setReadOnly(0);
    }
}

void MainWindow::on_Update_clicked()
{
    if(ui->stackedWidget->currentIndex()==0){
        if(ui->ChannelName->text()=="" || ui->CountryName->text()==""){
            QMessageBox().warning(this,"Warning","All lines must be filled!");
            on_Cancel_clicked();
            return;
        }
        ((golos*)start[0])->channel=ui->ChannelName->text();
        ((golos*)start[0])->country=ui->CountryName->text();
        show_list();
        on_Cancel_clicked();
    }


    if(ui->stackedWidget->currentIndex()==1){
        QTreeWidgetItem* item=ui->treeWidget->currentItem();
        int year=item->text(0).toInt();
        int pos;bool ok;
        if(ui->YearOfSeason->text()=="" || ui->Presenter1->text()=="" || ui->Presenter2->text()=="" || ui->NumberOfTours->text()==""){
            QMessageBox().warning(this,"Warning","All lines must be filled!");
            on_Cancel_clicked();
            return;
        }
        QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
        if (!re.exactMatch(ui->YearOfSeason->text()) || !re.exactMatch(ui->NumberOfTours->text())){
            QMessageBox().warning(this,"Warning","Your input data is incorrect!");
            on_Cancel_clicked();
            return;
        }
        FindElListSeason(((golos*)start[0])->sublevel,year,pos,ok);
        int useless;
        FindElListSeason(((golos*)start[0])->sublevel,ui->YearOfSeason->text().toInt(),useless,ok);
        if(ok && ui->YearOfSeason->text()!=ui->treeWidget->currentItem()->text(0)){
            QMessageBox().warning(this,"Warning","This season is already exist!");
            on_Cancel_clicked();
            return;
        }
        ((season*)(((golos*)start[0])->sublevel)[pos])->year=ui->YearOfSeason->text().toInt();
        ((season*)(((golos*)start[0])->sublevel)[pos])->count_tours=ui->NumberOfTours->text().toInt();
        ((season*)(((golos*)start[0])->sublevel)[pos])->pres1=ui->Presenter1->text();
        ((season*)(((golos*)start[0])->sublevel)[pos])->pres2=ui->Presenter2->text();
        void *pnew=((season*)(((golos*)start[0])->sublevel)[pos]);
        int cnt=((int*)(((golos*)start[0])->sublevel))[POS_CNT];
        if (pos == cnt-1){
            (((golos*)start[0])->sublevel)[pos]=NULL;
        }
        else if(pos==0){
            for(int i=0;i<cnt;i++){
                (((golos*)start[0])->sublevel)[i]=(((golos*)start[0])->sublevel)[i+1];
            }
        }
        else{
            for(int i=pos;i<cnt;i++){
                (((golos*)start[0])->sublevel)[i]=(((golos*)start[0])->sublevel)[i+1];
            }
        }
        cnt-=1;
        ((int*)(((golos*)start[0])->sublevel))[POS_CNT]=cnt;
        FindElListSeason(((golos*)start[0])->sublevel,((season*)pnew)->year,pos,ok);
        addToSort(((golos*)start[0])->sublevel,pnew,pos);
        show_list();
        on_Cancel_clicked();
    }


    if(ui->stackedWidget->currentIndex()==2){
        QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
        if (!re.exactMatch(ui->YearOfBirth->text())){
            QMessageBox().warning(this,"Warning","Your input data is incorrect!");
            on_Cancel_clicked();
            return;
        }
        if(ui->YearOfBirth->text()=="" || ui->NameOfTutor->text()==""){
            QMessageBox().warning(this,"Warning","All lines must be filled!");
            on_Cancel_clicked();
            return;
        }
        int pos;bool ok;
        QTreeWidgetItem *item = ui->treeWidget->currentItem()->parent();
        int YearOfseason=item->text(0).toInt();
        FindElListSeason(((golos*)start[0])->sublevel,YearOfseason,pos,ok);
        int newpos;
        FindElListTutor(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel,ui->NameOfTutor->text(),newpos,ok);
        if(ok && ui->NameOfTutor->text()!=ui->treeWidget->currentItem()->text(0)){
            QMessageBox().warning(this,"Warning","This tutor is already exist!");
            on_Cancel_clicked();
            return;
        }
        FindElListTutor(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel,item->text(0),newpos,ok);
        void* pnew=((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[newpos]);
        ((tutor*)pnew)->name=ui->NameOfTutor->text();
        ((tutor*)pnew)->year=ui->YearOfBirth->text().toInt();
        if(ui->isMan->isChecked()) {
            ((tutor*)pnew)->is_man=1;}
        else ((tutor*)pnew)->is_man=0;

        int cnt=((int*)((((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)))[POS_CNT];
        if (newpos == cnt-1){
            ((season*)(((golos*)start[0])->sublevel)[pos])->sublevel[newpos]=NULL;
        }
        else if(newpos==0){
            for(int i=0;i<cnt;i++){
                ((season*)(((golos*)start[0])->sublevel)[pos])->sublevel[i]=((season*)(((golos*)start[0])->sublevel)[pos])->sublevel[i+1];
            }
        }
        else{
            for(int i=newpos;i<cnt;i++){
                ((season*)(((golos*)start[0])->sublevel)[pos])->sublevel[i]=((season*)(((golos*)start[0])->sublevel)[pos])->sublevel[i+1];
            }
        }
        cnt-=1;
        ((int*)((((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)))[POS_CNT]=cnt;
        int new_pos;
        FindElListTutor(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel,((tutor*)pnew)->name,new_pos,ok);
        addToSort(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel,pnew,new_pos);
        show_list();
        on_Cancel_clicked();
    }


    if(ui->stackedWidget->currentIndex()==3){
        QRegExp re("\\d*");  // a digit (\d), zero or more times (*)
        if (!re.exactMatch(ui->YearOfBirthPart->text()) || !re.exactMatch(ui->part_place->text())){
            QMessageBox().warning(this,"Warning","Your input data is incorrect!");
            on_Cancel_clicked();
            return;
        }
        if(ui->YearOfBirthPart->text()=="" || ui->NameOfPart->text()=="" || ui->PlaceOfResidence->text()=="" || ui->TourOfParticipant->text()==""){
            QMessageBox().warning(this,"Warning","All lines must be filled!");
            on_Cancel_clicked();
            return;
        }

        QTreeWidgetItem *item = ui->treeWidget->currentItem();
        int grand=item->parent()->parent()->text(0).toInt();
        bool ok;
        int pos;
        FindElListSeason(((golos*)start[0])->sublevel,grand,pos,ok);
        if(ui->TourOfParticipant->text().toInt(0) == ((season*)(((golos*)start[0])->sublevel)[pos])->count_tours && (ui->part_place->text().toInt(0)!=1 && ui->part_place->text().toInt(0)!=2)){
            QMessageBox().warning(this,"Warning","In this tour you have places 1 or 2!");
            on_Cancel_clicked();
            return;
        }
        if((ui->TourOfParticipant->text().toInt(0)-1) == ((season*)(((golos*)start[0])->sublevel)[pos])->count_tours && (ui->part_place->text().toInt(0)!=3 && ui->part_place->text().toInt(0)!=4)){
            QMessageBox().warning(this,"Warning","In this tour you have places 3 or 4!");
            on_Cancel_clicked();
            return;
        }
        if(ui->TourOfParticipant->text().toInt(0) > ((season*)(((golos*)start[0])->sublevel)[pos])->count_tours){
            QMessageBox().warning(this,"Warning","In this season you have less tours!");
            on_Cancel_clicked();
            return;
        }
        int pos_tut;
        FindElListTutor(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel,item->parent()->text(0),pos_tut,ok);
        int true_pos;
        FindElListParticipant(((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[pos_tut])->sublevel,ui->NameOfPart->text(),true_pos,ok);
        if(ok && ui->NameOfPart->text()!=ui->treeWidget->currentItem()->text(0)){
            QMessageBox().warning(this,"Warning","This participant is already exist!");
            on_Cancel_clicked();
            return;
        }
        void* pnew=((((part*)(((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[pos_tut])->sublevel)[true_pos])));
        if(ui->part_place->text().toInt()!=0){
            for(int j=0;j<((int*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel))[POS_CNT];j++){
                for(int i=0;i<((int*)(((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[j])->sublevel))[POS_CNT];i++){
                    if(((part*)(((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[j])->sublevel)[i])->win_place==ui->part_place->text().toInt(0) && ui->part_place->text().toInt(0)!=0){
                        QMessageBox().warning(this,"Warning","In season this place is exists!");
                        on_Cancel_clicked();
                        return;
                    }

                }
            }
        }
        ((part*)pnew)->name=ui->NameOfPart->text();
        ((part*)pnew)->place=ui->PlaceOfResidence->text();
        ((part*)pnew)->year=ui->YearOfBirthPart->text().toInt();
        ((part*)pnew)->tour=ui->TourOfParticipant->text().toInt();
        ((part*)pnew)->win_place=ui->part_place->text().toInt();



        int cnt=((int*)(((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[pos_tut])->sublevel))[POS_CNT];
        if (true_pos == cnt-1){
            ((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[pos_tut])->sublevel[true_pos]=NULL;
        }
        else if(true_pos==0){
            for(int i=0;i<cnt;i++){
                ((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[pos_tut])->sublevel[i]=((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[pos_tut])->sublevel[i+1];
            }
        }
        else{
            for(int i=true_pos;i<cnt;i++){
                ((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[pos_tut])->sublevel[i]=((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[pos_tut])->sublevel[i+1];
            }
        }
        cnt-=1;
        ((int*)(((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[pos_tut])->sublevel))[POS_CNT]=cnt;
        FindElListParticipant(((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[pos_tut])->sublevel,ui->NameOfPart->text(),true_pos,ok);
        addToSort(((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[pos_tut])->sublevel,pnew,true_pos);
        show_list();
        on_Cancel_clicked();
    }
}

void MainWindow::on_actionDelete_triggered()
{
    int level=get_item_level(ui->treeWidget->currentItem());
    if(level==1){
        bool ok;
        int pos;
        FindElListSeason(((golos*)start[0])->sublevel,ui->treeWidget->currentItem()->text(0).toInt(),pos,ok);
        delElListSeason(((golos*)start[0])->sublevel,pos);
        show_list();
        on_Cancel_clicked();
    }
    else if(level==2){
        int father=ui->treeWidget->currentItem()->parent()->text(0).toInt();
        bool ok;
        int pos;
        FindElListSeason(((golos*)start[0])->sublevel,father,pos,ok);
        int pos_tut;
        FindElListTutor(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel,ui->treeWidget->currentItem()->text(0),pos_tut,ok);
        delElListTutor(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel,pos_tut);
        show_list();
        on_Cancel_clicked();
    }
    else if(level==3){
        int grand=ui->treeWidget->currentItem()->parent()->parent()->text(0).toInt();
        bool ok;
        int pos;
        FindElListSeason(((golos*)start[0])->sublevel,grand,pos,ok);
        int pos_tut;
        FindElListTutor(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel,ui->treeWidget->currentItem()->parent()->text(0),pos_tut,ok);
        int true_pos;
        FindElListParticipant(((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[pos_tut])->sublevel,ui->treeWidget->currentItem()->text(0),true_pos,ok);
        delElListParticipant(((tutor*)(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel)[pos_tut])->sublevel,true_pos);
        show_list();
        on_Cancel_clicked();
    }
}

FILE* openFileForWrite(){
    QString fileName = QFileDialog::getSaveFileName(NULL,
                                                    QString::fromUtf8("Choose fileName for Tree"),
                                                    QDir::currentPath(),"(*.*)");
    char *fName = (char*) qPrintable(fileName);
    FILE *fp = fopen(fName,"w+b");
    if(fp==NULL){
        QErrorMessage errorMessage;
        errorMessage.showMessage(fileName+" File open Error");
        errorMessage.exec();
        return NULL;
    }
    return fp;
}

void saveTree(void** &start){
    FILE *fp=openFileForWrite();
    if( fp==NULL) return;
    fgolos g;
    fseason s;
    ftutor t;
    fpart p;
    const char* l;
    int cnt_seasons=((int*)(((golos*)start[0])->sublevel))[POS_CNT];
    l=((golos*)start[0])->country.toStdString().c_str();
    strncpy(g.country,l,29);
    l=((golos*)start[0])->channel.toStdString().c_str();
    strncpy(g.channel,l,29);
    g.child=cnt_seasons;
    fwrite(&g,sizeof(fgolos),1,fp);
    for(int i=0;i<cnt_seasons;i++){
        void** tutor_level= (((season*)((golos*)start[0])->sublevel[i])->sublevel);
        int cnt_tutors=((int*)tutor_level)[POS_CNT];
        s.year=((season*)(((golos*)start[0])->sublevel)[i])->year;
        l=((season*)(((golos*)start[0])->sublevel)[i])->pres1.toStdString().c_str();
        strncpy(s.pres1,l,29);
        l=((season*)(((golos*)start[0])->sublevel)[i])->pres2.toStdString().c_str();
        strncpy(s.pres2,l,29);
        s.count_tours=((season*)(((golos*)start[0])->sublevel)[i])->count_tours;
        s.child=cnt_tutors;
        fwrite(&s,sizeof(fseason),1,fp);
        for(int j=0;j<cnt_tutors;j++){
            void** part_level= (((tutor*)tutor_level[j])->sublevel);
            int cnt_part=((int*)part_level)[POS_CNT];
            l=((tutor*)(((season*)(((golos*)start[0])->sublevel)[i])->sublevel)[j])->name.toStdString().c_str();
            strncpy(t.name,l,29);
            t.year=((tutor*)(((season*)(((golos*)start[0])->sublevel)[i])->sublevel)[j])->year;
            t.is_man=((tutor*)(((season*)(((golos*)start[0])->sublevel)[i])->sublevel)[j])->is_man;
            t.child=cnt_part;
            fwrite(&t,sizeof(ftutor),1,fp);
            for(int k=0;k<cnt_part;k++){
                l=((part*)(((tutor*)(((season*)(((golos*)start[0])->sublevel)[i])->sublevel)[j])->sublevel)[k])->name.toStdString().c_str();
                strncpy(p.name,l,29);
                l=((part*)(((tutor*)(((season*)(((golos*)start[0])->sublevel)[i])->sublevel)[j])->sublevel)[k])->place.toStdString().c_str();
                strncpy(p.place,l,29);
                p.year=((part*)(((tutor*)(((season*)(((golos*)start[0])->sublevel)[i])->sublevel)[j])->sublevel)[k])->year;
                p.tour=((part*)(((tutor*)(((season*)(((golos*)start[0])->sublevel)[i])->sublevel)[j])->sublevel)[k])->tour;
                p.win_place=((part*)(((tutor*)(((season*)(((golos*)start[0])->sublevel)[i])->sublevel)[j])->sublevel)[k])->win_place;
                fwrite(&p,sizeof(fpart),1,fp);
            }
        }
    }
    fclose(fp);
}

void MainWindow::on_actionSave_triggered()
{
    saveTree(start);
}

FILE* openFileForRead(){
    QString fileName = QFileDialog::getOpenFileName(NULL,
                                                    QString::fromUtf8("Choose fileName for Tree"),
                                                    QDir::currentPath(),"(*.*)");
    char *fName = (char*) qPrintable(fileName);
    FILE *fp = fopen(fName,"r+b");
    if(fp==NULL){
        QErrorMessage errorMessage;
        errorMessage.showMessage(fileName+" File open Error");
        errorMessage.exec();
        return NULL;
    }
    return fp;

}



void MainWindow::on_actionOpen_triggered()
{
    FILE *fp=openFileForRead();
    if( fp==NULL) return;
    int sc=((int*)(((golos*)start[0])->sublevel))[POS_CNT];
    for(int d=0;d<sc;d++){
        delElListSeason(((golos*)start[0])->sublevel,0);
    }
    start=InitArray();
    fgolos g;
    fseason s;
    ftutor t;
    fpart p;
    void* gnew=new golos;
    fread(&g,sizeof(fgolos),1,fp);
    ((golos*)gnew)->country=QString(g.country);
    ((golos*)gnew)->channel=QString(g.channel);
    ((golos*)gnew)->sublevel=InitArray();
    int cnt_seasons=g.child;
    addToSort(start,gnew,0);
    for(int i=0;i<cnt_seasons;i++){
        void* snew=new season;
        fread(&s,sizeof(fseason),1,fp);
        ((season*)snew)->year=s.year;
        ((season*)snew)->count_tours=s.count_tours;
        ((season*)snew)->pres1=QString(s.pres1);
        ((season*)snew)->pres2=QString(s.pres2);
        ((season*)snew)->sublevel=InitArray();
        int cnt_tutors=s.child;
        addToSort(((golos*)start[0])->sublevel,snew,i);
        for(int j=0;j<cnt_tutors;j++){
            void* tnew=new tutor;
            fread(&t,sizeof(ftutor),1,fp);
            ((tutor*)tnew)->name=QString(t.name);
            ((tutor*)tnew)->is_man=t.is_man;
            ((tutor*)tnew)->year=t.year;
            ((tutor*)tnew)->sublevel=InitArray();
            int cnt_part=t.child;
            addToSort(((season*)(((golos*)start[0])->sublevel)[i])->sublevel,tnew,j);
            for(int k=0;k<cnt_part;k++){
                void* pnew=new part;
                fread(&p,sizeof(fpart),1,fp);
                ((part*)pnew)->name=QString(p.name);
                ((part*)pnew)->place=QString(p.place);
                ((part*)pnew)->tour=p.tour;
                ((part*)pnew)->win_place=p.win_place;
                ((part*)pnew)->year=p.year;
                addToSort(((tutor*)(((season*)(((golos*)start[0])->sublevel)[i])->sublevel)[j])->sublevel,pnew,k);

            }


        }


    }
    fclose(fp);
    show_list();
    on_Cancel_clicked();
}

void MainWindow::on_actionTutor_s_achievments_triggered()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->stackedWidget->setVisible(1);
    ui->winnersTutor->clear();
    ui->winnersTutor->setReadOnly(1);
    ui->tutorSeasons->clear();
    ui->tutorSeasons->setReadOnly(1);
    ui->tutorsNameToInf->clear();
}

void MainWindow::on_endTutName_clicked()
{
    QString tutor_name=ui->tutorsNameToInf->text();
    int count_seasons=0;
    int count_winners=0;
    void** start_season=((golos*)start[0])->sublevel;
    for(int j = 0;j<((int*)start_season)[POS_CNT];j++){
        void** start_tutor=((season*)start_season[j])->sublevel;
        for(int k = 0;k < ((int*)start_tutor)[POS_CNT];k++){
            if(((tutor*)start_tutor[k])->name==tutor_name){
                count_seasons+=1;
                void** start_participant=((tutor*)start_tutor[k])->sublevel;
                for(int l = 0;l < ((int*)start_participant)[POS_CNT];l++){
                    if(((part*)start_participant[l])->win_place==1){count_winners+=1;}
                }
            }
        }
    }
    ui->winnersTutor->setText(QString::number(count_winners));
    ui->tutorSeasons->setText(QString::number(count_seasons));
}

struct rating{
    QString name;
    int count;
};

bool is_pres_exist(QString name, rating ar[],int size, int &pos){
    pos=0;
    for(;pos<size;pos++){
        if(ar[pos].name==name)return 1;
    }
    return 0;
}

void MainWindow::on_actionRating_of_the_presenters_triggered()
{
    ui->stackedWidget->setCurrentIndex(5);
    ui->stackedWidget->setVisible(1);
    ui->rating->clear();
    ui->rating->setReadOnly(1);
    int size=ui->treeWidget->topLevelItem(0)->childCount();
    size*=2;
    rating pres[size];
    size=0;
    for(int i=0;i<ui->treeWidget->topLevelItem(0)->childCount();i++){
        QString n=(((season*)(((golos*)start[0])->sublevel[i]))->pres1);
        int pos=0;
        if(!is_pres_exist(n,pres,size,pos) && n!="N/A"){
            pres[size].name=n;
            pres[size].count=1;
            size++;
        }
        else if(is_pres_exist(n,pres,size,pos) && n==((season*)(((golos*)start[0])->sublevel[i]))->pres2&& n!="N/A"){
            continue;
        }
        else if(is_pres_exist(n,pres,size,pos) && n!=((season*)(((golos*)start[0])->sublevel[i]))->pres2&& n!="N/A"){
            pres[pos].count++;
        }
        n=((season*)(((golos*)start[0])->sublevel[i]))->pres2;
        if(!is_pres_exist(n,pres,size,pos)&& n!="N/A"){
            pres[size].name=n;
            pres[size].count=1;
            size++;
        }
        else if(is_pres_exist(n,pres,size,pos)&& n!="N/A"){
            pres[pos].count++;
            continue;
        }

    }
    for(int i =0;i<size;i++){
        for(int j=i+1;j<size;j++){
            if(pres[i].count<pres[j].count){
                rating tmp=pres[i];
                pres[i]=pres[j];
                pres[j]=tmp;
            }
        }
    }
    QString str;
    for(int i=0;i<size;i++){
        str=str+QString::number(i+1)+" place - "+pres[i].name+", count of seasons - "+QString::number(pres[i].count)+"\n";
    }
    ui->rating->setText(str);
}


void MainWindow::on_actionSeason_s_winner_triggered()
{
    ui->stackedWidget->setCurrentIndex(6);
    ui->stackedWidget->setVisible(1);
    ui->CountOfPart->setReadOnly(1);
    ui->CountOfPart->clear();
    ui->winner->clear();
    ui->winner->setReadOnly(1);
}

void MainWindow::on_seasonInputDone_clicked()
{
    int count=0;
    QString winner="Doesn`t exist!";
    int season_cur=ui->seasonInput->text().toInt();
    int pos;bool ok;
    FindElListSeason(((golos*)start[0])->sublevel,season_cur,pos,ok);
    if(!ok){
        QMessageBox().warning(this,"Warning","This season doesn`t exist!");
        on_Cancel_clicked();
        return;
    }
    void** tutor_start=(((season*)(((golos*)start[0])->sublevel)[pos])->sublevel);
    for(int i=0;i<((int*)tutor_start)[POS_CNT];i++){
        void** part_start=((tutor*)tutor_start[i])->sublevel;
        count+=((int*)part_start)[POS_CNT];
        if(winner=="Doesn`t exist!"){
            for(int j=0;j<((int*)part_start)[POS_CNT];j++){
                if(((part*)part_start[j])->win_place==1){
                    winner=((part*)part_start[j])->name;
                    break;
                }
            }
        }
    }
    ui->winner->setText(winner);
    ui->CountOfPart->setText(QString::number(count));
}

void MainWindow::on_actionTour_s_participants_triggered()
{
    ui->stackedWidget->setCurrentIndex(7);
    ui->stackedWidget->setVisible(1);
    ui->seasonNum->clear();
    ui->seasonNum->setVisible(1);
    ui->OK1->setVisible(1);
    ui->tourNum->clear();
    ui->tourNum->setVisible(0);
    ui->OK2->setVisible(0);
    ui->participants->setReadOnly(1);
}

void MainWindow::on_OK1_clicked()
{
    int season_cur=ui->seasonNum->text().toInt();
    int pos;bool ok;
    FindElListSeason(((golos*)start[0])->sublevel,season_cur,pos,ok);
    if(!ok){
        QMessageBox().warning(this,"Warning","This season doesn`t exist!");
        on_Cancel_clicked();
        return;
    }
    ui->OK2->setVisible(1);
    ui->tourNum->setVisible(1);
    ui->OK1->setVisible(0);
}

void MainWindow::on_OK2_clicked()
{
    int season_cur=ui->seasonNum->text().toInt();
    int pos;bool ok;
    int tour=ui->tourNum->text().toInt();
    FindElListSeason(((golos*)start[0])->sublevel,season_cur,pos,ok);
    if(((season*)(((golos*)start[0])->sublevel)[pos])->count_tours < tour){
        QMessageBox().warning(this,"Warning","This season have less tours!");
        on_Cancel_clicked();
        return;
    }
    QString str="The following participants reached "+QString::number(tour)+" tour:\n";
    void** tutor_level=((season*)(((golos*)start[0])->sublevel)[pos])->sublevel;
    for(int i=0;i < ((int*)tutor_level)[POS_CNT];i++){
        void** part_level=((tutor*)tutor_level[i])->sublevel;
        for(int j=0;j< ((int*)part_level)[POS_CNT];j++){
            if(((part*)part_level[j])->tour >= tour){
                str+=((part*)part_level[j])->name+"\n";
            }
        }
    }
    ui->participants->setText(str);
}

