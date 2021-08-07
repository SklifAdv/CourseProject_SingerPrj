#ifndef TYPES_H
#define TYPES_H
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QErrorMessage>
using namespace std;

typedef
struct par{//Учасник
    QString name;//?м'я учасника
    int year;//Р?к народження
    QString place;//М?сце проживання
    int tour;//Тур, до якого д?йшов
    int win_place;//Призове м?сце

}part;

typedef
struct tut{//Тренер
    QString name;//?м'я тренера
    int year;//Р?к народження
    bool is_man;//Чи є чолов?чої стат?
    void **sublevel;//Поле-вказ?вник на массив вказ?вник?в
}tutor;

typedef
struct sea{//Сезон
    int year;//Р?к проведення
    QString pres1;//Ведучий №1
    QString pres2;//Ведучий №2
    int count_tours;//К?льк?сть тур?в
    void **sublevel;//Поле-вказ?вник на массив вказ?вник?в
}season;

typedef
struct gol{//Голос країни
    QString country;//Країна проведення
    QString channel;//Канал трансляц?ї
    void **sublevel;//Поле-вказ?вник на массив вказ?вник?в
}golos;

typedef
struct par_f{
    char name[30];
    int year;
    char place[30];
    int tour;
    int win_place;
}fpart;

typedef
struct tut_f{
    char name[30];
    int year;
    bool is_man;
    int child;
}ftutor;

typedef
struct sea_f{
    int year;
    char pres1[30];
    char pres2[30];
    int count_tours;
    int child;
}fseason;

typedef
struct gol_f{
    char country[30];
    char channel[30];
    int child;
}fgolos;

#endif // TYPES_H
