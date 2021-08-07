#include "functions.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "types.h"

void addToSort(void** &start,  void* pnew, int posAdd)
{
int cnt=((int*)start)[POS_CNT];
int sz= ((int*)start)[POS_SZ];
if (cnt == sz)
        {
        ExpendArrPtr (start, sz, cnt);
        }
 if (posAdd == cnt) //добавляемый элемент располагается в конце списка
        {
        start[posAdd] = pnew;
        cnt+=1;
        }
  else
        {     // сдвиг элементов в массиве указателей на 1 вправо
         for (int k = cnt-1; k >= posAdd; k--)
              {
                  start[k+1] = start[k];}
                  start[posAdd] = pnew;
                  cnt+=1;
               }

 ((int*)start)[POS_CNT]=cnt;

}

void **InitArray(){

    void** p = new void*[SIZE_AT_FIRST+2];
    p+=2;
    ((int*)p)[POS_CNT] = 0;
    ((int*)p)[POS_SZ] = SIZE_AT_FIRST;
    return p;
}

void ExpendArrPtr (void** &ar,int &SizeAr, int Cnt){
    int SizeW=SizeAr;
    void** arW;
    SizeAr+=DELTA;
    arW = new void*[SizeAr+2];
    arW=arW+2;
    ((int*)arW)[POS_CNT] = Cnt;
    ((int*)arW)[POS_SZ] = SizeAr;
    for(int i=0;i<SizeW;i++){
        arW[i]=ar[i];
    }
    delete []ar;
    ar=arW;
}

void setgolos(void ** &Start){
    void *pnew=new golos;
    ((golos*)pnew)->channel="1+1";
    ((golos*)pnew)->country="Ukraine";
    ((golos*)pnew)->sublevel=InitArray();
    int position;
    bool ok;
    FindElListGolos(Start,((golos*)pnew)->country,position,ok);
    addToSort(Start,pnew,position);
}

void FindElListGolos(void** start,  QString key, int &posFndEl, bool &findOK)
{
 int	middl;
 int	 hi, low;
 findOK = false;
 if (((int*)start)[POS_CNT] == 0)
 {
    posFndEl = 0;
    return;
 }
 low = 0;
 hi = (((int*)start)[POS_CNT]) - 1;
 do
 {
    middl = (hi + low) / 2 ; /*индекс среднего элемента*/
     if (key==((golos*)(start[middl]))->country)
        { posFndEl = middl; /*Элемент найден*/
        findOK = true;      /*элемент найден*/
        return;
        }
     if (key<((golos*)(start[middl]))->country)
        {
          hi = middl - 1;
       }
     else
        {
         low = middl + 1;
       }

 } while  (low <= hi);
 posFndEl = low;
}

void FindElListSeason(void** start,  int key, int &posFndEl, bool &findOK)
{
 int	middl;
 int	 hi, low;
 findOK = false;
 if (((int*)start)[POS_CNT] == 0)
 {
    posFndEl = 0;
    return;
 }
 low = 0;
 hi = (((int*)start)[POS_CNT]) - 1;
 do
 {
    middl = (hi + low) / 2 ; /*индекс среднего элемента*/
     if (key==((season*)(start[middl]))->year)
        { posFndEl = middl; /*Элемент найден*/
        findOK = true;      /*элемент найден*/
        return;
        }
     if (key<((season*)(start[middl]))->year)
        {
          hi = middl - 1;
       }
     else
        {
         low = middl + 1;
       }

 } while  (low <= hi);
 posFndEl = low;
}

void FindElListTutor(void** start,  QString key, int &posFndEl, bool &findOK)
{
 int	middl;
 int	 hi, low;
 findOK = false;
 if (((int*)start)[POS_CNT] == 0)
 {
    posFndEl = 0;
    return;
 }
 low = 0;
 hi = (((int*)start)[POS_CNT]) - 1;
 do
 {
    middl = (hi + low) / 2 ; /*индекс среднего элемента*/
     if (key==((tutor*)(start[middl]))->name)
        { posFndEl = middl; /*Элемент найден*/
        findOK = true;      /*элемент найден*/
        return;
        }
     if (key<((tutor*)(start[middl]))->name)
        {
          hi = middl - 1;
       }
     else
        {
         low = middl + 1;
       }

 } while  (low <= hi);
 posFndEl = low;
}

void FindElListParticipant(void** start,  QString key, int &posFndEl, bool &findOK)
{
 int	middl;
 int	 hi, low;
 findOK = false;
 if (((int*)start)[POS_CNT] == 0)
 {
    posFndEl = 0;
    return;
 }
 low = 0;
 hi = (((int*)start)[POS_CNT]) - 1;
 do
 {
    middl = (hi + low) / 2 ; /*индекс среднего элемента*/
     if (key==((part*)(start[middl]))->name)
        { posFndEl = middl; /*Элемент найден*/
        findOK = true;      /*элемент найден*/
        return;
        }
     if (key<((part*)(start[middl]))->name)
        {
          hi = middl - 1;
       }
     else
        {
         low = middl + 1;
       }

 } while  (low <= hi);
 posFndEl = low;
}

void delElListParticipant(void **&start, int pos){
    int cnt=((int*)start)[POS_CNT];
    if (pos == cnt-1){
        delete (part*)start[pos];
        start[pos]=NULL;
    }
    else if(pos==0){
        delete (part*)start[0];
        for(int i=0;i<cnt;i++){
            start[i]=start[i+1];
        }
    }
    else{
            delete (part*)start[pos];
            for(int i=pos;i<cnt;i++){
                start[i]=start[i+1];
            }
    }
    cnt-=1;
    ((int*)start)[POS_CNT]=cnt;
}

void delElListTutor(void **&start, int pos){
    int cnt_part= ((int*)(((tutor*)start[pos])->sublevel))[POS_CNT];
    for(int i = 0; i< cnt_part;i++){
        delElListParticipant(((tutor*)start[pos])->sublevel,0);
    }
    int cnt=((int*)start)[POS_CNT];
    if (pos == cnt-1){
        delete (tutor*)start[pos];
        start[pos]=NULL;
    }
    else if(pos==0){
        delete (tutor*)start[0];
        for(int i=0;i<cnt;i++){
            start[i]=start[i+1];
        }
    }
    else{
            delete (tutor*)start[pos];
            for(int i=pos;i<cnt;i++){
                start[i]=start[i+1];
            }
    }
    cnt-=1;
    ((int*)start)[POS_CNT]=cnt;
}

void delElListSeason(void **&start, int pos){
    int cnt_tutor= ((int*)(((season*)start[pos])->sublevel))[POS_CNT];
    for(int i = 0; i< cnt_tutor;i++){
        delElListTutor(((season*)start[pos])->sublevel,0);
    }
    int cnt=((int*)start)[POS_CNT];
    if (pos == cnt-1){
        delete (season*)start[pos];
        start[pos]=NULL;
    }
    else if(pos==0){
        delete (season*)start[0];
        for(int i=0;i<cnt;i++){
            start[i]=start[i+1];
        }
    }
    else{
            delete (season*)start[pos];
            for(int i=pos;i<cnt;i++){
                start[i]=start[i+1];
            }
    }
    cnt-=1;
    ((int*)start)[POS_CNT]=cnt;
}

