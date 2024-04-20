#include "PlikZAdresatami.h"

bool PlikZAdresatami::czyPlikJestPusty()
{
    fstream plikZAdresatami;
    plikZAdresatami.seekg(0, ios::end);
    if (plikZAdresatami.tellg() == 0)
        return false;
    else
        return true;
}
bool PlikZAdresatami::dopiszAdresataDoPliku(Adresat adresat)
{
    string liniaZDanymiAdresata = "";
    fstream plikZAdresatami;
    plikZAdresatami.open(NAZWA_PLIKU_Z_ADRESATAMI, ios:: out | ios::app);

    if (plikZAdresatami.is_open() == true)
    {
        liniaZDanymiAdresata = zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(adresat);

        if (czyPlikJestPusty() == true)
        {
            plikZAdresatami << liniaZDanymiAdresata << endl;
        }
        else
        {
            plikZAdresatami << endl << liniaZDanymiAdresata ;
        }
        plikZAdresatami.close();
        idOstatniegoAdresata++;
        return true;
    }
    return false;
}
int PlikZAdresatami::pobierzIdOstatniegoAdresata()
{
    return idOstatniegoAdresata;
}
int PlikZAdresatami::pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami)
{
    int pozycjaRozpoczeciaIdUzytkownika = daneJednegoAdresataOddzielonePionowymiKreskami.find_first_of('|') + 1;
    int idUzytkownika = MetodyPomocnicze::konwersjaStringNaInt(MetodyPomocnicze::pobierzLiczbe(daneJednegoAdresataOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdUzytkownika));
    return idUzytkownika;
}
int PlikZAdresatami::pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(string daneJednegoAdresataOddzielonePionowymiKreskami)
{
    int pozycjaRozpoczeciaIdAdresata = 0;
    int idAdresata = MetodyPomocnicze::konwersjaStringNaInt(MetodyPomocnicze::pobierzLiczbe(daneJednegoAdresataOddzielonePionowymiKreskami, pozycjaRozpoczeciaIdAdresata));
    return idAdresata;
}
vector<Adresat> PlikZAdresatami::wczytajAdresatowZalogowanegoUzytkownikaZPliku(int idZalogowanegoUzytkownika)
{
    Adresat adresat;
    vector <Adresat> adresaci;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";
    string daneOstatniegoAdresataWPliku = "";
    fstream plikTekstowy;
    plikTekstowy.open(NAZWA_PLIKU_Z_ADRESATAMI, ios::in);

    if (plikTekstowy.is_open() == true)
    {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami))
        {
            if(idZalogowanegoUzytkownika == pobierzIdUzytkownikaZDanychOddzielonychPionowymiKreskami(daneJednegoAdresataOddzielonePionowymiKreskami))
            {
                adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);
                adresaci.push_back(adresat);
            }
        }
        daneOstatniegoAdresataWPliku = daneJednegoAdresataOddzielonePionowymiKreskami;
        plikTekstowy.close();
    }
    if(daneOstatniegoAdresataWPliku != "")
    {
        idOstatniegoAdresata = pobierzIdAdresataZDanychOddzielonychPionowymiKreskami(daneOstatniegoAdresataWPliku);
    }
    return adresaci;
}
Adresat PlikZAdresatami::pobierzDaneAdresata(string daneJednegoAdresataOddzielonePionowymiKreskami)
{
    Adresat adresat;
    int pozycja;

    pozycja = daneJednegoAdresataOddzielonePionowymiKreskami.find('|');
    adresat.ustawId(stoi(daneJednegoAdresataOddzielonePionowymiKreskami.substr(0, pozycja)));
    daneJednegoAdresataOddzielonePionowymiKreskami = daneJednegoAdresataOddzielonePionowymiKreskami.substr(pozycja + 1, daneJednegoAdresataOddzielonePionowymiKreskami.length());

    pozycja = daneJednegoAdresataOddzielonePionowymiKreskami.find('|');
    adresat.ustawIdUzytkownika(stoi(daneJednegoAdresataOddzielonePionowymiKreskami.substr(0, pozycja)));
    daneJednegoAdresataOddzielonePionowymiKreskami = daneJednegoAdresataOddzielonePionowymiKreskami.substr(pozycja + 1, daneJednegoAdresataOddzielonePionowymiKreskami.length());

    pozycja = daneJednegoAdresataOddzielonePionowymiKreskami.find('|');
    adresat.ustawImie(daneJednegoAdresataOddzielonePionowymiKreskami.substr(0, pozycja));
    daneJednegoAdresataOddzielonePionowymiKreskami = daneJednegoAdresataOddzielonePionowymiKreskami.substr(pozycja + 1, daneJednegoAdresataOddzielonePionowymiKreskami.length());

    pozycja = daneJednegoAdresataOddzielonePionowymiKreskami.find('|');
    adresat.ustawNazwisko(daneJednegoAdresataOddzielonePionowymiKreskami.substr(0, pozycja));
    daneJednegoAdresataOddzielonePionowymiKreskami = daneJednegoAdresataOddzielonePionowymiKreskami.substr(pozycja + 1, daneJednegoAdresataOddzielonePionowymiKreskami.length());

    pozycja = daneJednegoAdresataOddzielonePionowymiKreskami.find('|');
    adresat.ustawNumerTelefonu(daneJednegoAdresataOddzielonePionowymiKreskami.substr(0, pozycja));
    daneJednegoAdresataOddzielonePionowymiKreskami = daneJednegoAdresataOddzielonePionowymiKreskami.substr(pozycja + 1, daneJednegoAdresataOddzielonePionowymiKreskami.length());

    pozycja = daneJednegoAdresataOddzielonePionowymiKreskami.find('|');
    adresat.ustawEmail(daneJednegoAdresataOddzielonePionowymiKreskami.substr(0, pozycja));

    pozycja = daneJednegoAdresataOddzielonePionowymiKreskami.find('|');
    adresat.ustawAdres(daneJednegoAdresataOddzielonePionowymiKreskami.substr(0, pozycja));

    return adresat;
}
string PlikZAdresatami::zamienDaneAdresataNaLinieZDanymiOddzielonymiPionowymiKreskami(Adresat adresat)
{
    string liniaZDanymiAdresata = "";

    liniaZDanymiAdresata += MetodyPomocnicze::konwerjsaIntNaString(adresat.pobierzId()) + '|';
    liniaZDanymiAdresata += MetodyPomocnicze::konwerjsaIntNaString(adresat.pobierzIdUzytkownika()) + '|';
    liniaZDanymiAdresata += adresat.pobierzImie() + '|';
    liniaZDanymiAdresata += adresat.pobierzNazwisko() + '|';
    liniaZDanymiAdresata += adresat.pobierzNumerTelefonu() + '|';
    liniaZDanymiAdresata += adresat.pobierzEmail() + '|';
    liniaZDanymiAdresata += adresat.pobierzAdres() + '|';

    return liniaZDanymiAdresata;
}
void PlikZAdresatami::zwiekszIdOstatniegoAdresataOJedenPoZalogowaniuInnegoUzytkownika()
{
    fstream plik;
    plik.open(NAZWA_PLIKU_Z_ADRESATAMI, ios::in);
    if (plik.is_open())
    {
        string linia;
        while (getline(plik, linia))
        {
            idOstatniegoAdresata++;
        }
    }
    plik.close();
}
