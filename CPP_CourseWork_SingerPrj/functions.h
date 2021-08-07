#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include "types.h"

const int POS_CNT = -1;
const int POS_SZ = -2;
const int DELTA = 2;
const int SIZE_AT_FIRST=2;


void ExpendArrPtr (void** &ar,int &SizeAr, int Cnt);
void **InitArray();
void addToSort(void** &start,  void* pnew, int posAdd);
void FindElListGolos(void** start,  QString key, int &posFndEl, bool &findOK);
void setgolos(void ** &Start);
void FindElListSeason(void** start,  int key, int &posFndEl, bool &findOK);
void FindElListTutor(void** start,  QString key, int &posFndEl, bool &findOK);
void FindElListParticipant(void** start,  QString key, int &posFndEl, bool &findOK);
void delElListParticipant(void **&start, int pos);
void delElListTutor(void **&start, int pos);
void delElListSeason(void **&start, int pos);

#endif // FUNCTIONS_H
