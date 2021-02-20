#include <cstring> /// am adaugat asta pentru strcpy
#include <stdio.h> /// pentru FILE
#include <stdlib.h> ///pentru exit(1)
#include <graphics.h> ///pentru line

#include "functii.h"
#include "structuri.h"

float zoom = 14.0;
float zoomMen=14.0;

piesa Meniu[MAX1];
const int nrPieseMeniu = 21;
void roteste(unsigned int nrPiesaAleasa, piesa Piesa[MAX2], unsigned int nrPiese, legatura Legatura[MAX2], unsigned int nrLegaturi)
{
    deseneaza(Piesa[nrPiesaAleasa], FUNDAL);
    for(int i = 1; i <= nrLegaturi; i++)
                if(Legatura[i].pStart.piesa ==  nrPiesaAleasa || Legatura[i].pEnd.piesa == nrPiesaAleasa)
                    deseneazaLegatura(Piesa, nrPiese, Legatura[i], FUNDAL);
    Piesa[nrPiesaAleasa].orientare = ( Piesa[nrPiesaAleasa].orientare + 1) % 4;
    for(int i = 1; i <= Piesa[nrPiesaAleasa].nrLegaturi; i++)
        roteste(Piesa[nrPiesaAleasa].pLeg[i].x, Piesa[nrPiesaAleasa].pLeg[i].y, Piesa[nrPiesaAleasa].pLeg[i].x, Piesa[nrPiesaAleasa].pLeg[i].y);
    deseneaza(Piesa[nrPiesaAleasa], WHITE);
    for(int i = 1; i <= nrLegaturi; i++)
    {
        if(Legatura[i].pStart.piesa ==  nrPiesaAleasa)
        {
            roteste(Legatura[i].pStart.x, Legatura[i].pStart.y, Legatura[i].pStart.x, Legatura[i].pStart.y);
            deseneazaLegatura(Piesa, nrPiese, Legatura[i], WHITE);
        }
        if(Legatura[i].pEnd.piesa ==  nrPiesaAleasa)
        {
            roteste(Legatura[i].pEnd.x, Legatura[i].pEnd.y, Legatura[i].pEnd.x, Legatura[i].pEnd.y);
            deseneazaLegatura(Piesa, nrPiese, Legatura[i], WHITE);
        }
    }
}
void initializeaza(piesa& P)
{
    P.orientare = 0;
    char numeFisier[256], s[MAX1];
    //strcpy(numeFisier, "D:\\Electron\\electronBun\\Piese\\");
    strcpy(numeFisier, P.nume);
    strcat(numeFisier, ".txt");
    FILE* f = fopen(numeFisier, "r");
    if(f == NULL)
    {
        printf("Eroare la deschiderea fisierului! \n");
        exit(1);
    }
    fscanf(f, "%s", s);
    //printf("%s\n", s);
    fscanf(f, "%d", &P.nrLegaturi);
    //printf("%d\n", P.nrLegaturi);
    for (unsigned i = 1; i <= P.nrLegaturi; i++)
    {
        fscanf(f,"%f%f", &P.pLeg[i].x, &P.pLeg[i].y);
         //printf("%f %f\n", P.pLeg[i].x, P.pLeg[i].y);
    }
    fscanf(f, "%s", s);
    //printf("%s\n", s);
    unsigned i = 1;
    while(!feof(f))
    {
        fscanf(f, "%c%f%f", &P.descr.comanda[i], &P.descr.x1[i], &P.descr.y1[i]);
        fscanf(f, "%f%f\n", &P.descr.x2[i], &P.descr.y2[i]);
        // printf("%c %f %f %f %f\n",P.descr.comanda[i],P.descr.x1[i],P.descr.y1[i],P.descr.x2[i],P.descr.y2[i]);
         i++;
    }
    P.descr.nComenzi = --i;
    fclose(f);
}
void roteste (float x, float y, float & xnou, float & ynou)
{

    xnou = y;
    ynou = -x;
}
void myLine(piesa P, unsigned i)
{
    float x_1, y_1, x_2, y_2;
    float x1, y1, x2, y2;
    x1 = P.descr.x1[i];
    y1 = P.descr.y1[i];
    x2 = P.descr.x2[i];
    y2 = P.descr.y2[i];
    switch (P.orientare)
    {
    case 0: x_1 = x1; y_1 = y1; x_2 = x2; y_2 = y2; break;
    case 1: roteste(x1, y1, x_1, y_1); roteste(x2, y2, x_2, y_2); break;
    case 2: roteste(x1, y1, x_1, y_1); roteste(x_1, y_1, x1, y1); x_1 = x1; y_1 = y1;
            roteste(x2, y2, x_2, y_2); roteste(x_2, y_2, x2, y2); x_2 = x2; y_2 = y2; break;
    case 3: roteste(x1, y1, x_1, y_1); roteste(x_1, y_1, x1, y1); roteste(x1, y1, x_1, y_1);
            roteste(x2, y2, x_2, y_2); roteste(x_2, y_2, x2, y2); roteste(x2, y2, x_2, y_2); break;
    }
    line(P.x + zoom * x_1, P.y + zoom * y_1, P.x + zoom * x_2, P.y + zoom * y_2);
}
void myRectangle(piesa P, unsigned i)
{
    float x_1, y_1, x_2, y_2;
    float x1, y1, x2, y2;
    x1 = P.descr.x1[i];
    y1 = P.descr.y1[i];
    x2 = P.descr.x2[i];
    y2 = P.descr.y2[i];
    switch (P.orientare)
    {
    case 0: x_1 = x1; y_1 = y1; x_2 = x2; y_2 = y2; break;
    case 1: roteste(x1,y1,x_1,y_1); roteste(x2,y2,x_2,y_2); break;
    case 2: roteste(x1,y1,x_1,y_1); roteste(x_1,y_1,x1,y1); x_1 = x1; y_1 = y1;
            roteste(x2,y2,x_2,y_2); roteste(x_2,y_2,x2,y2); x_2 = x2; y_2 = y2; break;
    case 3: roteste(x1,y1,x_1,y_1); roteste(x_1,y_1,x1,y1); roteste(x1,y1,x_1,y_1);
            roteste(x2,y2,x_2,y_2); roteste(x_2,y_2,x2,y2); roteste(x2,y2,x_2,y_2); break;
    }
    rectangle(P.x+zoom*x_1,P.y+zoom*y_1,P.x+zoom*x_2,P.y+zoom*y_2);
}

