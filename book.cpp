#include "book.h"
#include <sstream>
#include <set>

Book::Book(const std::string& title, const std::string& author, double price, int quantity, const std::string& ISBN)
    : Product("book", title, price, quantity), ISBN_(ISBN), author_(author) //constructor
{

}


std::set<std::string> Book::keywords() const {
    std::set<std::string> res = parseStringToWords(author_);
    std::set<std::string> tKeywords = parseStringToWords(getName()); //parses title, gets keywords
    res.insert(tKeywords.begin(), tKeywords.end());
    res.insert(ISBN_); //isbn is one keyword so added after
    return res;
}

std::string Book::displayString() const {
    std::ostringstream info;
    info << name_ << "\nAuthor: " << author_ << " ISBN: " << ISBN_ << "\n"
        << price_ << " " << qty_ << " left.";
    return info.str();
}

void Book::dump(std::ostream& os) const {
    os << "book\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n"
        << ISBN_ << "\n" << author_ << std::endl;
}