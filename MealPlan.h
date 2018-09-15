#ifndef MEAL_PLAN_H
#define MEAL_PLAN_H
#include <queue>
#include <sstream>
#include <iomanip>

#include <ctime>
#include "Recipe.h"
#include "Day.h"

using std::endl;

class MealPlan
{
private:
    std::vector<Recipe> breakfastList;
    std::vector<Recipe> lunchList;
    std::vector<Recipe> dinnerList;
    std::vector<Day> daysOfWeek;
    std::queue<Recipe> leftoverMeals;
    Recipe InterFasting;
    double maxNetCarbs;
    double maxProtein;
    /** Returns true if current meal is of a different meat type than the previous day's
        and if the net carbs and net protein are less than or equal to their maximums */
    bool AssessMeal(int dayIndex, int recipeIndex, int mealType) const;
public:
    MealPlan();

    /** Adds @param newRecipe to the appropriate meal list vector */
    void AddRecipe(Recipe newRecipe);

    /** Determines what Breakfast, Lunch, and Dinner will be for each day */
    void CreatePlan();

    /** Writes all meals along with their respective Net Carbs and Protein to the output file */
    string ListAllMeals();

    /** Adds a leftover to the leftoverMeals queue. If newLeftover is a dinner, it removes it 
       from the dinnerList vector */
    string AddLeftover(unsigned int typeIndex, unsigned int mealNum, unsigned int numServings);

    /** Returns a string of Breakfast, Lunch, and Dinner for each day along with the days total 
        macro-nutrients */
    string MealPlan::PrintMealPlan();
    
};
#endif // !MEAL_PLAN_H