void myEllipse(piesa P, unsigned i)
{
    float x_1, y_1, x_2, y_2;
    float x1, y1, x2, y2;
    x1 = P.descr.x1[i];
    y1 = P.descr.y1[i];
    x2 = P.descr.x2[i];
    y2 = P.descr.y2[i];
    switch (P.orientare)
    {
    case 0: x_1 = x1; y_1 = y1; x_2 = x2; y_2 = y2; break;
    case 1: roteste(x1,y1,x_1,y_1); x_2 = y2; y_2 = x2; break;
    case 2: roteste(x1,y1,x_1,y_1); roteste(x_1,y_1,x1,y1); x_1 = x1; y_1 = y1; x_2 = x2; y_2 = y2; break;
    case 3: roteste(x1,y1,x_1,y_1); roteste(x_1,y_1,x1,y1); roteste(x1,y1,x_1,y_1); x_2 = y2; y_2 = x2; break;
    }
    ellipse(P.x+x_1*zoom,P.y+y_1*zoom,0,360,x_2*zoom,y_2*zoom);
}

void myArc(piesa P, unsigned i)
{
    float x1, y1, x2;
    float x_1, y_1;
    x1 = P.descr.x1[i];
    y1 = P.descr.y1[i];
    x2 = P.descr.x2[i]; /* y2=P.descr.y2[i]; */
    switch (P.orientare)
    {
    case 0: arc(P.x+x1*zoom,P.y+y1*zoom,-90,90,x2*zoom); break;
    case 1: roteste(x1,y1,x_1,y_1); arc(P.x+x_1*zoom,P.y+y_1*zoom,0,180,x2*zoom); break;
    case 2: roteste(x1,y1,x_1,y_1); roteste(x_1,y_1,x1,y1); arc(P.x+x1*zoom,P.y+y1*zoom,90,270,x2*zoom); break;
    case 3: roteste(x1,y1,x_1,y_1); roteste(x_1,y_1,x1,y1); roteste(x1,y1,x_1,y_1); arc(P.x+x_1*zoom,P.y+y_1*zoom,-180,0,x2*zoom); break;
    }
}



