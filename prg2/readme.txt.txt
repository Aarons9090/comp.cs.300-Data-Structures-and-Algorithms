Uudet .hh tiedoston osat:

1. Towns structiin on lisätty graafialgoritmeja varten
	- Väri
	- Naapurit (tiet)
	- Kaupungin id
	- etäisyys
	- etäisyyden arvio
	- pi (kaupunki josta kaupunkiin saavuttiin)

2. enum Color, joka antaa kaupungille värin

Käytetyt graafialgoritmit:

1. any_route - DFS
2. least_towns_route - BFS
3. cycle_route - DFS
4. shortest_route - A*


Itseluotuja apufunktioita

1. std::vector<TownID> get_path_recr(Town* node, std::vector<TownID> &town_vec);
	- suoritetaan graafialgoritmin suorituksen jälkeen.
	- hakee kaupunkiketjun jäsenet rekursiivisesti
	- rekursio välttää vektorin reversauksen ja on ajallisesti hieman nopeampi

2. int distance_between_town_pointers(Town* town1, Town* town2);
	- Laskee kahden osoittimen etäisyyden

3. void relax_a(Town* u, Town* v, Town* g);
	- Apufunktio A* funktiolle

4. bool town_exists(TownID town);
	- tarkistetaan että kaupunki on olemassa