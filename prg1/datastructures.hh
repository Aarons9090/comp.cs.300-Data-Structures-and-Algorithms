// Datastructures.hh
//
// Student name: Aaron Hirvi
// Student email: aaron.hirvi@tuni.fi
// Student number: 050320442

#ifndef DATASTRUCTURES_HH
#define DATASTRUCTURES_HH

#include <string>
#include <vector>
#include <tuple>
#include <utility>
#include <limits>
#include <functional>
#include <exception>
#include <unordered_map>
#include <map>
#include <math.h>


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

// Type for a distance (in metres)
using Distance = int;

// Return value for cases where Distance is unknown
Distance const NO_DISTANCE = NO_VALUE;


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
        // Yksitt??isen elementin poisto on vakioaikainen operaatio
        // Se toistetaan loopissa n kertaa jokaiselle towns__:in alkiolle
    void clear_all();

    // Estimate of performance:
        // O(n), ??(1)
    // Short rationale for estimate:
        // Kaupungin inserttaus unordered mappiin on huonoimmassa tapauksessa
        // O(n) mutta keskiverto tapauksessa ??(1).
        //town_distance_from_coord on vakio aikainen
    bool add_town(TownID id, Name const& name, Coord coord, int tax);

    // Estimate of performance:
        // O(n), ??(1)
    // Short rationale for estimate:
        // Unordered mapin find operaatio on huonoimmassa tapauksessa
        // O(n), mutta keskim????rin ??(1)
    Name get_town_name(TownID id);

    // Estimate of performance:
        // O(n), ??(1)
    // Short rationale for estimate:
        // Unordered mapin find operaatio on huonoimmassa tapauksessa
        // O(n), mutta keskim????rin ??(1)
    Coord get_town_coordinates(TownID id);

    // Estimate of performance:
        // O(n), ??(1)
    // Short rationale for estimate:
        // Unordered mapin find operaatio on huonoimmassa tapauksessa
        // O(n), mutta keskim????rin ??(1)
    int get_town_tax(TownID id);

    // Estimate of performance:
        // O(n)
    // Short rationale for estimate:
        // Vektorin pushback operaatio on vakioaikainen.
        // K??yd????n alkioita l??pi towns__.size() eli n kertaa
    std::vector<TownID> all_towns();

    // Estimate of performance:
        // O(n)
    // Short rationale for estimate:
        // Vektorin pushback operaatio on vakioaikainen.
        // K??yd????n alkioita l??pi towns__.size() eli n kertaa
    std::vector<TownID> find_towns(Name const& name);

    // Estimate of performance:
        // O(n), ??(1)
    // Short rationale for estimate:
        // Unordered mapin find operaatio on huonoimmassa tapauksessa
        // O(n), mutta keskim????rin ??(1)
    bool change_town_name(TownID id, Name const& newname);

    // Estimate of performance:
        // O(nlog(n)
    // Short rationale for estimate:
        // Mappiin lis??ys on tehokkuudeltaan O(log(n)).
        // t??m?? toteutetaan towns__.size() eli n kertaa
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
         // joskus O(n) mutta keskiverto tapauksessa usein ??(1).
    // Short rationale for estimate:
        // Find ja insert operaatiot ovat yleens?? vakioaikaisia
        // mutta joissain tapauksissa O(n)
    bool add_vassalship(TownID vassalid, TownID masterid);

    // Estimate of performance:
         // O(n)
    // Short rationale for estimate:
        // Vektorin pushback operaatio on vakioaikainen.
        // K??yd????n alkioita l??pi vassalships__.size() eli n kertaa
    std::vector<TownID> get_town_vassals(TownID id);

    // Estimate of performance:
        // ??(n), O(n^2)
    // Short rationale for estimate:
        // while silmukkaa toistetaan niin kauan kuin kaupungilla on vassaleita
        // eli n kertaa.
        // Find operaatio on usein ??(1) mutta joskus O(n)
    std::vector<TownID> taxer_path(TownID id);

    // Non-compulsory phase 1 operations

    // Estimate of performance:
        // O(n^2), ??(n)
    // Short rationale for estimate:
        // Suhteen poistaminen on yksitt??iselle elementille ??(1), mutta huonoimmassa
        // tapauksessa O(n). T??m?? toistetaan n kertaa
        // Suhteen inserttaus unordered mappiin on huonoimmassa tapauksessa
        // O(n) mutta keskiverto tapauksessa ??(1). T??m?? toistetaan n kertaa
    bool remove_town(TownID id);

    // Estimate of performance:
        // O(nlog(n))
    // Short rationale for estimate:
        // Multimappiin inserttaus on yleisesti O(log(n))
        // t??m?? toeutetaan n kertaa
    std::vector<TownID> towns_nearest(Coord coord);

    // Estimate of performance:
        // O(n^2)
    // Short rationale for estimate:
        // rekursiivinen funktio kutsuu itse????n n kertaa
        // ja for loop kutsuu itse????n n kertaa
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
        // Funktio kutsuu itse????n n kertaa for loopissa jota kutsutaan n kertaa
    int tax_from_vassals(TownID id);

private:
    // Add stuff needed for your class implementation here
    struct Town {
        Name name = NO_NAME;
        Coord location = NO_COORD;
        int tax = NO_VALUE;
    };

    // Kaupungit
    std::unordered_map<TownID,Town*> towns__;

    // Kaupunkien et??isyydet origosta
    std::multimap<int, TownID> towns_distance_from_origo__;

    // vassalisuhteet
    // <Vassali, Master>
    std::unordered_map<TownID, TownID> vassalships__;

    using TownsIterator = std::unordered_map<TownID, Town*>::iterator;
    using VassalsIterator =  std::unordered_map<TownID, TownID>::iterator;
};

#endif // DATASTRUCTURES_HH
