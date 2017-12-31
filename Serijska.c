#include "Serijska.h"

void OdabirDatoteke(char **naziv)
{
    FILE *f;

    printf("Unesite naziv datoteke: ");
    scanf("%s", naziv);
    if(!FajlPostoji(naziv, &f))
    {
        printf("Datoteka sa ovim nazivom ne postoji!\n");
        return;
    }

    fclose(f);
}

void FormiranjeDatoteke(char **naziv)
{
    FILE *f;
    Blok blok;

    printf("Unesite naziv datoteke: ");
    scanf("%s", naziv);

    f = fopen(naziv, "wb");

    FormirajPrazanBlok(&blok);
    fwrite(&blok, sizeof(Blok), 1, f);

    fclose(f);
}

void FormirajPrazanBlok(Blok *blok)
{
    int i = 0;

    for(i = 0; i < FAKTOR_BLOKIRANJA; i++)
        FormirajPrazanSlog(&blok->slog[i]);
}

void FormirajPrazanSlog(Slog *slog)
{
    slog->statusZnaka = 2;
    slog->zatvor.evidencioniBroj = 0;
    slog->zatvor.duzinaKazne = 0;
    strcpy(slog->zatvor.datumDolaska ,"");
    strcpy(slog->zatvor.oznakaCelija, "");
    strcpy(slog->zatvor.sifraZatvorenika,"");
}


void PretragaDatoteke(char *naziv)
{
    FILE *f;
    Blok blok;
    int flag = 0, i;
    char sifra[7];

    if(!FajlPostoji(naziv, &f))
    {
        printf("Datoteka sa takvim nazivom ne postoji!\n");
        return;
    }

    printf("Unesite sifru zatvorenika: ");
    scanf("%s", sifra);

    while(flag == 0 && fread(&blok, sizeof(Blok), 1, f))
    {
        for(i = 0; i < FAKTOR_BLOKIRANJA; i++)
        {
            if(!strcmp(blok.slog[i].zatvor.sifraZatvorenika, sifra))
            {
                flag = 1;
                break;
            }
        }
    }

    if(flag == 0)
        printf("Zatvorenik sa takvom sifrom ne postoji!\n");
    else
        IspisiZatvorenika(&blok.slog[i].zatvor);

    fclose(f);
    return;

}

void UnosNovogSloga(char *naziv)
{
   FILE *f;
   Blok blok, blok2;
   Zatvor zatvor;
   int flag = 0, i;


   if(!FajlPostoji(naziv, &f))
   {
       printf("Datoteka sa takvim nazivom ne postoji!!\n");
       return;
   }

   UnosNovogZatvorenika(&zatvor);

   while(flag == 0 && fread(&blok, sizeof(Blok), 1, f))
   {
       for(i = 0; i < FAKTOR_BLOKIRANJA; i++)
       {
           if(blok.slog[i].statusZnaka != 0)
           {
               flag = 1;
               break;
           }
       }
   }

   fseek(f, -sizeof(Blok), SEEK_CUR);

   if(blok.slog[i].statusZnaka == 2)
   {
       if(i == FAKTOR_BLOKIRANJA -1)
       {
          FormirajPrazanBlok(&blok2);
          blok.slog[i].statusZnaka = 0;
          blok.slog[i].zatvor = zatvor;
          fwrite(&blok, sizeof(Blok), 1, f);
          fwrite(&blok2, sizeof(Blok), 1,f);
       }
       else{
            blok.slog[i].statusZnaka = 0;
            blok.slog[i].zatvor = zatvor;
            fwrite(&blok, sizeof(Blok), 1, f);
       }
   }
   else
   {
      blok.slog[i].statusZnaka = 0;
      blok.slog[i].zatvor = zatvor;
      fwrite(&blok, sizeof(Blok), 1, f);
   }

    fclose(f);

}

void IspisSvihSlogova(char *naziv)
{
    FILE *f;
    Blok blok;
    int i, brojac = 1;

    if(FajlPostoji(naziv, &f) == 0)
    {
        printf("Fajl sa takvim nazivom ne postoji!!\n");
        return 0;
    }

    while(fread(&blok, sizeof(Blok), 1, f))
    {
        printf("Blok%d\n\n", brojac);

        for(i = 0; i < FAKTOR_BLOKIRANJA; i++)
        {
            printf("Slog -->%d", i);
            IspisiZatvorenika(&blok.slog[i].zatvor);
            printf("Status znaka: %d\n\n", blok.slog[i].statusZnaka);
        }
        brojac++;
    }

    fclose(f);
}

void AzuriranjeSloga(char *naziv)
{

}

