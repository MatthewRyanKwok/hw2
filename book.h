#ifndef BOOK_H
#define BOOK_H

#include "product.h"
#include <string>
#include "util.h"

class Book : public Product {
public:
	Book(const std::string& title, const std::string& author, double price, int quantity, const std::string& ISBN);
	std::set<std::string> keywords() const override;
	std::string displayString() const override;
	void dump(std::ostream& os) const override;

private:
	std::string ISBN_;
	std::string author_;
};




#endif