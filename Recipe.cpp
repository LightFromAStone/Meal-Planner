#include "Recipe.h"


Recipe::Recipe()
{
    Nutrition noNutrients;
    name = "No Name";
    numServings = 0;
    mealServing = 0;
    isSplittable = false;
    allNutrients = noNutrients;
    isLeftover = false;
    proteinType = Undefined;
    mealClass = NotSet;
}


Recipe::Recipe(string setName, double setServing, double setMealServ, string setSplit,
               Nutrition setNutrition, string setProteinType, string setMealClass)
{
    name = setName;
    numServings = setServing;
    mealServing = setMealServ;
    allNutrients = setNutrition;
    if (setSplit == "Yes") { isSplittable = true; }
    else { isSplittable = false; }
    isLeftover = false;
    if (setProteinType == "Chicken") { proteinType = Chicken; }
    else if (setProteinType == "Pork") { proteinType = Pork; }
    else if (setProteinType == "Beef") { proteinType = Beef; }
    else if (setProteinType == "Fish") { proteinType = Fish; }
    else if (setProteinType == "None") { proteinType = NoMeat; }
    else { proteinType = Undefined; }

    if (setMealClass == "Breakfast") { mealClass = Breakfast; }
    else if (setMealClass == "Lunch") { mealClass = Lunch; }
    else if (setMealClass == "Dinner") { mealClass = Dinner; }
    else { mealClass = NotSet; }
}


void Recipe::ToggleLeftover()
{
    if (!isLeftover) { isLeftover = true; }
    else if (isLeftover) { isLeftover = false; }
}


void Recipe::AddIngredient(Ingredient setIngredient)
{
    allIngredients.push_back(setIngredient);
}


string Recipe::GetName() const { return name; }

void Recipe::SetNumServings(double servToSet) { numServings = servToSet; }

double Recipe::GetNumServings() const { return numServings; }

meatType Recipe::GetProteinType() const { return proteinType; }

mealType Recipe::GetMealClass() const { return mealClass; }

bool Recipe::CheckLeftover() const { return isLeftover; }