void myLineMen(piesa P, unsigned i)
{
    float x_1, y_1, x_2, y_2;
    float x1, y1, x2, y2;
    x1 = P.descr.x1[i];
    y1 = P.descr.y1[i];
    x2 = P.descr.x2[i];
    y2 = P.descr.y2[i];
    switch (P.orientare)
    {
    case 0: x_1 = x1; y_1 = y1; x_2 = x2; y_2 = y2; break;
    case 1: roteste(x1, y1, x_1, y_1); roteste(x2, y2, x_2, y_2); break;
    case 2: roteste(x1, y1, x_1, y_1); roteste(x_1, y_1, x1, y1); x_1 = x1; y_1 = y1;
            roteste(x2, y2, x_2, y_2); roteste(x_2, y_2, x2, y2); x_2 = x2; y_2 = y2; break;
    case 3: roteste(x1, y1, x_1, y_1); roteste(x_1, y_1, x1, y1); roteste(x1, y1, x_1, y_1);
            roteste(x2, y2, x_2, y_2); roteste(x_2, y_2, x2, y2); roteste(x2, y2, x_2, y_2); break;
    }
    line(P.x + zoomMen * x_1, P.y + zoomMen * y_1, P.x + zoomMen * x_2, P.y + zoomMen * y_2);
}
void myRectangleMen(piesa P, unsigned i)
{
    float x_1, y_1, x_2, y_2;
    float x1, y1, x2, y2;
    x1 = P.descr.x1[i];
    y1 = P.descr.y1[i];
    x2 = P.descr.x2[i];
    y2 = P.descr.y2[i];
    switch (P.orientare)
    {
    case 0: x_1 = x1; y_1 = y1; x_2 = x2; y_2 = y2; break;
    case 1: roteste(x1,y1,x_1,y_1); roteste(x2,y2,x_2,y_2); break;
    case 2: roteste(x1,y1,x_1,y_1); roteste(x_1,y_1,x1,y1); x_1 = x1; y_1 = y1;
            roteste(x2,y2,x_2,y_2); roteste(x_2,y_2,x2,y2); x_2 = x2; y_2 = y2; break;
    case 3: roteste(x1,y1,x_1,y_1); roteste(x_1,y_1,x1,y1); roteste(x1,y1,x_1,y_1);
            roteste(x2,y2,x_2,y_2); roteste(x_2,y_2,x2,y2); roteste(x2,y2,x_2,y_2); break;
    }
    rectangle(P.x+zoomMen*x_1,P.y+zoomMen*y_1,P.x+zoomMen*x_2,P.y+zoomMen*y_2);
}

void myEllipseMen(piesa P, unsigned i)
{
    float x_1, y_1, x_2, y_2;
    float x1, y1, x2, y2;
    x1 = P.descr.x1[i];
    y1 = P.descr.y1[i];
    x2 = P.descr.x2[i];
    y2 = P.descr.y2[i];
    switch (P.orientare)
    {
    case 0: x_1 = x1; y_1 = y1; x_2 = x2; y_2 = y2; break;
    case 1: roteste(x1,y1,x_1,y_1); x_2 = y2; y_2 = x2; break;
    case 2: roteste(x1,y1,x_1,y_1); roteste(x_1,y_1,x1,y1); x_1 = x1; y_1 = y1; x_2 = x2; y_2 = y2; break;
    case 3: roteste(x1,y1,x_1,y_1); roteste(x_1,y_1,x1,y1); roteste(x1,y1,x_1,y_1); x_2 = y2; y_2 = x2; break;
    }
    ellipse(P.x+x_1*zoomMen,P.y+y_1*zoomMen,0,360,x_2*zoomMen,y_2*zoomMen);
}

void myArcMen(piesa P, unsigned i)
{
    float x1, y1, x2;
    float x_1, y_1;
    x1 = P.descr.x1[i];
    y1 = P.descr.y1[i];
    x2 = P.descr.x2[i]; /* y2=P.descr.y2[i]; */
    switch (P.orientare)
    {
    case 0: arc(P.x+x1*zoomMen,P.y+y1*zoomMen,-90,90,x2*zoomMen); break;
    case 1: roteste(x1,y1,x_1,y_1); arc(P.x+x_1*zoomMen,P.y+y_1*zoomMen,0,180,x2*zoomMen); break;
    case 2: roteste(x1,y1,x_1,y_1); roteste(x_1,y_1,x1,y1); arc(P.x+x1*zoomMen,P.y+y1*zoomMen,90,270,x2*zoomMen); break;
    case 3: roteste(x1,y1,x_1,y_1); roteste(x_1,y_1,x1,y1); roteste(x1,y1,x_1,y_1); arc(P.x+x_1*zoomMen,P.y+y_1*zoomMen,-180,0,x2*zoomMen); break;
    }
}

