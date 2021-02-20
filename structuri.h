#pragma once

#define MAX1 40
#define MAX2 80
#define FUNDAL BLACK


struct descriere
{
    char comanda[MAX1];
    unsigned nComenzi;
    float x1[MAX1], y1[MAX1], x2[MAX1], y2[MAX1];
};

struct punctLegatura
{
    float x, y;
    bool ocupat = false;
    unsigned int piesa;
};


struct piesa
{
    unsigned id;
    char nume[MAX1];
    int x,y;
    unsigned orientare;
    char continut[MAX2];
    unsigned nrLegaturi;
    punctLegatura pLeg[MAX1];
    descriere descr;
};

struct legatura
{
    punctLegatura pStart, pEnd;
    unsigned varianta = 1;
};
