/*
Created by Peter Fakkel
Started on 4 May 2018
*/
#include <iostream>
#include <fstream>

#include "Ingredient.h"
#include "Nutrition.h"
#include "Recipe.h"
#include "MealPlan.h"

using std::cout;

/** Takes a string and replaces the underscores with spaces */
void UnderscoreToSpace(string &line)
{
    for (unsigned int i = 0; i < line.length(); ++i)
    {
        if (line.at(i) == '_') { line.at(i) = ' '; }
    }
}

int main(int argc, char* argv[])
{
    // Open Input and Output Files //
    if (argc < 3)
    {
        cout << "Please provide name of input and output files" << endl;
        return 1;
    }
    cout << "Input file: " << argv[1] << endl;
    std::ifstream in(argv[1]);
    if (!in)
    {
        cout << "Unable to open " << argv[1] << " for input" << endl;
        return 1;
    }
    cout << "Output file: " << argv[2] << endl;
    std::ofstream out(argv[2]);
    if (!out)
    {
        in.close();
        cout << "Unable to open " << argv[2] << " for output" << endl;
    }

    MealPlan myMealPlan;

    // Read in and Create Recipes //
    while (!in.eof())
    {
        string recipeName;
        string proteinClass;
        string bldClass;

        in >> recipeName >> proteinClass >> bldClass;
        UnderscoreToSpace(recipeName);
        
        // Nutrition Info //
        double ingCarbs = 0;
        double ingFat = 0;
        double ingProtein = 0;
        double ingCals = 0;

        in >> ingCarbs >> ingFat >> ingProtein >> ingCals;
        Nutrition newNutrition(ingCarbs, ingFat, ingProtein, ingCals);
        // Serving Size Info //
        double ingServings = 0;
        double mealServings = 0;
        string canSplit;

        in >> ingServings >> mealServings >> canSplit;
        // Create Recipe //
        Recipe newRecipe(recipeName, ingServings, mealServings, canSplit, newNutrition, proteinClass, bldClass);
        // Ingredient Loop //
        int numIngredients;
        in >> numIngredients;
        for (int i = 0; i < numIngredients; ++i)
        {
            double ingQuantity = 0;
            string ingMeasure;
            string ingName;

            in >> ingQuantity >> ingMeasure >> ingName;
            UnderscoreToSpace(ingName);
            Ingredient newIngredient(ingName, ingQuantity, ingMeasure);
            newRecipe.AddIngredient(newIngredient);
        }
        // Add Recipe to Meal Plan //
        myMealPlan.AddRecipe(newRecipe);
        
    }
    // Prompt user for Leftovers and unwanted Meals //
    int userNum = 0;
    int mealNum, servNum = 0;
    cout << endl;

    cout << "Do you have any leftovers with 2 or more servings that you would like to include in this meal plan?" << endl;
    cout << "NOTE: If the leftover meal is a dinner, it will be removed from the dinner list if you have more than 7 dinners!" << endl;
    cout << "Enter 1 for Yes or 2 for No:" << endl;
    do
    {
        if (userNum != 0) { cout << "You must enter 1 or 2" << endl; }
        std::cin >> userNum;
        if (userNum == 0) { cout << "You must enter 1 or 2" << endl; }
    } while (userNum > 2 || userNum < 1);
    if (userNum == 1)
    {
        while (userNum != 0)
        {
            userNum = 0; // Reset userNum
            cout << myMealPlan.ListAllMeals();
            cout << "Which meal do you have leftovers for?" << endl;
            cout << "Use 1, 2, or 3 to note if the recipe is from Breakfast, Lunch, or Dinner. ";
            cout << "If you are done adding leftovers, enter 0." << endl;
            do
            {
                if (userNum > 3 || userNum < 0) { cout << "You must enter 1, 2, 3, or 0" << endl; }
                std::cin >> userNum;
            } while (userNum > 3 || userNum < 0);
            if (userNum == 0) { break; }
            cout << "What is the recipe number?" << endl;
            std::cin >> mealNum;
            //userNum = 3; // Circumvents first if statement in following loop
            cout << "How many servings do you have left?" << endl;
            do
            {
                std::cin >> servNum;
                if (servNum < 2) { cout << "The number of servings must be 2 or greater! Try again:" << endl; }
            } while (servNum < 2);
            cout << myMealPlan.AddLeftover(userNum, mealNum, servNum) << endl;
        }
    }
   

    myMealPlan.CreatePlan();
    out << myMealPlan.PrintMealPlan();

    in.close();
    out.close();

    system("pause");
    return 0;
}