void deseneazaMen(piesa P, int culoare)
{
    setcolor(culoare);
    for (unsigned i = 1; i <= P.descr.nComenzi; i++)
        switch(P.descr.comanda[i])
        {
        case 'L':
            myLineMen(P, i);
            break;
        case 'R':
            myRectangleMen(P, i);
            break;
        case 'O':
            myEllipseMen(P, i);
            break;
        case 'A':
            myArcMen(P, i);
            break;
        }
}
void amplaseazaMen(piesa& P, unsigned x, unsigned y, unsigned orient, bool inv=0)
{
    P.x = x;
    P.y = y;
    P.orientare = orient;
    if(inv==0)
        deseneazaMen(P, WHITE);
    else
        deseneazaMen(P,FUNDAL);
}


void deseneaza(piesa P, int culoare)
{
    setcolor(culoare);
    for (unsigned i = 1; i <= P.descr.nComenzi; i++)
        switch(P.descr.comanda[i])
        {
        case 'L':
            myLine(P, i);
            break;
        case 'R':
            myRectangle(P, i);
            break;
        case 'O':
            myEllipse(P, i);
            break;
        case 'A':
            myArc(P, i);
            break;
        }
}

void amplaseaza(piesa& P, unsigned x, unsigned y, unsigned orient, bool inv=0)
{
    P.x = x;
    P.y = y;
    P.orientare = orient;
    if(inv==0)
        deseneaza(P, WHITE);
    else
        deseneaza(P,FUNDAL);
}

unsigned alegePiesa(piesa vectorPiese[MAX2], unsigned nrPiese)
{
    bool click = false;
    unsigned i, nrPiesaAleasa = 0;
    int xMouse, yMouse;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse = mousex(); yMouse = mousey();
            for (i = 1; i <= nrPiese; i++)
                if (abs(vectorPiese[i].x - xMouse) <= 10 && abs(vectorPiese[i].y - yMouse) <= 10)
                {
                    nrPiesaAleasa = i;
                    click = true;
                }
        }
    while (!click);
    return nrPiesaAleasa;
}


/*
void roteste(piesa& P)
{
    deseneaza(P, FUNDAL);
    P.orientare = (P.orientare+1) % 4;
    deseneaza(P, WHITE);
}
*/

