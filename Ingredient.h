#ifndef INGREDIENT_H
#define INGREDIENT_H
#include <string>

using std::string;

class Ingredient
{
private:
    string name;
    double quantity;
    string unitOfMeasurement;
public:
    Ingredient()
    {
        name = "No Name";
        quantity = 0;
        unitOfMeasurement = "No Unit of Measurement";
    };
    Ingredient(string ingName, double ingQuantity, string ingUnit)
    {
        name = ingName;
        quantity = ingQuantity;
        unitOfMeasurement = ingUnit;
    };
    /** Returns name */
    string GetName() const { return name; };
    /** Returns quantity */
    double GetQuantity() const { return quantity; };
    /** Returns unitOfMeasurement */
    string GetUnits() const { return unitOfMeasurement; };
};
#endif // !INGREDIENT_H