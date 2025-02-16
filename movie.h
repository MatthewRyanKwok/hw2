#ifndef MOVIE_H
#define MOVIE_H

#include "product.h"
#include <string>
#include <set>

class Movie : public Product {
public:
    Movie(std::string name, double price, int quantity, std::string rating, std::string genre);
    std::set<std::string> keywords() const override;
    std::string displayString() const override;
    void dump(std::ostream& os) const override;

private:
    std::string rating_;
    std::string genre_;
};

#endif
