#include "mydatastore.h"

MyDataStore::MyDataStore()
{
	//empty constructor
} 

MyDataStore::~MyDataStore() { //destructor
	std::set<Product*>::iterator it;
	for (it = products_.begin(); it != products_.end(); it++) { //deletes products
		delete* it; 
	}
	for (std::map<std::string, User*>::iterator user = users_.begin(); user != users_.end(); user++) { //deletes users
		delete user->second; 
	}
}
void MyDataStore::addProduct(Product* p) {
	products_.insert(p); //adds product to product set
	std::set<std::string> keywords = p->keywords();
	for (std::set<std::string>::iterator it = keywords.begin(); it != keywords.end(); it++) {
		keywordMap_[*it].insert(p);  //map each keyword to product
	}
}

void MyDataStore::addUser(User* u) {
	users_[u->getName()] = u; //this adds the user to the users_ map
}

std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
	std::set<std::string> sWords; //for search words
	for (size_t i = 0; i < terms.size(); i++) {
		sWords.insert(convToLower(terms[i]));  //terms to lowercase
	}

	std::set<Product*> resultSet;
	bool first = true;

	for (std::set<std::string>::iterator it = sWords.begin(); it != sWords.end(); it++) { //iterates through sWords
		std::map<std::string, std::set<Product*>>::iterator mapIt = keywordMap_.find(*it); //finds current keyword
		if (mapIt != keywordMap_.end()) {
			if (first) { //if this is first keyword, initialize the result set
				resultSet = mapIt->second;  
				first = false;
			}
			else {
				if (type == 0) {  //and search
					resultSet = setIntersection(resultSet, mapIt->second);
				}
				else {  //or search
					resultSet = setUnion(resultSet, mapIt->second);
				}
			}
		}
		else if (type == 0) {
			//result empty if and search done and nothing is found
			return std::vector<Product*>();
		}
	}

	return std::vector<Product*>(resultSet.begin(), resultSet.end());
}


void MyDataStore::dump(std::ostream& ofile) {
	ofile << "<products>" << std::endl;
	std::set<Product*>::iterator pIt;
	for (pIt = products_.begin(); pIt != products_.end(); pIt++) { //dump each product
		(*pIt)->dump(ofile);
	}
	ofile << "</products>" << std::endl; ofile << "<users>" << std::endl;
	std::map<std::string, User*>::iterator uIt;
	for (uIt = users_.begin(); uIt != users_.end(); uIt++) { //dump each user
		uIt->second->dump(ofile);
	}
	ofile << "</users>" << std::endl;
}

void MyDataStore::addToCart(std::string username, int hitResultIndex, const std::vector<Product*>& hits) {
	username = convToLower(username);//username is conv to lowercase

	//checks user and hit index validity
	if (users_.find(username) == users_.end() || hitResultIndex < 0 || hitResultIndex >= static_cast<int>(hits.size())) {
		std::cout << "Invalid request" << std::endl;
		return;
	}

	carts_[username].push_back(hits[hitResultIndex]);//adds selected product to cart
}


std::vector<Product*> MyDataStore::viewCart(std::string username) {
	std::vector<Product*> cartProducts; //for products in cart

	std::string uLow = convToLower(username); //makes user lowercase

	if (users_.find(uLow) == users_.end()) { //looks if user is in users_ map
		std::cout << "Invalid username" << std::endl; 
		return cartProducts;
	}
	if (carts_.find(uLow) == carts_.end() || carts_.at(uLow).empty()) { //checks emptiness
		std::cout << "Cart is empty" << std::endl;
		return cartProducts;
	}

	const std::vector<Product*>& cart = carts_.at(uLow);
	cartProducts = cart; //cart copied to cartProducts vec

	for (size_t i = 0; i < cart.size(); i++) { //iterates over the cart products
		std::cout << "Item " << i + 1 << std::endl;        
		std::cout << cart[i]->displayString() << std::endl;  //displays product details     
		std::cout << std::endl;
	}

	return cartProducts;
}



void MyDataStore::buyCart(std::string username) {
	std::string uLow = convToLower(username); //converts username to lowercase
	if (users_.find(uLow) == users_.end()) { //checks user
		std::cout << "Invalid username" << std::endl; //if not in map, invalid username
		return;
	}

	User* user = users_[uLow];
	std::vector<Product*>& cart = carts_[uLow]; //gets the user's cart
	std::vector<Product*>::iterator pIt; //product iterator
	for (pIt = cart.begin(); pIt != cart.end(); pIt++) { //iterates through the cart
		Product* prod = *pIt; //dereferences product iterator

		if (prod->getQty() > 0 && user->getBalance() >= prod->getPrice()) { //checks if user has credit/prod is available
			prod->subtractQty(1); //reduces prod qty by 1
			user->deductAmount(prod->getPrice()); //lowers the money in user's balance
			cart.erase(pIt); //product removed from the cart
			--pIt; 
		}
	}
}