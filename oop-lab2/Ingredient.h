#pragma once
#include <string>
#include <iostream>
using namespace std;

class Ingredient
{
private:
    string name;     // назва продукту
    double dose;     // дозування (кг)
    double price;    // ціна за 1 кг

public:
    Ingredient();
    Ingredient(string name, double dose, double price);
    ~Ingredient();

    void setName(string value);
    void setDose(double value);
    void setPrice(double value);
    string getName() const;
    double getDose() const;
    double getPrice() const;

    double cost() const;      // дозування * ціна
    void show() const;
};