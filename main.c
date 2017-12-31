#include "Serijska.c"

void IspisMenija() {

    printf("\n1.Odabir datoteke\n");
    printf("2.Formiranje datoteke\n");
    printf("3.Pretraga Datoteke\n");
    printf("4.Unos novog sloga\n");
    printf("5.Azuriranje sloga\n");
    printf("6.Ispis svih slogova\n");
    printf("7.Logicko brisanje sloga\n");
    printf("8.Fizicko brisanje sloga\n");
    printf("9.Izlazak iz programa\n");
    printf("Vas izbor: ");
}


int main(){

    int izbor;
    char naziv[30];

   do {
        IspisMenija();
        scanf("%d", &izbor);

        switch (izbor)
        {
            case 1: OdabirDatoteke(&naziv);
                break;
            case 2: FormiranjeDatoteke(&naziv);
                break;
            case 3: PretragaDatoteke(naziv);
                break;
            case 4: UnosNovogSloga(naziv);
                break;
            case 5: AzuriranjeSloga(naziv);
                break;
            case 6: IspisSvihSlogova(naziv);
                break;
            case 7: LogickoBrisanjeSloga(naziv);
                break;
            case 8: FizickoBrisanjeSloga(naziv);
                break;
            case 9:
                break;

            default: printf("Uneli ste pogresan broj");
        }
    }while(izbor != 9);
    return 0;
}
