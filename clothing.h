#ifndef CLOTHING_H
#define CLOTHING_H

#include "product.h"
#include <string>
#include <set>
#include "util.h"

class Clothing : public Product {
public:
	Clothing(std::string name, double price, int quantity, std::string brand, std::string size);
	std::set<std::string> keywords() const override;
	std::string displayString() const override;
	void dump(std::ostream& os) const override;

private:
	std::string brand_;
	std::string size_;

};

#endif