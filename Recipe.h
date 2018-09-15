#ifndef RECIPE_H
#define RECIPE_H

#include <vector>
#include <string>
#include "Nutrition.h"
#include "Ingredient.h"
using std::string;

enum meatType { Chicken, Pork, Beef, Fish, NoMeat, Undefined };
enum mealType { Breakfast, Lunch, Dinner, NotSet };

class Recipe
{
private:
    friend class MealPlan;
    friend class Day;
    string name;
    double numServings;
    double mealServing;
    bool isSplittable;
    std::vector<Ingredient> allIngredients;
    Nutrition allNutrients;
    meatType proteinType;
    mealType mealClass;
    bool isLeftover;

public:
    Recipe();
    Recipe(string setName, double setServing, double setMealServ, string setSplit,
           Nutrition setNutrition, string setProteinType, string setMealClass);

    /** Sets isLeftover member to opposite of current value */
    void ToggleLeftover();

    /** Adds a new ingredient to the allIngredients vector */
    void AddIngredient(Ingredient setIngredient);

    /** Returns name */
    string GetName() const;

    /** Sets the number of servings */
    void SetNumServings(double servToSet);
    /** Returns numServings */
    double GetNumServings() const;

    /** Returns proteinType */
    meatType GetProteinType() const;

    /** Returns mealClass */
    mealType GetMealClass() const;

    /** Returns True if recipe is a leftover */
    bool CheckLeftover() const;

    
};
/** */
#endif // !RECIPE_H