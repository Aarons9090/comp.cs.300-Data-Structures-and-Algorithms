// Datastructures.hh
//
// Student name:
// Student email:
// Student number:

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <map>
#include <queue>
#include <unordered_set>
#include <stack>

// Types for IDs
using TownID = std::string;
using Name = std::string;

// Return values for cases where required thing was not found
TownID const NO_TOWNID = "----------";

// Return value for cases where integer values were not found
int const NO_VALUE = std::numeric_limits<int>::min();

// Return value for cases where name values were not found
Name const NO_NAME = "!!NO_NAME!!";

// Type for a coordinate (x, y)
struct Coord
{
    int x = NO_VALUE;
    int y = NO_VALUE;
};


// Type for a distance (in metres)
using Distance = int;

// Example: Defining == and hash function for Coord so that it can be used
// as key for std::unordered_map/set, if needed
inline bool operator==(Coord c1, Coord c2) { return c1.x == c2.x && c1.y == c2.y; }
inline bool operator!=(Coord c1, Coord c2) { return !(c1==c2); } // Not strictly necessary


struct CoordHash
{
    std::size_t operator()(Coord xy) const
    {
        auto hasher = std::hash<int>();
        auto xhash = hasher(xy.x);
        auto yhash = hasher(xy.y);
        // Combine hash values (magic!)
        return xhash ^ (yhash + 0x9e3779b9 + (xhash << 6) + (xhash >> 2));
    }
};

// Example: Defining < for Coord so that it can be used
// as key for std::map/set
inline bool operator<(Coord c1, Coord c2)
{
    if (c1.y < c2.y) { return true; }
    else if (c2.y < c1.y) { return false; }
    else { return c1.x < c2.x; }
}

// Return value for cases where coordinates were not found
Coord const NO_COORD = {NO_VALUE, NO_VALUE};

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;

// Värit graafialgoritmeja varten
enum Color {White, Grey, Black};

// Tietomuoto kaupunkien tallennukseen
struct Town {
    Name name = NO_NAME;
    Coord location = NO_COORD;
    int tax = NO_VALUE;

    // Lisää arvoja graafialgoritmeja varten
    TownID id = NO_TOWNID;
    Color color = White;
    Distance dist = NO_VALUE;
    Distance dist_estimate = NO_VALUE;
    Town* pi = nullptr;
    std::unordered_set<Town*> adj_towns;
};



// This exception class is there just so that the user interface can notify
// about operations which are not (yet) implemented
class NotImplemented : public std::exception
{
public:
    NotImplemented() : msg_{} {}
    explicit NotImplemented(std::string const& msg) : msg_{msg + " not implemented"} {}

    virtual const char* what() const noexcept override
    {
        return msg_.c_str();
    }
private:
    std::string msg_;
};


// This is the class you are supposed to implement

class Datastructures
{
public:
    Datastructures();
    ~Datastructures();

    // Estimate of performance:
        // Vakio eli O(1)
    // Short rationale for estimate:
        // Funktio palauttaa mapin .size() operaation, joka on vakio
    unsigned int town_count();

    // Estimate of performance:
        // Lineaarinen eli O(n)
    // Short rationale for estimate:
        // Yksittäisen elementin poisto on vakioaikainen operaatio
        // Se toistetaan loopissa n kertaa jokaiselle towns__:in alkiolle
    void clear_all();

    // Estimate of performance:
        // O(n), Θ(1)
    // Short rationale for estimate:
        // Kaupungin inserttaus unordered mappiin on huonoimmassa tapauksessa
        // O(n) mutta keskiverto tapauksessa Θ(1).
        //town_distance_from_coord on vakio aikainen
    bool add_town(TownID id, Name const& name, Coord coord, int tax);

    // Estimate of performance:
        // O(n), Θ(1)
    // Short rationale for estimate:
        // Unordered mapin find operaatio on huonoimmassa tapauksessa
        // O(n), mutta keskimäärin Θ(1)
    Name get_town_name(TownID id);

