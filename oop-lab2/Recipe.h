#pragma once
#include <string>
#include <vector>
#include "Ingredient.h"
using namespace std;

class Recipe
{
private:
    string name;                   // назва страви
    vector<Ingredient> items;      // масив інгредієнтів

public:
    Recipe();
    Recipe(string name);
    ~Recipe();

    void setName(string value);
    string getName() const;
    int count() const;

    void addIngredient(const Ingredient& ing);
    double totalCost() const;
    void show() const;

    bool saveToFile(const string& fileName) const;
    static bool findInFile(const string& fileName,
        const string& recipeName,
        Recipe& result);
};
