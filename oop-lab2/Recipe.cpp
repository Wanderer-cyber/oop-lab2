#include "Recipe.h"
#include <fstream>
#include <sstream>
#include <cstdlib>

Recipe::Recipe() : name("Без назви") {}
Recipe::Recipe(string name) : name(name) {}
Recipe::~Recipe() {}

void Recipe::setName(string value) { name = value; }
string Recipe::getName() const { return name; }
int Recipe::count() const { return (int)items.size(); }

void Recipe::addIngredient(const Ingredient& ing) { items.push_back(ing); }

double Recipe::totalCost() const
{
    double sum = 0;
    for (size_t i = 0; i < items.size(); i++)
        sum += items[i].cost();
    return sum;
}

void Recipe::show() const
{
    cout << "Рецепт: " << name << endl;
    for (size_t i = 0; i < items.size(); i++)
        items[i].show();
    cout << "Разом: " << totalCost() << " грн" << endl;
}

// Формат у файлі:
// RECIPE;назва;кількість
// назва продукту;дозування;ціна
bool Recipe::saveToFile(const string& fileName) const
{
    ofstream f(fileName, ios::app);          // app = дописувати в кінець
    if (!f.is_open()) return false;
    f << "RECIPE;" << name << ";" << items.size() << "\n";
    for (size_t i = 0; i < items.size(); i++)
        f << items[i].getName() << ";" << items[i].getDose() << ";"
        << items[i].getPrice() << "\n";
    return true;
}

bool Recipe::findInFile(const string& fileName, const string& recipeName, Recipe& result)
{
    ifstream f(fileName);
    if (!f.is_open()) return false;

    string line;
    while (getline(f, line))
    {
        if (line.rfind("RECIPE;", 0) != 0) continue;   // шукаємо заголовок

        stringstream head(line);
        string tag, name, cnt;
        getline(head, tag, ';');
        getline(head, name, ';');
        getline(head, cnt, ';');
        int n = atoi(cnt.c_str());

        if (name != recipeName) continue;              // не той рецепт

        Recipe r(name);
        for (int i = 0; i < n && getline(f, line); i++)
        {
            stringstream row(line);
            string iname, d, p;
            getline(row, iname, ';');
            getline(row, d, ';');
            getline(row, p, ';');
            r.addIngredient(Ingredient(iname, atof(d.c_str()), atof(p.c_str())));
        }
        result = r;
        return true;
    }
    return false;
}