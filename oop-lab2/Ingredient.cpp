#include "Ingredient.h"

Ingredient::Ingredient() : name("Невідомо"), dose(0), price(0) {}

Ingredient::Ingredient(string name, double dose, double price)
{
    setName(name);
    setDose(dose);
    setPrice(price);
}

Ingredient::~Ingredient() {}

void Ingredient::setName(string value) { name = value; }
void Ingredient::setDose(double value) { dose = value < 0 ? 0 : value; }
void Ingredient::setPrice(double value) { price = value < 0 ? 0 : value; }

string Ingredient::getName() const { return name; }
double Ingredient::getDose() const { return dose; }
double Ingredient::getPrice() const { return price; }

double Ingredient::cost() const { return dose * price; }

void Ingredient::show() const
{
    cout << "  " << name << ": " << dose << " x " << price
        << " грн = " << cost() << " грн" << endl;
}