void deseneazaMeniul()
{
    setcolor(WHITE);
    outtextxy(575,10,(char*)"Electron v:0.01.00");
     outtextxy(575,25,(char*)"Proiect creat de Hututuc Felix si Lucaci Alexandru. Speram sa va placa.");
    setcolor(RED);
    rectangle(0,0,80,getmaxy());
    strcpy(Meniu[1].nume,"DIODA");
    strcpy(Meniu[2].nume,"ZENNER");
    strcpy(Meniu[3].nume,"TRANZNPN");
    strcpy(Meniu[4].nume,"TRANZPNP");
    strcpy(Meniu[5].nume,"CONDENS");
    strcpy(Meniu[6].nume,"REZIST");
    strcpy(Meniu[7].nume,"BATERIE");
    strcpy(Meniu[8].nume,"POLARIZ");
    strcpy(Meniu[9].nume,"SINU");
    strcpy(Meniu[10].nume,"SERVOMOT");
    strcpy(Meniu[11].nume,"AMPLOP");
    strcpy(Meniu[12].nume,"NOD");
    strcpy(Meniu[13].nume,"LINIE");
    strcpy(Meniu[14].nume,"MOVE");
    strcpy(Meniu[15].nume, "STOP");
    strcpy(Meniu[16].nume, "SAVE");
    strcpy(Meniu[17].nume, "STERGE");
    strcpy(Meniu[18].nume, "ROTESTE");
    strcpy(Meniu[19].nume, "MINUS");
    strcpy(Meniu[20].nume, "PLUS");
    rectangle(0,0,getmaxx()-20,50);
    //line(80,24,getmaxx()-20,24);
    //int lat=getmaxy()/nrPieseMeniu+1; /// LAT nu e folosit la nimic
    //setcolor(WHITE);
    //outtextxy(25,12*50+20,"Linie");
    //outtextxy(25,13*50+20,"MOVE");

    for (unsigned i = 1; i <= nrPieseMeniu-2; i++)
    {
        initializeaza(Meniu[i]);
        zoomMen /= 2;
        if(i==13)
        {
            amplaseazaMen(Meniu[i],39,(i-1)*50+25,0,1);
            setcolor(RED);
            line(0,i*50,80,i*50);
            setcolor(WHITE);
            outtextxy(25,(i-1)*50+20,"Linie");
            setcolor(RED);
        }
        else{

            if(i==14)
            {
                amplaseazaMen(Meniu[i],39,(i-1)*50+25,0,1);
                setcolor(RED);
                line(0,i*50,80,i*50);
                setcolor(WHITE);
                outtextxy(25,(i-1)*50+20,"MOVE");
                setcolor(RED);
            }

            if(i == 15)
            {
                amplaseazaMen(Meniu[i],39,(i-1)*50+25,0,0);
                setcolor(RED);
                line(0,i*50,80,i*50);
                setcolor(WHITE);
                outtextxy(25,(i-1)*50+20,"STOP");
                setcolor(RED);
            }
            else
            {
                amplaseazaMen(Meniu[i],39,(i-1)*50+25,0,0);
                setcolor(RED);
                line(0,i*50,80,i*50);
            }
        }
        zoomMen *= 2;

    }

    /*setcolor(WHITE);
    outtextxy(25,12*50+20,"Linie");
    outtextxy(25,13*50+20,"MOVE");
    setcolor(RED);*/
    initializeaza(Meniu[16]);
    zoomMen /= 2;
    line(150,0,150,50);

    amplaseazaMen(Meniu[16],115,25,0,1);
    setcolor(WHITE);
    outtextxy(97,19,"SAVE");
    zoomMen *= 2;


    setcolor(RED);
    line(getmaxx()-20,0,getmaxx()-20,getmaxy());
    line(80,getmaxy()-20,getmaxx(),getmaxy()-20);

    initializeaza(Meniu[17]);
    zoomMen /= 2;
    line(250,0,250,50);

    amplaseazaMen(Meniu[17],200,25,0,1);
    setcolor(WHITE);
    outtextxy(165,19,"JMP BACK");

    setcolor(RED);
    line(getmaxx()-20,0,getmaxx()-20,getmaxy());
    line(80,getmaxy()-20,getmaxx(),getmaxy()-20);
    zoomMen *= 2;

    initializeaza(Meniu[18]);
    zoomMen /= 2;
    line(350,0,350,50);

    amplaseazaMen(Meniu[18],295,25,0,1);
    setcolor(WHITE);
    outtextxy(270,19,"ROTESTE");

    setcolor(RED);
    line(getmaxx()-20,0,getmaxx()-20,getmaxy());
    line(80,getmaxy()-20,getmaxx(),getmaxy()-20);
    zoomMen *= 2;

    initializeaza(Meniu[19]);
    zoomMen /= 2;
    line(470,0,470,50);

    amplaseazaMen(Meniu[19],410,25, 0, 1);
    setcolor(WHITE);
    outtextxy(367,19,"MICSOREAZA");

    setcolor(RED);
    line(getmaxx()-20,0,getmaxx()-20,getmaxy());
    line(80,getmaxy()-20,getmaxx(),getmaxy()-20);
    zoomMen *= 2;

    initializeaza(Meniu[20]);
    zoomMen /= 2;
    line(560,0,560,50);

    amplaseazaMen(Meniu[20],520,25,0,1);
    setcolor(WHITE);
    outtextxy(485,19,"MARESTE");

    setcolor(RED);
    line(getmaxx()-20,0,getmaxx()-20,getmaxy());
    line(80,getmaxy()-20,getmaxx(),getmaxy()-20);
    zoomMen *= 2;

    setcolor(WHITE);




}

