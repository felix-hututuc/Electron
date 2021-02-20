#pragma once

#include "structuri.h"

extern float zoom;
extern piesa Meniu[MAX1];
extern const int nrPieseMeniu;
extern float zoomMen;


void initializeaza(piesa& P);
void roteste (float x, float y, float & xnou, float & ynou);
void amplaseaza(piesa& P, unsigned x, unsigned y, unsigned orient);
void deseneaza(piesa P, int culoare);
void myLine(piesa P, unsigned i);
void myRectangle(piesa P, unsigned i);
void myEllipse(piesa P, unsigned i);
void myArc(piesa P, unsigned i);
unsigned alegePiesa(piesa vectorPiese[MAX2], unsigned nrPiese);
void roteste(piesa& P);
void deseneazaMeniul();
unsigned alegeOPiesaDinMeniu(piesa Meniu[MAX2],unsigned nrPieseMeniu);
void punePiesa(piesa& P);
punctLegatura alegePunctLegatura(piesa Piesa[MAX2], unsigned int nrPiese);
void deseneazaLegatura(piesa Piesa[MAX2], unsigned int nrPiese, legatura leg, int culoare);
bool verificaPunctLegatura(piesa Piesa[MAX2], unsigned int nrPiese, int x, int y, legatura &leg);
void deseneazaLegaturaStart(piesa Piesa[MAX2], punctLegatura pStart, int xEnd, int yEnd, int culoare);
void refresh(piesa Piesa[MAX2], unsigned int nrPiese, legatura Legatura[MAX2], unsigned int nrLegaturi);
void puneLegatura(piesa Piesa[MAX2], unsigned int nrPiese, legatura Legatura[MAX2], unsigned int &nrLegaturi);
void movePiesa(int nrPiesaAleasa, piesa Piesa[MAX2], unsigned int nrPiese, legatura Legatura[MAX2], unsigned int nrLegaturi);
void selectieMeniu(int &mX,int &mY);
void initializareFisier(char numeFis[MAX1]);
void adaugarePiesaFis(piesa p,FILE *fisier);
//void initDinFisierBIN(FILE *fisier, piesa p[MAX1], unsigned &nrPiese);
void roteste(unsigned int nrPiesaAleasa, piesa Piesa[MAX2], unsigned int nrPiese, legatura Legatura[MAX2], unsigned int nrLegaturi);
void scrieInBin(piesa Piesa[MAX2],legatura Legatura[MAX2], unsigned &nrPiese,unsigned &nrLegaturi, FILE *fisier);

void citesteDinBin(piesa Piesa[MAX2],legatura Legatura[MAX2], unsigned &nrPiese,unsigned &nrLegaturi, FILE *fisier);

void myLineMen(piesa P, unsigned i);
void myRectangleMen(piesa P, unsigned i);
void myEllipseMen(piesa P, unsigned i);
void myArcMen(piesa P, unsigned i);
void deseneazaMen(piesa P, int culoare);
void amplaseazaMen(piesa& P, unsigned x, unsigned y, unsigned orient);
