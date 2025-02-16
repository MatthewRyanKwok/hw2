#include "movie.h"
#include "util.h"
#include <sstream>
#include <set>

Movie::Movie(std::string name, double price, int quantity, std::string rating, std::string genre)
    : Product("movie", name, price, quantity), rating_(rating), genre_(genre) //constructor
{
   
}

std::set<std::string> Movie::keywords() const {
    std::set<std::string> keywords;

    keywords.insert(convToLower(genre_)); //inserts genre when it is converted to lowercase

    std::set<std::string> tKeywords = parseStringToWords(getName()); //parses name of movie

    keywords.insert(tKeywords.begin(), tKeywords.end()); //inserts to the set

    return keywords;
}

std::string Movie::displayString() const {
    std::ostringstream info;

    info << getName() << "\n" //displays info
    << "Genre: " << genre_ << " Rating: " << rating_ << "\n" 
    << price_ << " " << qty_ << " left.";

    return info.str();
}

void Movie::dump(std::ostream& os) const {
    // Print movie information in database format
    os << "movie\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n"
    << genre_ << "\n" << rating_ << std::endl;
}