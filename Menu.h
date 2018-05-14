#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>

#include "Ingredient.h"
#include "Pizza.h"
#include "Parser.h"

#define _STR(s) #s
#define STR(s) _STR(s)

template<class T>
class Menu;

template<class T>
class Menu
{
public:
	struct Order
	{
		int id;
		int size = -1;
		size_t qty = 1;
		bool isOnline = false;
		double distance = 0;

		Order(const int id, const int size = static_cast<int>(Menu::OrderSize::S),  
			const size_t qty = 1, const bool onl = false, const double dist = 0)
			: id(id), size(size), qty(qty), isOnline(onl), distance(dist){}
	};

private:
	//characteristic of order sizes
	enum class OrderSize : int 
	{ 
		S = -1, //small (base)
		M,		//medium
		L,		//large
		NUM		//number of additional sizes
	};

	std::vector<Ingredient> IngredientRef;
	std::vector<T> ProductRef;

	//price modifiers
	std::vector<double> mods;
	
	//tracks product sales
	std::vector<Product::Point> Ledger;

	//tracks Vege product IDs
	std::set<int> VLedger;

	//generator files directory
	std::string genDir;

	//price of workmanship
	const double workPrice = 5.;

public:

	inline Menu()
	{
		genDir = std::string(STR(ASSETS)) + "/gen/";
		loadIngredients();
		loadProducts();
		initLedgers();

		mods.push_back(1.6);
		mods.push_back(2.0);
	};

	inline ~Menu() {};
	
	inline void showIngredients(std::ostream & out = std::cout)
	{
		if (IngredientRef.empty())
		{
			out << "Nu exista ingrediente. \n";
			return;
		}
		for (const auto& ing : IngredientRef)
		{
			//TODO alter after test
			out << ing <<": $"<<ing.getPrice()<<"\n";
		}
	}
	
	inline void showProducts(std::ostream & out = std::cout) const
	{
		if (ProductRef.empty())
		{
			out << "Nu exista produse. \n";
			return;
		}
		
		for (size_t i=0; i < ProductRef.size(); i++)
		{
			out << i + 1 << ".\t" << ProductRef[i] << " \n";
		}
	}

	inline const size_t getSize() const { return ProductRef.size(); }
	inline const size_t getOrderSizes() const { return static_cast<int>(OrderSize::NUM); }
	inline void showOrderSizes(std::ostream & out = std::cout) const
	{
		for (int i = 0; i <= getOrderSizes(); i++)
		{
			switch (i - 1)
			{
				case static_cast<int>(OrderSize::S) :
					out << "1. " << "Mica.\n";
					break;
					case static_cast<int>(OrderSize::M) :
						out << "2. " << "Medie.\n";
						break;
						case static_cast<int>(OrderSize::L) :
							out << "3. " << "Mare.\n";
							break;
							case static_cast<int>(OrderSize::NUM) :
								break;
			}
		}
	}


	void placeOrder(const int productID, const int size = -1, const int qty = 1, const bool isOnline = false, const double distance = 9.);
	
	void placeOrder(const Order & order);

	void showSales(std::ostream & out = std::cout);

	Menu & operator+=(const Order& toPlace);

private:
	void loadIngredients();
	void loadProducts();
	void initLedgers();

};

template<>
void Menu<Pizza>::placeOrder(const int productID, const int size, const int qty, const bool isOnline, const double distance)
{
	if (productID >= 0 && productID < Ledger.size() && !Ledger.empty())
	{
		double orderPrice = ProductRef[productID].getPrice() + workPrice;

		auto qt = qty;
		if (qty < 1) { qt = 1; }

		if (size <= static_cast<int>(OrderSize::S) || size > static_cast<int>(OrderSize::L))
		{
			orderPrice *= qt;
		}
		else
		{
			orderPrice = orderPrice * mods[size] * qt;
		}

		//change entire order's price
		if (isOnline)
		{
			orderPrice += 0.05*orderPrice*(distance / 10);
		}

		Ledger[productID].x += qt;
		Ledger[productID].y += orderPrice;

	}
}

