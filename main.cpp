#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winbgim.h>
#include <graphics.h>

#include "structuri.h"
#include "functii.h"


using namespace std;


int main()
{
    char numeFisier[100];
    bool DejaInitializat=false;
    initwindow(1080,740,"Electron");
    setfillstyle(1, FUNDAL);
    bar(0, 0, 1080, 740);

    piesa Piesa[MAX2];
    unsigned nrPiese = 0;

    legatura Legatura[MAX2];
    unsigned nrLegaturi = 0;

    unsigned nrPiesaAleasa;

    bool jmpBack[MAX2+MAX2];///piesa = true, legatura = false
    unsigned nrJumps=0;


    settextstyle(10,HORIZ_DIR,5);
    outtextxy(getmaxx()/4+10,50, (char*)"ELECTRON, v: 0.01.0");
    settextstyle(10,HORIZ_DIR,4);
    rectangle(0,125,getmaxx(),200);
    outtextxy(getmaxx()/3,150,(char*)"Incepe Nou");
    rectangle(0,225,getmaxx(),300);
    outtextxy(getmaxx()/3,250,(char*)"Deschide fisier");
    rectangle(0,325,getmaxx(),400);
    outtextxy(getmaxx()/3,350,(char*)"Deschide informatii");
    rectangle(0,425,getmaxx(),500);
    outtextxy(getmaxx()/3,450,(char*)"Future updates");

    int mX,mY;
    selectieMeniu(mX,mY);
  //  printf("mx=%d,my=%d",mX,mY);


    //getch();
    cleardevice();
    closegraph();



    if(mY>=125&&mY<=200)
    {
        /*
        // fisierul in care va fi salvat tot ce se va lucra
        char numeFisier[100];
        initializareFisier(numeFisier);
        printf("%s",numeFisier);
        FILE *fisier;
        fisier=fopen(numeFisier,"wb");
    */
        initwindow(1080,740,"Electron");
        deseneazaMeniul();

        do {
                nrPiesaAleasa = alegeOPiesaDinMeniu(Meniu,nrPieseMeniu);

                if (nrPiesaAleasa <= 12)
                    {
                        nrPiese++; Piesa[nrPiese] = Meniu[nrPiesaAleasa];

                        punePiesa(Piesa[nrPiese]);

                        nrJumps++;
                        jmpBack[nrJumps]=true;

                    }
                else
                {
                    switch(nrPiesaAleasa){
                    case 13:
                        puneLegatura(Piesa, nrPiese, Legatura, nrLegaturi);
                        nrJumps++;
                        jmpBack[nrJumps]=false;
                        break;
                    case 14:
                        nrPiesaAleasa = alegePiesa(Piesa, nrPiese);
                        movePiesa(nrPiesaAleasa, Piesa, nrPiese, Legatura, nrLegaturi);
                        break;
                    case 18:
                        nrPiesaAleasa = alegePiesa(Piesa, nrPiese);
                        roteste(nrPiesaAleasa, Piesa, nrPiese, Legatura, nrLegaturi);
                        break;
                    case 16:
                        //nrPiesaAleasa = alegePiesa(Piesa,nrPiese);
                        closegraph();

                        system("cls");
                        if(!DejaInitializat)///Nu avem niciun fisier in care sa salvam
                        {

                            ///Partea de creare a fisierului
                            initializareFisier(numeFisier);
                            printf("%s",numeFisier);
                            ///Partea in care scriem in fisier legaturile si piesele
                            FILE *fisier;
                            fisier=fopen(numeFisier,"wb");
                            scrieInBin(Piesa,Legatura,nrPiese,nrLegaturi,fisier);
                            fclose(fisier);
                            ///Partea in care citim din fisier totul
                            fisier=fopen(numeFisier,"rb");
                            citesteDinBin(Piesa,Legatura,nrPiese,nrLegaturi,fisier);
                            fclose(fisier);

                            ///Redeschidem si refacem meniu si afisam ce am citit din fisier
                            initwindow(1080,740,"Electron");
                            deseneazaMeniul();
                                setcolor(WHITE);
                                for(int i = 1; i <= nrPiese; i++)
                                    deseneaza(Piesa[i], WHITE);
                                for(int i = 1; i <= nrLegaturi; i++)
                                    deseneazaLegatura(Piesa, nrPiese, Legatura[i], WHITE);

                            ///Deja avem un fisier in care vom salva mai departe
                            DejaInitializat=true;

                        }
                        else///Avem fisierul creat inainte
                        {
                            closegraph();
                            FILE *fisier;
                            fisier=fopen(numeFisier,"wb");
                            scrieInBin(Piesa,Legatura,nrPiese,nrLegaturi,fisier);

                            //Piesa[0].x = Piesa[0].x+ nrPiese-Piesa[0].x;
                            //Piesa[0].y = Piesa[0].y+ nrLegaturi-Piesa[0].y;
                            fclose(fisier);
                         //   FILE *fisier;
                            fisier=fopen(numeFisier,"rb");
                            citesteDinBin(Piesa,Legatura,nrPiese,nrLegaturi,fisier);
                            fclose(fisier);
                             initwindow(1080,740,"Electron");
                            deseneazaMeniul();
                                setcolor(WHITE);
                                for(int i = 1; i <= nrPiese; i++)
                                    deseneaza(Piesa[i], WHITE);
                                for(int i = 1; i <= nrLegaturi; i++)
                                    deseneazaLegatura(Piesa, nrPiese, Legatura[i], WHITE);


                        }
                        break;
                        /// de aici e ceva nou
                        case 17:

                            if(nrJumps==0)
                            {
                                /*initwindow(400,350,"Eroare");
                                outtextxy(75,165,(char*)"Inca nu ai adaugat nicio piesa");
                                Sleep(350);
                                closegraph();
                                initwindow(1080,740,"Electron");
                                deseneazaMeniul();
                                refresh(Piesa,nrPiese,Legatura,nrLegaturi);*/

                                int wError = initwindow(400,350, "Eroare");
                                setcurrentwindow(wError);
                                outtextxy(75,165,(char*)"Inca nu ai adaugat nicio piesa");
                                Sleep(350);
                                closegraph();
                                int wMain = initwindow(1080,740,"Electron");
                                setcurrentwindow(wMain);
                                deseneazaMeniul();
                                refresh(Piesa,nrPiese,Legatura,nrLegaturi);

                            }
                            else
                            {
                                if(jmpBack[nrJumps]==true)
                                    nrPiese--;
                                else
                                    nrLegaturi--;
                                nrJumps--;
                                cleardevice();
                                deseneazaMeniul();
                                refresh(Piesa,nrPiese,Legatura,nrLegaturi);
                            }

                        break;

                        case 19:
                            if(zoom>14)
                                zoom -= 4;
                            cleardevice();
                            deseneazaMeniul();
                            refresh(Piesa, nrPiese, Legatura, nrLegaturi);
                            break;
                        case 20:
                            zoom += 4;
                            cleardevice();
                            deseneazaMeniul();
                            refresh(Piesa, nrPiese, Legatura, nrLegaturi);
                            break;

                    default:
                        break;
                    }
                }
        } while (nrPiesaAleasa != 15);
        //getch();
        closegraph();
       // fclose(fisier);
    }
    else
    {
        if(mY>=225&&mY<325)
        {
           // printf("SOON");
            printf("Ce fisier vrei sa deschizi >>");
            char numeFisier[MAX2],fisCitit[MAX1];
            strcpy(numeFisier,"Saves\\");
            scanf("%s",fisCitit);
            strcat(numeFisier,fisCitit);
            strcat(numeFisier,".sav");
            strupr(numeFisier);
            printf("Am deschis >> %s",numeFisier);

            FILE *fisier;
            fisier=fopen(numeFisier,"rb");
            citesteDinBin(Piesa,Legatura,nrPiese,nrLegaturi,fisier);

            fclose(fisier);
            //printf("Nr de piese>> %d %d\n",Piesa[0].x,Piesa[0].y);
            //printf("Nr de piese>> %d, Nr de legaturi>>%d",nrPiese,nrLegaturi);
            initwindow(1080,740,"Electron");
            deseneazaMeniul();
            setcolor(WHITE);
            for(int i = 1; i <= nrPiese; i++){//printf("Coordonatele Piesei[%d] = %d %d ",i,Piesa[i].x,Piesa[i].y);
                deseneaza(Piesa[i], WHITE);}
            for(int i = 1; i <= nrLegaturi; i++)
                deseneazaLegatura(Piesa, nrPiese, Legatura[i], WHITE);
            DejaInitializat=true;

            do {
                    nrPiesaAleasa = alegeOPiesaDinMeniu(Meniu,nrPieseMeniu);
                    //roteste(nrPiesaAleasa, Piesa, nrPiese, Legatura, nrLegaturi);
                    // printf("Am ales piesa %u\n",nrPiesaAleasa);
                    if (nrPiesaAleasa <= 12)
                        {
                            nrPiese++; Piesa[nrPiese] = Meniu[nrPiesaAleasa];

                            punePiesa(Piesa[nrPiese]);
                            nrJumps++;
                            jmpBack[nrJumps]=true;

                        }
                    else
                    {
                        switch(nrPiesaAleasa){
                        case 13:
                            puneLegatura(Piesa, nrPiese, Legatura, nrLegaturi);
                            nrJumps++;
                            jmpBack[nrJumps]=false;
                           // fprintf(fisier,"%c",'L');
                           // fwrite(&Piesa[nrPiese],sizeof(struct piesa),1,fisier);
                            break;
                        case 14:
                            nrPiesaAleasa = alegePiesa(Piesa, nrPiese);
                            movePiesa(nrPiesaAleasa, Piesa, nrPiese, Legatura, nrLegaturi);
                            break;
                        case 18:
                            nrPiesaAleasa = alegePiesa(Piesa, nrPiese);
                            roteste(nrPiesaAleasa, Piesa, nrPiese, Legatura, nrLegaturi);
                            break;
                        case 16:
                            //nrPiesaAleasa = alegePiesa(Piesa,nrPiese);
                            closegraph();

                            system("cls");
                            if(!DejaInitializat)///Nu avem niciun fisier in care sa salvam
                            {

                                ///Partea de creare a fisierului
                                initializareFisier(numeFisier);
                                printf("%s",numeFisier);
                                ///Partea in care scriem in fisier legaturile si piesele
                                FILE *fisier;
                                fisier=fopen(numeFisier,"wb");
                                scrieInBin(Piesa,Legatura,nrPiese,nrLegaturi,fisier);
                                fclose(fisier);

                                ///Partea in care citim din fisier totul
                                fisier=fopen(numeFisier,"rb");
                                citesteDinBin(Piesa,Legatura,nrPiese,nrLegaturi,fisier);
                                fclose(fisier);

                                ///Redeschidem si refacem meniu si afisam ce am citit din fisier
                                initwindow(1080,740,"Electron");
                                deseneazaMeniul();
                                setcolor(WHITE);
                                for(int i = 1; i <= nrPiese; i++)
                                    deseneaza(Piesa[i], WHITE);
                                for(int i = 1; i <= nrLegaturi; i++)
                                    deseneazaLegatura(Piesa, nrPiese, Legatura[i], WHITE);

                                ///Deja avem un fisier in care vom salva mai departe
                                DejaInitializat=true;

                            }
                            else///Avem fisierul creat inainte
                            {
                                closegraph();
                                FILE *fisier;
                                fisier=fopen(numeFisier,"wb");
                                scrieInBin(Piesa,Legatura,nrPiese,nrLegaturi,fisier);

                                //Piesa[0].x = Piesa[0].x+ nrPiese-Piesa[0].x;
                                //Piesa[0].y = Piesa[0].y+ nrLegaturi-Piesa[0].y;
                                fclose(fisier);
                             //   FILE *fisier;
                                fisier=fopen(numeFisier,"rb");


                                citesteDinBin(Piesa,Legatura,nrPiese,nrLegaturi,fisier);
                                fclose(fisier);

                                initwindow(1080,740,"Electron");
                                deseneazaMeniul();
                                    setcolor(WHITE);
                                    for(int i = 1; i <= nrPiese; i++)
                                        deseneaza(Piesa[i], WHITE);
                                    for(int i = 1; i <= nrLegaturi; i++)
                                        deseneazaLegatura(Piesa, nrPiese, Legatura[i], WHITE);


                            }
                            break;
                        case 19:
                            if(zoom>14)
                                zoom -= 4;
                            cleardevice();
                            deseneazaMeniul();
                            refresh(Piesa, nrPiese, Legatura, nrLegaturi);
                            break;
                        case 20:
                            zoom += 4;
                            cleardevice();
                            deseneazaMeniul();
                            refresh(Piesa, nrPiese, Legatura, nrLegaturi);
                            break;

/// de aici e ceva nou
                        case 17:

                            if(nrJumps==0)
                            {
                                /*initwindow(400,350,"Eroare");
                                outtextxy(75,165,(char*)"Inca nu ai adaugat nicio piesa");
                                Sleep(350);
                                closegraph();
                                initwindow(1080,740,"Electron");
                                deseneazaMeniul();
                                refresh(Piesa,nrPiese,Legatura,nrLegaturi);*/

                                int wError = initwindow(400,350, "Eroare");
                                setcurrentwindow(wError);
                                outtextxy(75,165,(char*)"Inca nu ai adaugat nicio piesa");
                                Sleep(350);
                                closegraph();
                                int wMain = initwindow(1080,740,"Electron");
                                setcurrentwindow(wMain);
                                deseneazaMeniul();
                                refresh(Piesa,nrPiese,Legatura,nrLegaturi);
                            }
                            else
                            {
                                if(jmpBack[nrJumps]==true)
                                    nrPiese--;
                                else
                                    nrLegaturi--;
                                nrJumps--;
                                cleardevice();
                                deseneazaMeniul();
                                refresh(Piesa,nrPiese,Legatura,nrLegaturi);
                            }

                        break;
                        default:
                            break;
                        }
                    }
            } while (nrPiesaAleasa != 15);


            //fclose(fisier);
            getch();
            closegraph();
        }
        else
        {
            if(mY>=325&&mY<=400)
                system("Info.docx");

            else
            {
                if(mY>=425&&mY<=500)
                    system("FutureUpdates.txt");
                else
                {
                    initwindow(1080,740,"Electron");
                    outtextxy(getmaxx()/4+10,50,(char*)"Proiect creat de Hututuc Felix si Lucaci Alexandru. Speram sa va placa");
                    outtextxy(getmaxx()/4+10,70,(char*)"UPS nu ai apasat pe nicio actiune");
                    getch();
                    closegraph();

                }
            }
        }
    }
//coment
    system("pause");
    return 0;
}
