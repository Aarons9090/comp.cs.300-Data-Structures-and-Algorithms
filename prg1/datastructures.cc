// Datastructures.cc
//
// Student name: Aaron Hirvi
// Student email: aaron.hirvi@tuni.fi
// Student number: 050320442

#include "datastructures.hh"
#include <random>
#include <cmath>

std::minstd_rand rand_engine; // Reasonably quick pseudo-random generator

template <typename Type>
Type random_in_range(Type start, Type end)
{
    auto range = end-start;
    ++range;

    auto num = std::uniform_int_distribution<unsigned long int>(0, range-1)(rand_engine);

    return static_cast<Type>(start+num);
}

// Modify the code below to implement the functionality of the class.
// Also remove comments from the parameter names when you implement
// an operation (Commenting out parameter name prevents compiler from
// warning about unused parameters on operations you haven't yet implemented.)

Datastructures::Datastructures()
{
    // Write any initialization you need here
}

Datastructures::~Datastructures()
{
    clear_all();
}

unsigned int Datastructures::town_count()
{
    return towns__.size();
}

void Datastructures::clear_all()
{
    towns_distance_from_origo__.clear();
    vassalships__.clear();

    for(auto &pair : towns__){
        delete pair.second;
    }
    towns__.clear();
}

bool Datastructures::add_town(TownID id, const Name &name, Coord location, int tax)
{
    // Tarkastellaa onko kyseisellä id:llä jo kaupunkia
    if(towns__.find(id) == towns__.end()){
        // Jos kaupunkia ei löydetä, luodaan uusi

        Town* new_town = new Town();

        // Lisätään tiedot uuteen kaupunkiin
        new_town->name = name;
        new_town->location = location;
        new_town->tax = tax;

        // Lisätään kaupunki kaupunki mappiin
        towns__.insert( {id,new_town} );

        // tallennetaan etäisyys origosta kaupungin ID:n kanssa
        towns_distance_from_origo__.insert( {town_distance_from_coord(id, {0,0}), id} );

        // Kaupungin luonnin jälkeen palautetaan true
        return true;
    }
    // Jos kaupunki löydettiin, palautetaan false
    return false;
}

Name Datastructures::get_town_name(TownID id)
{
    // Luodaan iteraattori tietorakenteelle
    TownsIterator it;
    // Etsitään kaupunki id:n perusteella
    it = towns__.find(id);

    // Jos kaupunki löytyi, palautetaan sen nimi
    if(it != towns__.end()){
        return it->second->name;
    }

    // Muussa tapauksessa palautetaan NO_NAME
    return NO_NAME;

}

Coord Datastructures::get_town_coordinates(TownID id)
{
    // Luodaan iteraattori tietorakenteelle
    TownsIterator it;
    // Etsitään kaupunki id:n perusteella
    it = towns__.find(id);

    // Jos kaupunki löytyi, palautetaan sen sijainti
    if(it != towns__.end()){
        return it->second->location;
    }

    // Muussa tapauksessa palautetaan NO_COORD
    return NO_COORD;
}

int Datastructures::get_town_tax(TownID id)
{
    // Luodaan iteraattori tietorakenteelle
    TownsIterator it;
    // Etsitään kaupunki id:n perusteella
    it = towns__.find(id);

    // Jos kaupunki löytyi, palautetaan sen verot
    if(it != towns__.end()){
        return it->second->tax;
    }

    // Muussa tapauksessa palautetaan NO_VALUE
    return NO_VALUE;
}

std::vector<TownID> Datastructures::all_towns()
{
    // Luodaan vektori, joka sisältää kaikkien kaupunkien ID:t
    std::vector<TownID> town_vec;
    for(auto& pair : towns__){
        town_vec.push_back(pair.first);
    }

    // Palautetaan vektori
    return town_vec;
}

std::vector<TownID> Datastructures::find_towns(const Name &name)
{
    // Luodaan vektori, joka sisältää kaikkien kaupunkien ID:t, joilla
    // on annettu nimi
    std::vector<TownID> town_vec;

    // Etsitään ja lisätään kaupungit
    for(auto& pair : towns__){
        if(pair.second->name == name){
            town_vec.push_back(pair.first);
        }
    }

    // Palautetaan vektori
    return town_vec;
}