unsigned alegeOPiesaDinMeniu(piesa Meniu[MAX2],unsigned nrPieseMeniu)
{
    unsigned nrPiesaAleasa = 0;
    nrPiesaAleasa = alegePiesa(Meniu,nrPieseMeniu);
    // printf("%d, ",nrPiesaAleasa);
    return nrPiesaAleasa;
}
void punePiesa(piesa& P)
{
    bool click = false;
    int xMouse, yMouse;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse = mousex(); yMouse = mousey();
            // printf("%d, %d\n",xMouse,yMouse);
            if(xMouse > 80 && xMouse < getmaxx() - 30 && yMouse > 50 && yMouse < getmaxy() - 30)
            {
                amplaseaza(P,xMouse,yMouse,0,0);
                click = true;
            }
        }
    while (!click);
}
punctLegatura alegePunctLegatura(piesa Piesa[MAX2], unsigned int nrPiese)
{
    bool click = false;
    //printf("TEST2 \n");
    int xMouse, yMouse;
    punctLegatura p;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            //printf("TEST IF \n");
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse = mousex(); yMouse = mousey();
            for(unsigned int i = 1; i <= nrPiese; i++)
            {
                //printf("TEST LOOP i \n");
                //printf("%d - %d \n", i, Piesa[i].nrLegaturi);
                for(unsigned int j = 1; j <= Piesa[i].nrLegaturi; j++)
                {
                    //printf("TEST LOOP j \n");
                    if(abs(Piesa[i].x + (zoom * Piesa[i].pLeg[j].x) - xMouse) <= 10 && abs(Piesa[i].y + (zoom * Piesa[i].pLeg[j].y) - yMouse) <= 10)
                    {
                        //Piesa[i].pLeg[j].ocupat = true;
                        p = Piesa[i].pLeg[j];
                        p.piesa = i;
                        click = true;
                        //printf("Am ales punctul %d %d \n", xMouse, yMouse);
                    }
                }
            }
        }
    while(!click);
    return p;

}

void deseneazaLegatura(piesa Piesa[MAX2], unsigned int nrPiese, legatura leg, int culoare)
{
    //printf("TEST deseneazaLegatura \n");
    setcolor(culoare);
    if(leg.varianta == 1)
    {
        line(Piesa[leg.pStart.piesa].x + (zoom * leg.pStart.x), Piesa[leg.pStart.piesa].y + (zoom * leg.pStart.y), Piesa[leg.pStart.piesa].x + (zoom * leg.pStart.x), Piesa[leg.pEnd.piesa].y + (zoom * leg.pEnd.y));
        line(Piesa[leg.pStart.piesa].x + (zoom * leg.pStart.x), Piesa[leg.pEnd.piesa].y + (zoom * leg.pEnd.y), Piesa[leg.pEnd.piesa].x + (zoom * leg.pEnd.x), Piesa[leg.pEnd.piesa].y + (zoom * leg.pEnd.y));
    }
    else
    {
        line(Piesa[leg.pStart.piesa].x + (zoom * leg.pStart.x), Piesa[leg.pStart.piesa].y + (zoom * leg.pStart.y), Piesa[leg.pEnd.piesa].x + (zoom * leg.pEnd.x), Piesa[leg.pStart.piesa].y + (zoom * leg.pStart.y));
        line(Piesa[leg.pEnd.piesa].x + (zoom * leg.pEnd.x), Piesa[leg.pStart.piesa].y + (zoom * leg.pStart.y), Piesa[leg.pEnd.piesa].x + (zoom * leg.pEnd.x), Piesa[leg.pEnd.piesa].y + (zoom * leg.pEnd.y));
    }

}

bool verificaPunctLegatura(piesa Piesa[MAX2], unsigned int nrPiese, int x, int y, legatura &leg)
{
    for(unsigned int i = 1; i <= nrPiese; i++)
    {
        //printf("TEST LOOP i \n");
        //printf("%d - %d \n", i, Piesa[i].nrLegaturi);
        for(unsigned int j = 1; j <= Piesa[i].nrLegaturi; j++)
        {
            //printf("TEST LOOP j \n");
            if(abs(Piesa[i].x + (zoom * Piesa[i].pLeg[j].x) - x) <= 10
                            && abs(Piesa[i].y + (zoom * Piesa[i].pLeg[j].y) - y) <= 10)
            {
                //Piesa[i].pLeg[j].ocupat = true;
                //printf("Am ales punctul %d %d \n", xMouse, yMouse);
                leg.pEnd.x = Piesa[i].pLeg[j].x;
                leg.pEnd.y = Piesa[i].pLeg[j].y;
                leg.pEnd.piesa = i;
                return true;
            }
        }
    }
    return false;
}

