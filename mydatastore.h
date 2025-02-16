#ifndef MYDATASTORE_H
#define MYDATASTORE_H

#include "datastore.h"
#include "util.h"
#include "user.h"
#include "product.h"
#include <map>
#include <set>
#include <string>
#include <vector>

class MyDataStore : public DataStore {
public:
	MyDataStore();
	~MyDataStore();
	void addProduct(Product* p) override;
	void addUser(User* u) override;
	std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
	void addToCart(std::string username, int hitResultIndex, const std::vector<Product*>& hits);
	std::vector<Product*> viewCart(std::string username);
	void buyCart(std::string username);
	void dump(std::ostream& ofile) override;
private:
	std::set<Product*> products_;
	std::map<std::string, User*> users_;
	std::map<std::string, std::set<Product*>> keywordMap_;
	std::map<std::string, std::vector<Product*>> carts_;
};

#endif