bool Datastructures::change_town_name(TownID id, const Name &newname)
{
    // Etsitään haluttu kaupunki
    TownsIterator it = towns__.find(id);

    // Jos haluttu kaupunki löytyi vaihdetaan sen nimeksi haluttu nimi
    if(it != towns__.end()){
        it->second->name = newname;

        // Operaation onnistuessa palautetaan true
        return true;
    }
    // muussa tapauksessa palautetaan false
    return false;

}

std::vector<TownID> Datastructures::towns_alphabetically()
{
    // Muunnetaan tietomuoto <TownID, Town*>
    // muotoon <Name, TownID>, jotta saadaan map lajiteltua
    std::map<Name, TownID> sorted_towns;
    for(auto& pair : towns__){
        sorted_towns.insert( {pair.second->name, pair.first} );
    }

    // Muunnetaan lajiteltu map vektoriksi
    std::vector<TownID> sorted_ids;
    for(auto& pair2 : sorted_towns){
        sorted_ids.push_back(pair2.second);
    }

    // Palautetaan vektori
    return sorted_ids;
}

int Datastructures::town_distance_from_coord(TownID id, Coord c)
{
    // Lasketaan kaupungin ja koordinaattien etäisyys
    Coord coord = get_town_coordinates(id);
    int x1;
    int y1;
    int x2;
    int y2;

    x1 = coord.x;
    y1 = coord.y;
    x2 = c.x;
    y2 = c.y;

    int distance = sqrt( (pow(x1-x2,2) ) + ( pow(y1-y2,2) ));

    return distance;
}

std::vector<TownID> Datastructures::towns_distance_increasing()
{
    // Palautetaan jo aiemmin lasketut etäisyydet vektoriksi muunnettuna
    std::vector<TownID> distance_sorted_towns;
    for(auto &pair : towns_distance_from_origo__){
        distance_sorted_towns.push_back(pair.second);
    }

    return distance_sorted_towns;
}

TownID Datastructures::min_distance()
{
    // Palauttaa mapin ensimmäisen alkion arvon
    if(towns_distance_from_origo__.size() != 0){
        return towns_distance_from_origo__.begin()->second;
    }

    return NO_TOWNID;
}

TownID Datastructures::max_distance()
{
    // Palauttaa mapin viimeisen alkion arvon
    if(towns_distance_from_origo__.size() != 0){
        return towns_distance_from_origo__.rbegin()->second;
    }

    return NO_TOWNID;

}

bool Datastructures::add_vassalship(TownID vassalid, TownID masterid)
{
    // Katsotaan löytyykö molemmat kaupungit
    TownsIterator it = towns__.find(vassalid);
    if(it != towns__.end()){
        it = towns__.find(masterid);
        if(it != towns__.end()){
            // Jos molemmat löytyvät kaupunki listasta
            // tarkistetaan vielä, ettei kaupunki ole jo vassali
            VassalsIterator vt = vassalships__.find(vassalid);
            if(vt == vassalships__.end()){
                vassalships__.insert({vassalid, masterid});
                return true;
            }
        }
    }
    // Jos toista kaupunkia ei löydy tai se on jo vassali palautetaan false
    return false;
}

std::vector<TownID> Datastructures::get_town_vassals(TownID id)
{
    // Etsitään kaupunki vassalisuhde mapista ja lisätään sen vassali vektoriin
    std::vector<TownID> vassal_vector;
    if(towns__.find(id) != towns__.end()){
        for(auto &pair : vassalships__){
            if(pair.second == id){
                vassal_vector.push_back(pair.first);
            }
        }
    }else{
        vassal_vector.push_back(NO_TOWNID);
    }


    // palautetaan aina sama vektori
    return vassal_vector;
}

std::vector<TownID> Datastructures::taxer_path(TownID id)
{
    // Alustetaan etsittävän kaupungin tietomuoto
    TownID master = id;

    // Vektori johon isännät lisätään
    std::vector<TownID> path;

    // Lisätään aloittava kaupunki vektoriin
    path.push_back(master);

    VassalsIterator vt;
    bool has_vassal = true;

    // Isäntiä etsitään niin kauan kuin niitä löytyy
    while(has_vassal){
        vt = vassalships__.find(master);
        if(vt != vassalships__.end()){
            // Isäntä löytyi, lisätään se vektoriin
            path.push_back(vt->second);
            // Nimitetään uusi isäntä
            master = vt->second;
        }else{
            has_vassal = false;
        }
    }

    // Jos vektorissa on vain yksi alkio, palautetaan NO TOWNID
    if(path.size() == 0){
        return {NO_TOWNID};
    }else if(path.size() == 1 ){
        return path;
    }
    return path;

}

