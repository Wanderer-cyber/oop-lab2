#include <iostream>
#include <string>
#include "Recipe.h"
#ifdef _WIN32
#include <windows.h>
#endif
using namespace std;

const string FILE_NAME = "recipes.txt";

double readNumber(const string& text)
{
    while (true)
    {
        cout << text;
        string s;
        getline(cin, s);
        try
        {
            size_t pos;
            double v = stod(s, &pos);
            if (pos == s.size() && v >= 0) return v;
        }
        catch (...) {}
        cout << "  Некоректне введення, потрібне невід'ємне число.\n";
    }
}

string readText(const string& text)
{
    while (true)
    {
        cout << text;
        string s;
        getline(cin, s);
        if (!s.empty()) return s;
        cout << "  Рядок не може бути порожнім.\n";
    }
}

Recipe inputRecipe()
{
    Recipe r(readText("Назва рецепта: "));
    int n = (int)readNumber("Скільки інгредієнтів: ");
    for (int i = 1; i <= n; i++)
    {
        cout << "Інгредієнт " << i << ":\n";
        string name = readText("  Назва продукту: ");
        double dose = readNumber("  Дозування (кг): ");
        double price = readNumber("  Ціна за 1 кг (грн): ");
        r.addIngredient(Ingredient(name, dose, price));
    }
    return r;
}

int main()
{
#ifdef _WIN32
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
#endif

    Recipe current;
    int choice = -1;

    while (choice != 0)
    {
        cout << "\n===== МЕНЮ =====\n"
            << "1 - Ввести новий рецепт\n"
            << "2 - Показати рецепт і вартість\n"
            << "3 - Зберегти рецепт у файл\n"
            << "4 - Знайти рецепт у файлі\n"
            << "0 - Вихід\n";
        choice = (int)readNumber("Ваш вибір: ");

        switch (choice)
        {
        case 1:
            current = inputRecipe();
            break;
        case 2:
            if (current.count() == 0) cout << "Рецепт порожній.\n";
            else current.show();
            break;
        case 3:
            if (current.count() == 0) cout << "Нічого зберігати.\n";
            else if (current.saveToFile(FILE_NAME)) cout << "Збережено у " << FILE_NAME << endl;
            else cout << "Не вдалося записати файл.\n";
            break;
        case 4:
        {
            Recipe found;
            string name = readText("Яку страву шукати: ");
            if (Recipe::findInFile(FILE_NAME, name, found))
            {
                cout << "Знайдено!\n";
                found.show();
            }
            else cout << "Рецепт не знайдено.\n";
            break;
        }
        case 0:
            cout << "До побачення!\n";
            break;
        default:
            cout << "Немає такого пункту.\n";
        }
    }
    return 0;
}