void deseneazaLegaturaStart(piesa Piesa[MAX2], punctLegatura pStart, int xEnd, int yEnd, int culoare)
{
    setcolor(culoare);
    line(Piesa[pStart.piesa].x + (zoom * pStart.x), Piesa[pStart.piesa].y + (zoom * pStart.y), Piesa[pStart.piesa].x + (zoom * pStart.x), yEnd);
    line(Piesa[pStart.piesa].x + (zoom * pStart.x), yEnd, xEnd, yEnd);
}

void refresh(piesa Piesa[MAX2], unsigned int nrPiese, legatura Legatura[MAX2], unsigned int nrLegaturi)
{
    setcolor(WHITE);
    for(int i = 1; i <= nrPiese; i++)
        deseneaza(Piesa[i], WHITE);
    for(int i = 1; i <= nrLegaturi; i++)
        deseneazaLegatura(Piesa, nrPiese, Legatura[i], WHITE);
    int lat=getmaxx()/nrPieseMeniu;
    for (unsigned i = 1; i <= nrPieseMeniu; i++)
    {
        zoomMen /= 2;
        deseneazaMen(Meniu[i], WHITE);
        zoomMen *= 2;
    }
}

void puneLegatura(piesa Piesa[MAX2], unsigned int nrPiese, legatura Legatura[MAX2], unsigned int &nrLegaturi)
{
    //printf("TEST");
    punctLegatura legStart, legEnd;
    int xEnd, yEnd;
    legStart = alegePunctLegatura(Piesa, nrPiese);
    nrLegaturi++;
    Legatura[nrLegaturi].pStart = legStart;

    do{
        while(!ismouseclick(WM_LBUTTONUP))
        {
            deseneazaLegaturaStart(Piesa, legStart, xEnd, yEnd, FUNDAL);
            delay(50);
            if(ismouseclick(WM_MOUSEMOVE))
                getmouseclick(WM_MOUSEMOVE, xEnd, yEnd);
            deseneazaLegaturaStart(Piesa, legStart, xEnd, yEnd, WHITE);
            delay(50);
        }
        deseneazaLegaturaStart(Piesa, legStart, xEnd, yEnd, FUNDAL);
        getmouseclick(WM_LBUTTONUP, xEnd, yEnd);
        deseneazaLegaturaStart(Piesa, legStart, xEnd, yEnd, WHITE);
    }while(!verificaPunctLegatura(Piesa, nrPiese, xEnd, yEnd, Legatura[nrLegaturi]) && !ismouseclick(WM_RBUTTONDOWN));
    deseneazaLegaturaStart(Piesa, legStart, xEnd, yEnd, FUNDAL);
    if(ismouseclick(WM_RBUTTONDOWN))
    {
        /*for(unsigned i = 1; i <= Piesa[legStart.piesa].nrLegaturi; i++)
        {
            printf("TEST FOR \n");
            if(Piesa[Legatura[nrLegaturi].pStart.piesa].pLeg[i].x == legStart.x && Piesa[Legatura[nrLegaturi].pStart.piesa].pLeg[i].y == legStart.y)
            {
                printf("TEST IF \n");
                Piesa[Legatura[nrLegaturi].pStart.piesa].pLeg[i].ocupat = false;
            }
        }*/
        nrLegaturi--;
        clearmouseclick(WM_RBUTTONDOWN);
    }

    else
        deseneazaLegatura(Piesa, nrPiese, Legatura[nrLegaturi], WHITE);
    refresh(Piesa, nrPiese, Legatura, nrLegaturi);
}