    // Estimate of performance:
        // O(n), Θ(1)
    // Short rationale for estimate:
        // Unordered mapin find operaatio on huonoimmassa tapauksessa
        // O(n), mutta keskimäärin Θ(1)
    Coord get_town_coordinates(TownID id);

    // Estimate of performance:
        // O(n), Θ(1)
    // Short rationale for estimate:
        // Unordered mapin find operaatio on huonoimmassa tapauksessa
        // O(n), mutta keskimäärin Θ(1)
    int get_town_tax(TownID id);

    // Estimate of performance:
        // O(n)
    // Short rationale for estimate:
        // Vektorin pushback operaatio on vakioaikainen.
        // Käydään alkioita läpi towns__.size() eli n kertaa
    std::vector<TownID> all_towns();

    // Estimate of performance:
        // O(n)
    // Short rationale for estimate:
        // Vektorin pushback operaatio on vakioaikainen.
        // Käydään alkioita läpi towns__.size() eli n kertaa
    std::vector<TownID> find_towns(Name const& name);

    // Estimate of performance:
        // O(n), Θ(1)
    // Short rationale for estimate:
        // Unordered mapin find operaatio on huonoimmassa tapauksessa
        // O(n), mutta keskimäärin Θ(1)
    bool change_town_name(TownID id, Name const& newname);

    // Estimate of performance:
        // O(nlog(n)
    // Short rationale for estimate:
        // Mappiin lisäys on tehokkuudeltaan O(log(n)).
        // tämä toteutetaan towns__.size() eli n kertaa
    std::vector<TownID> towns_alphabetically();

    // Estimate of performance:
        // O(1)
    // Short rationale for estimate:
        // Suoritettavat operaatiot ovat vakioaikaisia
    std::vector<TownID> towns_distance_increasing();

    // Estimate of performance:
        // O(1)
    // Short rationale for estimate:
        // size operaatio multimapille on vakioaikainen
    TownID min_distance();

    // Estimate of performance:
        // O(1)
    // Short rationale for estimate:
        // size operaatio multimapille on vakioaikainen
    TownID max_distance();

    // Estimate of performance:
         // joskus O(n) mutta keskiverto tapauksessa usein Θ(1).
    // Short rationale for estimate:
        // Find ja insert operaatiot ovat yleensä vakioaikaisia
        // mutta joissain tapauksissa O(n)
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance:
         // O(n)
    // Short rationale for estimate:
        // Vektorin pushback operaatio on vakioaikainen.
        // Käydään alkioita läpi vassalships__.size() eli n kertaa
    std::vector<TownID> get_town_vassals(TownID id);

    // Estimate of performance:
        // Θ(n), O(n^2)
    // Short rationale for estimate:
        // while silmukkaa toistetaan niin kauan kuin kaupungilla on vassaleita
        // eli n kertaa.
        // Find operaatio on usein Θ(1) mutta joskus O(n)
    std::vector<TownID> taxer_path(TownID id);

    // Non-compulsory phase 1 operations

    // Estimate of performance:
        // O(n^2), Θ(n)
    // Short rationale for estimate:
        // Suhteen poistaminen on yksittäiselle elementille Θ(1), mutta huonoimmassa
        // tapauksessa O(n). Tämä toistetaan n kertaa
        // Suhteen inserttaus unordered mappiin on huonoimmassa tapauksessa
        // O(n) mutta keskiverto tapauksessa Θ(1). Tämä toistetaan n kertaa
    bool remove_town(TownID id);

    // Estimate of performance:
        // O(nlog(n))
    // Short rationale for estimate:
        // Multimappiin inserttaus on yleisesti O(log(n))
        // tämä toeutetaan n kertaa
    std::vector<TownID> towns_nearest(Coord coord);

    // Estimate of performance:
        // O(n^2)
    // Short rationale for estimate:
        // rekursiivinen funktio kutsuu itseään n kertaa
        // ja for loop kutsuu itseään n kertaa
    std::vector<TownID> longest_vassal_path(TownID id);

    // Estimate of performance:
        // O(n^2) ?
    // Short rationale for estimate:
        // Funktio kutsuu apufunktiota tax_from_vassals
        // jonka tehokkuus on O(n^2)
    int total_net_tax(TownID id);

