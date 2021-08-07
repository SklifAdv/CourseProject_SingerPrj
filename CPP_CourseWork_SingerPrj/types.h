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
struct par{//��᭨�
    QString name;//?�'� ��᭨��
    int year;//�?� ��த�����
    QString place;//�?�� �஦������
    int tour;//���, �� 类�� �?�订
    int win_place;//�ਧ��� �?��

}part;

typedef
struct tut{//�७��
    QString name;//?�'� �७��
    int year;//�?� ��த�����
    bool is_man;//�� � 箫��?�� ���?
    void **sublevel;//����-����?���� �� ���ᨢ ����?����?�
}tutor;

typedef
struct sea{//�����
    int year;//�?� �஢������
    QString pres1;//����稩 �1
    QString pres2;//����稩 �2
    int count_tours;//�?��?��� ���?�
    void **sublevel;//����-����?���� �� ���ᨢ ����?����?�
}season;

typedef
struct gol{//����� �����
    QString country;//����� �஢������
    QString channel;//����� �࠭���?�
    void **sublevel;//����-����?���� �� ���ᨢ ����?����?�
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