void LogickoBrisanjeSloga(char *naziv)
{
    FILE *f;
    Blok blok;
    int flag = 0, i;
    char sifra[7];

    if(!FajlPostoji(naziv, &f))
    {
        printf("Datoteka sa takvim nazivom ne postoji!\n");
        return;
    }

    printf("Unesite sifru zatvorenika: ");
    scanf("%s", sifra);

    while(flag == 0 && fread(&blok, sizeof(Blok), 1, f))
    {
        for(i = 0; i < FAKTOR_BLOKIRANJA; i++)
        {
            if(!strcmp(blok.slog[i].zatvor.sifraZatvorenika, sifra))
            {
                blok.slog[i].statusZnaka = 1;
                flag = 1;
                break;
            }
        }
    }

    if(flag == 0)
    {
        printf("Zatvorenik sa sifrom %s ne postoji\n", sifra);
    }
    else
    {
        fseek(f, -sizeof(Blok), SEEK_CUR);
        fwrite(&blok, sizeof(Blok), 1, f);
    }

    fclose(f);

}

void FizickoBrisanjeSloga(char *naziv)
{
    FILE *f;
    Blok blok, blok2;
    Slog temp;
    int flag = 0, i;
    char sifra[7];

    if(!FajlPostoji(naziv, &f))
    {
        printf("Datoteka sa takvim nazivom ne postoji!\n");
        return;
    }

    printf("Unesite sifru zatvorenika: ");
    scanf("%s", sifra);

    while(flag == 0 && fread(&blok, sizeof(Blok), 1, f))
    {
        for(i = 0; i < FAKTOR_BLOKIRANJA; i++)
        {
            if(!strcmp(blok.slog[i].zatvor.sifraZatvorenika, sifra))
            {
                flag = 1;
                break;
            }
        }
    }

    if(flag == 0)
    {
        printf("Zatvorenik sa sifrom %s ne postoji\n", sifra);
        fclose(f);
        return;
    }

    do{

        for(; i < FAKTOR_BLOKIRANJA - 1; i++)
        {
            memcpy(&temp, &blok.slog[i], sizeof(Slog));
            memcpy(&blok.slog[i], &blok.slog[i + 1], sizeof(Slog));
            memcpy(&blok.slog[i + 1], &temp, sizeof(Slog));
        }

        if(fread(&blok2, sizeof(Blok), 1, f))
        {
            memcpy(&temp, &blok2.slog[0], sizeof(Slog));
            memcpy(&blok2.slog[0], &blok.slog[FAKTOR_BLOKIRANJA - 1], sizeof(Slog));
            memcpy(&blok.slog[FAKTOR_BLOKIRANJA - 1], &temp, sizeof(Slog));
            fseek(f, -2 * sizeof(Blok), SEEK_CUR);

            fwrite(&blok, sizeof(Blok), 1, f);
            fflush(f);
            fwrite(&blok2, sizeof(Blok), 1, f);
            fflush(f);
            memcpy(&blok, &blok2, sizeof(Blok));
            i = 0;
        }
        else
        {
            fseek(f, -sizeof(Blok), SEEK_CUR);
            FormirajPrazanSlog(&blok.slog[FAKTOR_BLOKIRANJA - 1]);
            fwrite(&blok, sizeof(Blok), 1, f);
            fclose(f);
            return;
        }

    }while(1);

}

int FajlPostoji(char *naziv, FILE ** f)
{
    if((*f = fopen(naziv, "rb+")) == NULL)
        return 0;

    return 1;

}

void IspisiZatvorenika(Zatvor *zatvor)
{
    printf("\nEvidencioni broj: %d", zatvor->evidencioniBroj);
    printf("\nSifra: %s", zatvor->sifraZatvorenika);
    printf("\nDatum dolaska: %s", zatvor->datumDolaska);
    printf("\nOznaka celije: %s", zatvor->oznakaCelija);
    printf("\nDuzina kazne: %d\n", zatvor->duzinaKazne);
}

void UnosNovogZatvorenika(Zatvor *zatvor)
{
    printf("Unesite evidencioni broj zatvorenika: ");
    scanf("%d", &zatvor->evidencioniBroj);
    printf("Unesite sifru zatvorenika: ");
    scanf("%s", &zatvor->sifraZatvorenika);
    printf("Unesite datum dolaska zatvorenika: ");
    scanf("%s", &zatvor->datumDolaska);
    printf("Unesite oznaku celije zatvorenika: ");
    scanf("%s", &zatvor->oznakaCelija);
    printf("Unesite duzinu kazne zatvorenika: ");
    scanf("%d", &zatvor->duzinaKazne);
}