void movePiesa(int nrPiesaAleasa, piesa Piesa[MAX2], unsigned int nrPiese, legatura Legatura[MAX2], unsigned int nrLegaturi)
{
    int xMouse, yMouse;
    do{
        while(!ismouseclick(WM_LBUTTONUP))
        {
            deseneaza(Piesa[nrPiesaAleasa], FUNDAL);
            for(unsigned int i = 1; i <= nrLegaturi; i++)
                if(Legatura[i].pStart.piesa ==  nrPiesaAleasa || Legatura[i].pEnd.piesa == nrPiesaAleasa)
                    deseneazaLegatura(Piesa, nrPiese, Legatura[i], FUNDAL);
            delay(50);
            if(ismouseclick(WM_MOUSEMOVE))
            {
                getmouseclick(WM_MOUSEMOVE, xMouse, yMouse);

            }
            amplaseaza(Piesa[nrPiesaAleasa], xMouse, yMouse, Piesa[nrPiesaAleasa].orientare,0);
            for(int i = 1; i <= nrLegaturi; i++)
                if(Legatura[i].pStart.piesa ==  nrPiesaAleasa || Legatura[i].pEnd.piesa == nrPiesaAleasa)
                    deseneazaLegatura(Piesa, nrPiese, Legatura[i], WHITE);
            delay(50);
        }
        deseneaza(Piesa[nrPiesaAleasa], FUNDAL);
        for(int i = 1; i <= nrLegaturi; i++)
                if(Legatura[i].pStart.piesa ==  nrPiesaAleasa || Legatura[i].pEnd.piesa == nrPiesaAleasa)
                    deseneazaLegatura(Piesa, nrPiese, Legatura[i], FUNDAL);
        getmouseclick(WM_LBUTTONUP, xMouse, yMouse);
        deseneaza(Piesa[nrPiesaAleasa], WHITE);
        for(int i = 1; i <= nrLegaturi; i++)
                if(Legatura[i].pStart.piesa ==  nrPiesaAleasa || Legatura[i].pEnd.piesa == nrPiesaAleasa)
                    deseneazaLegatura(Piesa, nrPiese, Legatura[i], WHITE);
    }while(!ismouseclick(WM_LBUTTONDOWN));
    refresh(Piesa, nrPiese, Legatura, nrLegaturi);
    clearmouseclick(WM_LBUTTONUP);
}
void selectieMeniu(int &mX,int &mY)
{
    bool click = false;

    while(!click){
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
                clearmouseclick(WM_LBUTTONDOWN);
                mX = mousex();
                mY = mousey();
                click=true;
        }
    }

}

void initializareFisier(char numeFis[MAX1])
{
    char inceput[MAX1]="Saves\\";
    printf("Fisierul pe care doriti sa-l creati>> ");
    scanf("%s", numeFis);
    strcat(inceput,numeFis);
    strcat(inceput,".sav");
    strcpy(numeFis,inceput);
    strupr(numeFis);
}
/*
void adaugarePiesaFis(piesa p,FILE *fisier)
{
    fprintf(fisier,"%c",'P');
    fwrite(&p,sizeof(struct piesa),1,fisier);

}

void adaugareLegaturaFIs(legatura &l, FILE *fisier)
{
        fprintf(fisier,"%c",'P');

}
void initDinFisierBIN(FILE *fisier, piesa p[MAX1], unsigned &nrPiese)
{
    nrPiese=0;
    char k;
    while(!feof(fisier))
    {
        nrPiese++;
        fscanf(fisier,"%c",&k);

        switch (k)
        {
        case 'P':
            fread(&p[nrPiese],sizeof(struct piesa),1,fisier);
            break;
        default:

            break;
        }

    }



}*/
void scrieInBin(piesa Piesa[MAX2],legatura Legatura[MAX2], unsigned &nrPiese,unsigned &nrLegaturi, FILE *fisier)
{
    Piesa[0].x=nrPiese;
    Piesa[0].y=nrLegaturi;
    for(unsigned i=0;i<=nrPiese;i++)
        {fwrite(&(Piesa[i]),sizeof(struct piesa),1,fisier);
            //printf("Coord piesa[%d]= %d %d ",i,Piesa[i].x,Piesa[i].y);
        }
    for(unsigned i=1;i<=nrLegaturi;i++)
        fwrite(&(Legatura[i]),sizeof(struct legatura),1,fisier);

}


void citesteDinBin(piesa Piesa[MAX2],legatura Legatura[MAX2], unsigned &nrPiese,unsigned &nrLegaturi, FILE *fisier)
{

        fread(&Piesa[0],sizeof(struct piesa),1,fisier);
        nrPiese=Piesa[0].x;
        nrLegaturi=Piesa[0].y;
        for(unsigned i=1;i<=nrPiese;i++){
              fread(&Piesa[i],sizeof(struct piesa),1,fisier);
              //printf("Coord piesa[%d]= %d %d ",i,Piesa[i].x,Piesa[i].y);
        }
        for(unsigned i=1;i<=nrLegaturi;i++)
            fread(&Legatura[i],sizeof(struct legatura),1,fisier);
}