template<>
void Menu<Pizza>::placeOrder(const Order & ord)
{
	if (ord.id >= 0 && ord.id < Ledger.size() && !Ledger.empty())
	{
		double orderPrice = ProductRef[ord.id].getPrice() + workPrice;

		auto qt = ord.qty;
		if (ord.qty < 1) { qt = 1; }

		if (ord.size <= static_cast<int>(OrderSize::S) || ord.size > static_cast<int>(OrderSize::L))
		{
			orderPrice *= qt;
		}
		else
		{
			orderPrice = orderPrice * mods[ord.size] * qt;
		}

		//change entire order's price
		if (ord.isOnline)
		{
			orderPrice += 0.05*orderPrice*(ord.distance / 10);
		}

		Ledger[ord.id].x += qt;
		Ledger[ord.id].y += orderPrice;

	}
}


template<>
void Menu<Pizza>::showSales(std::ostream & out)
{
	double vegTotal = 0., total = 0.;

	for (size_t i = 0; i < Ledger.size(); i++)
	{
		if (Ledger[i].x && !VLedger.count(i))
		{
			out << ProductRef[i].getName() << " x " << Ledger[i].x << " : $"<<Ledger[i].y<<"\n";
			total += Ledger[i].y;
		}
	}

	for (const auto &i : VLedger)
	{
		if (Ledger[i].x)
		{
			out << ProductRef[i].getName() << " x " << Ledger[i].x << " : $" << Ledger[i].y << "\n";
			vegTotal += Ledger[i].y;
		}
	}

	total += vegTotal;

	if (!total)
	{
		out << "Monentan nu s-a inregistrat nicio vanzare. \n";
	}

	else
	{
		out << "\nTotal vanzari: $" << total << "\n";
	}

	if (vegTotal)
	{
		out << "\nTotal vanzari produse Vegetariene: $" << vegTotal << "\n";
	}
}

template<>
void Menu<Pizza>::loadIngredients()
{
	Parser<Ingredient> P1(genDir + "pizzaIng.in");
	P1.parseFile();
	std::vector<std::string> src;
	auto status = P1.getParsedData(src);

	if (status != Parser<Ingredient>::Status::PARSEOK)
	{
		return;
	}

	for (const std::string &elem : src)
	{
		std::istringstream iss(elem);
		Ingredient ingToAdd;
		iss >> ingToAdd;
		ingToAdd.setID(IngredientRef.size());

		IngredientRef.push_back(ingToAdd);
	}
}

template<>
void Menu<Pizza>::loadProducts()
{
	Parser<Pizza> P1(genDir + "pizza.in");
	P1.parseFile();

	std::vector<std::string> toAdd;
	auto status = P1.getParsedData(toAdd);

	if (status != Parser<Pizza>::Status::PARSEOK) { return; }

	//for every pizza
	for (size_t i = 0; i < toAdd.size(); i+=2)
	{
		//parse the title and flag line
		auto prod = P1.getStringToken(toAdd[i], '|');
		
		//prepare the recipe vector
		std::vector<Product::Point> tempRecipe;

		//count elements in recipe
		auto rec = P1.getStringToken(toAdd[i + 1], ',');
		for (auto &x : rec) 
		{ 
			//parse each ingredient
			auto ing = P1.getStringToken(x, '|');
			
			P1.trimWhitespace(ing[0]);
			int qty = 1;
			
			if (ing.size() > 1)
			{
				P1.trimWhitespace(ing[1]);
				qty = std::stoi(ing[1]);
			}

			//check ingredient against refrence in Menu
			for (auto const & ref : IngredientRef)
			{
				//update recipe
				if (ref.getName() == ing[0])
				{
					Product::Point temp(ref.getID(), qty);
					tempRecipe.push_back(temp);
				}

			}

		}

		Pizza pizzaToAdd(prod[0], tempRecipe, IngredientRef);
		//set flags if they exist
		if (prod.size() > 1) { pizzaToAdd.setFlags(prod[1]); }

		//add product
		ProductRef.push_back(pizzaToAdd);

		//add Veg to separate ledger
		if (pizzaToAdd.isVeg())
		{
			VLedger.insert(ProductRef.size() - 1);
		}
 	}
}

template <class T>
void Menu<T>::initLedgers()
{
	if (Ledger.size() < ProductRef.size())
	{
		Ledger.reserve(ProductRef.size());
		for (size_t i = Ledger.size(); i < ProductRef.size(); i++)
		{
			Ledger.push_back(Product::Point(0,0));
			//add Veg to separate ledger
			if (ProductRef[i].isVeg())
			{
				VLedger.insert(i);
			}
		}
	}
}

template <>
Menu<Pizza> & Menu<Pizza>::operator+=(const Order & toPlace)
{
	this->placeOrder(toPlace);
	return *this;
}