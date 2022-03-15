Ohjelmassa käytetään kolmea private osaan tallennettua tietorakennetta:

1. std::unordered_map<TownID,Town*> towns__;
	Tämä tietorakenne tallentaa kaikkien kaupunkien ID:t ja Town osoittimet yhteen unordered mappiin
	Valitsin Unordered mapin, sillä kaupunkien lisäysjärjestystä ei tarvitse ja map rakenne sopii hyvin tietoparin tallentamiseen
	Myös useat unordered map operaatiota ovat nopeita

2. std::multimap<int, TownID> towns_distance_from_origo__;
	Tämä tietorakenne tallentaa kaikkien kaupunkien etäisyydet origosta ja kaupunkien ID:t yhteen multimappiin.
	Valitsin tälle tiedolle multimapin, sillä map tietorakenne järjestää parit automaattisesti avaimen (eli etäisyyden) perusteella, eikä manuaaliselle järjestämiselle ole tarvetta
	Multimap voi tallentaa useita samoja avaimia, joka on tärkeää, sillä usealla kaupungilla voi olla sama etäisyys
	Halusin tallentaa etäisyydet omaan tietorakenteeseen selkeyden vuoksi, sekä helpon min ja max distancen laskemisen vuoksi. 
	Tulee ottaa huomioon, että kaupunkia poistaessa, tulee myös kaupunki poistaa etäisyystietorakenteesta. 
	Tämä vähentää hieman koodin selkeyttä.

3. std::unordered_map<TownID, TownID> vassalships__;
	Tämä tietorakenne tallentaa tiedot vassalisuhteista unordered mappiin. 
	Tiedot tallentuu <vassali, isäntä> järjestyksessä. Näin myös estetään kaupungin olemasta kahden kaupungin vassali
	Tallensin nämäkin tiedot omaan rakenteeseen selkeyden vuoksi


Yksittäisen kaupungin tietorakenteesta on luotu Struct, johon tallennetaan nimi, koordinaatit ja vero. Jokainen näistä alustetaan tyhjään arvoon.

Loin ohjelmaan apufunktiot: 

1.int Tax_from_vassals(TownID id);
	Tämä auttaa kaupungin varallisuuden laskemista. Tulon laskennan rekursiivisyys tapahtuu tässä funktiossa.

2. town_distance_from_coord(TownID id, Coord c);
	Tällä voidaan laskea kaupungin etäisyys annetuista koordinaateista. Tätä käytetään hyväksi origosta, kuin toisista 
	kaupungeista etäisyyttä laskiessa.


Kaupunkien etäisyys origosta lasketaan jo kaupunkia lisätessä ja se lisätään towns_distance_from_origo__ tietorakenteeseen.
Näin jokaisen kaupungin etäisyydestä on aina ajankohtainen tieto. Tässä käytetään apuna town_distance_from_coord funktiota.


Min_ ja max_distance funktiot eivät suorita mitään laskuoperaatioista, vaan tarkastelevat vain tietorakenteen ensimmäistä tai viimeistä alkiota.


Käytössä on myös kaksi declarationia TownsIterator, joka on towns__ tietomuodolle luotu iteraattori
ja VassalsIterator, joka on vassalisuhteille luotu iteraattori. Tämä selkeyttää koodia.