bool Datastructures::remove_town(TownID id)
{
    TownsIterator it = towns__.find(id);
    VassalsIterator vt;
    std::vector<TownID> vassals;

    // Etsitään onko kaupunki olemassa
    if(it != towns__.end()){

        // haetaan kaupungin vassalit
        vassals = get_town_vassals(id);

        // Poistetaan kaupungin vassalien suhteet isäntään
        if(vassals.size() > 0){
            for(TownID &i : vassals){
                vassalships__.erase(vassalships__.find(i));
            }
        }

        // etsitään onko kaupungilla isäntää
        vt = vassalships__.find(id);
        if(vt != vassalships__.end()){

            // kaupungilla oli isäntä, tallennetaan se
            TownID master = vt->second;

            // Poistetaan suhde vassaleista
            vassalships__.erase(vt);

            // Jos kaupungilla on vassaleita, suunnataan niiden verot
            // poistettavan kaupungin isännälle
            if(vassals.size() > 0){
                for(TownID &v : vassals){
                    vassalships__.insert({v,master});
                }
        }
        }

        // Poistetaan kaupunki etäisyystietorakenteesta
        for(std::multimap<int, TownID>::iterator i = towns_distance_from_origo__.begin();
            i != towns_distance_from_origo__.end(); i++){
            if(i->second == id){
                towns_distance_from_origo__.erase(i);
                break;
            }
        }

        // Poistetaan kaupunki
        Town* town = it->second;
        towns__.erase(it);
        delete town;
        return true;
    }
    // kaupunkia ei löytnyny
    return false;

}

std::vector<TownID> Datastructures::towns_nearest(Coord coord)
{
    std::multimap<int, TownID> distance_sorted_map;
    std::vector<TownID> distance_sorted_vector;
    int distance;

    // Lasketaan etäisyydet jokaiselle kaupungille käyttäen
    // town_distance_from_coord() apufunktiota
    // Lisätään etäisyydet ensin multimappiin, jossa ne lajitellaan etäisyyden perusteella
    for(auto &pair : towns__){
        distance = town_distance_from_coord(pair.first, coord);
        distance_sorted_map.insert({distance, pair.first});
    }

    // Muunnetaan multimapin TownID:t vektoriksi
    for(auto &i : distance_sorted_map){
        distance_sorted_vector.push_back(i.second);
    }

    return distance_sorted_vector;
}

std::vector<TownID> Datastructures::longest_vassal_path(TownID id)
{
    std::vector<TownID> path1;
    std::vector<TownID> path2;

    // Määritellään pisin reitti rekursiolla
    for(auto &pair : vassalships__){
        if(pair.second == id){
            path2 = longest_vassal_path(pair.first);
            if(path2.size() > path1.size()){
                // Jos 2. reitti on pidempi kuin 1. korvataan 1=2
                // ja alustetaan 2.
                path1 = path2;
                path2.clear();
            }
        }
    }
    path1.insert(path1.begin(), id);
    return path1;
}

int Datastructures::tax_from_vassals(TownID id)
{
    int income_tax = 0;
    TownsIterator it = towns__.find(id);
    std::vector<TownID> vassals = get_town_vassals(id);

    // Lasketaan tuleva raha rekursiivisesti
    if(vassals.size() != 0){
        for(TownID &town : vassals){
            income_tax += 0.1*tax_from_vassals(town);
        }
    }
    income_tax += it->second->tax;
    return income_tax;
}

int Datastructures::total_net_tax(TownID id)
{

    int total_tax = 0;
    TownsIterator it = towns__.find(id);

    if(it == towns__.end()){
        return NO_VALUE;
    }

    // Kutsutaan apufunktiota laskeaksemme tulevan rahan määrä
    total_tax += tax_from_vassals(id);

    // Jos kaupungilla on vassali, nettovarallisuudesta otetaan 10% pois
    if(vassalships__.find(id) != vassalships__.end()){
        return total_tax - (total_tax * 0.1);
    }
    return total_tax;
}
