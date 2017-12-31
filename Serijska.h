#ifndef SERIJSKA_H_INCLUDED
#define SERIJSKA_H_INCLUDED
#define FAKTOR_BLOKIRANJA 4
#include <stdio.h>
#include <string.h>


typedef struct zatvor{
    int evidencioniBroj;
    char sifraZatvorenika[7];
    char datumDolaska[15];
    char oznakaCelija[5];
    int duzinaKazne;
}Zatvor;

typedef struct slog{
    Zatvor zatvor;
    int statusZnaka; //0-OK; 1-Logicki Izbrisan; 2- Specijalni karakter
}Slog;

typedef struct blok{
    Slog slog[FAKTOR_BLOKIRANJA];
}Blok;

void OdabirDatoteke(char **naziv);
void FormiranjeDatoteke(char **naziv);
void PretragaDatoteke(char *naziv);
void UnosNovogSloga(char *naziv);
void IspisSvihSlogova(char *naziv);
void AzuriranjeSloga(char *naziv);
void LogickoBrisanjeSloga(char *naziv);
void FizickoBrisanjeSloga(char *naziv);

int FajlPostoji(char *naziv, FILE ** f);
void IspisiZatvorenika(Zatvor *zatvor);
void UnosNovogZatvorenika(Zatvor *zatvor);

void FormirajPrazanBlok(Blok *blok);
void FormirajPrazanSlog(Slog *slog);




#endif // SERIJSKA_H_INCLUDED