    // Estimate of performance:
        // O(1)
    // Short rationale for estimate:
        // funktiossa suoritetaan vain vakioaikaisia operaatioita
    int town_distance_from_coord(TownID id, Coord c);

    // Estimate of performance:
        // O(n^2) ?
    // Short rationale for estimate:
        // Funktio kutsuu itseään n kertaa for loopissa jota kutsutaan n kertaa
    int tax_from_vassals(TownID id);

    // Phase 2 operations

    // Estimate of performance:
        // O(n)
    // Short rationale for estimate:
        // Lineaarinen, suoritetaan n=kaupunkien määrän verran
    void clear_roads();

    // Estimate of performance:
        // O(n^2) vaikka ei olekkaan mukana tehokkuustestissä
    // Short rationale for estimate:
        // toteutetaan jokaisen kaupungin naapurin verran
    std::vector<std::pair<TownID, TownID>> all_roads();

    // Estimate of performance:
        // Huonoin tapaus O(n), keskimääräinen Θ(1)
    // Short rationale for estimate:
        // town_exists ja muutkin find operaatiot ovat
        // Huonoimmassa tapauksessa O(n), mutta keskimäärärin Θ(1)
    bool add_road(TownID town1, TownID town2);

    // Estimate of performance:
        // O(n)
    // Short rationale for estimate:
        // toistetaan kaupungin naapureiden
    std::vector<TownID> get_roads_from(TownID id);

    // Estimate of performance:
        // O(n+k) n = solmu, k = kaari
    // Short rationale for estimate:
        // DFS toteutuksen tehokkuus
    std::vector<TownID> any_route(TownID fromid, TownID toid);

    // Non-compulsory phase 2 operations

    // Estimate of performance:
        // pahin tapaus o(n), keskimäärin Θ(1)
    // Short rationale for estimate:
        // find operaatiot ja exists funktio ovat keskimäärin Θ(1)
    bool remove_road(TownID town1, TownID town2);

    // Estimate of performance:
        // O(n+k) n = solmu, k = kaari
    // Short rationale for estimate:
        // BFS toteutuksen tehokkuus
    std::vector<TownID> least_towns_route(TownID fromid, TownID toid);

    // Estimate of performance:
        // O(n+k) n = solmu, k = kaari
    // Short rationale for estimate:
        // DFS toteutuksen tehokkuus
    std::vector<TownID> road_cycle_route(TownID startid);

    // Estimate of performance:
        // O((n+k) log)
    // Short rationale for estimate:
        // dijkstran/A* algortimin tehokkuus
    std::vector<TownID> shortest_route(TownID fromid, TownID toid);

    // Estimate of performance:
       // ei toteutettu
    // Short rationale for estimate:
    Distance trim_road_network();

    // Estimate of performance:
        // huonoin tapaus O(n), keskimääräinen Θ(1)
    // Short rationale for estimate:
    bool town_exists(TownID town);

    // Estimate of performance:
        // O(1)
    // Short rationale for estimate:
        // vain vakioaikaisia operaatioita
    void relax_a(Town* u, Town* v, Town* g);

    // Estimate of performance:
        // O(n)
    // Short rationale for estimate:
        // toistetaan kaupunkiketjun pituuden verran
    std::vector<TownID> get_path_recr(Town* node, std::vector<TownID> &town_vec);

    // Estimate of performance:
        // O(1)
    // Short rationale for estimate:
        // vain vakioaikaisia operaatioita
    int distance_between_town_pointers(Town* town1, Town* town2);


private:

    // Kaupungit
    std::unordered_map<TownID,Town*> towns__;

    // Kaupunkien etäisyydet origosta
    std::multimap<int, TownID> towns_distance_from_origo__;

    // vassalisuhteet
    // <Vassali, Master>
    std::unordered_map<TownID, TownID> vassalships__;

    using TownsIterator = std::unordered_map<TownID, Town*>::iterator;
    using VassalsIterator =  std::unordered_map<TownID, TownID>::iterator;


};
#endif // DATASTRUCTURES_HH
