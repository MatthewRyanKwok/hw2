#include "clothing.h"
#include <sstream>


Clothing::Clothing(std::string name, double price, int quantity, std::string brand, std::string size)
    : Product("clothing", name, price, quantity), brand_(brand), size_(size) //constructor
{

}

std::set<std::string> Clothing::keywords() const {
    std::set<std::string> result;
    std::set<std::string> bKeywords = parseStringToWords(brand_); //keywords for brand
    std::set<std::string> nKeywords = parseStringToWords(getName()); //keywords for name
    result.insert(bKeywords.begin(), bKeywords.end()); //inserts brand keywords
    result.insert(nKeywords.begin(), nKeywords.end()); //inserts name keywords

    return result; 
}

std::string Clothing::displayString() const { 
    std::ostringstream info;
    info << name_ << "\n" << "Size: " << size_ << " Brand: " << brand_ << "\n" << price_ << " " << qty_ << " left.";
    return info.str();
}

void Clothing::dump(std::ostream& os) const { 
    os << "clothing" << std::endl; os << name_ << std::endl; os << price_ << std::endl; os << qty_ << std::endl;
    os << size_ << std::endl; os << brand_ << std::endl;
}
