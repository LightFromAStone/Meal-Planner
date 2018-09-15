#ifndef DAY_H
#define DAY_H
#include <string>
#include "Nutrition.h"
#include "Recipe.h"

class Day
{
private:
    friend class MealPlan;
    Nutrition dailyNutrients;
    Recipe breakfast;
    double bfServing;
    Recipe lunch;
    double lunchServing;
    Recipe dinner;
    double dinnerServing;
public:
    Day()
    {
        Nutrition startingTotals;
        dailyNutrients = startingTotals;
        Recipe blankRecipe;
        breakfast = blankRecipe;
        lunch = blankRecipe;
        dinner = blankRecipe;
        bfServing, lunchServing, dinnerServing = 0;
    };
    /** Sets breakfast equal to @param bfastToSet*/
    void SetBreakfast(Recipe bfastToSet) { breakfast = bfastToSet; }
    /** Returns breakfast */
    std::string GetBreakfast() { return breakfast.GetName(); }

    /** Sets lunch equal to @param lunchToSet */
    void SetLunch(Recipe lunchToSet) { lunch = lunchToSet; }
    /** Returns lunch */
    std::string GetLunch() { return lunch.GetName(); }

    /** Sets dinner equal to @param dinnerToSet */
    void SetDinner(Recipe dinnerToSet) { dinner = dinnerToSet; }
    /** Returns dinner */
    std::string GetDinner() { return dinner.GetName(); }

    /** Sets dailyNutrients to the nutrient totals from breakfast, lunch and dinner */
    void UpdateNutrients()
    {
        double runningTotal = 0;
        // Update Carbs //
        runningTotal = breakfast.allNutrients.GetNetCarbs() * breakfast.mealServing;
        runningTotal += lunch.allNutrients.GetNetCarbs() * lunch.mealServing;
        runningTotal += dinner.allNutrients.GetNetCarbs() * dinner.mealServing;
        dailyNutrients.SetNetCarbs(runningTotal);
        // Update Fat //
        runningTotal = breakfast.allNutrients.GetTotalFat() * breakfast.mealServing;
        runningTotal += lunch.allNutrients.GetTotalFat() * lunch.mealServing;
        runningTotal += dinner.allNutrients.GetTotalFat() * dinner.mealServing;
        dailyNutrients.SetTotalFat(runningTotal);
        // Update Protein //
        runningTotal = breakfast.allNutrients.GetProtein() * breakfast.mealServing;
        runningTotal += lunch.allNutrients.GetProtein() * lunch.mealServing;
        runningTotal += dinner.allNutrients.GetProtein() * dinner.mealServing;
        dailyNutrients.SetProtein(runningTotal);
        // Update Calories //
        runningTotal = breakfast.allNutrients.GetCalories() * breakfast.mealServing;
        runningTotal += lunch.allNutrients.GetCalories() * lunch.mealServing;
        runningTotal += dinner.allNutrients.GetCalories() * dinner.mealServing;
        dailyNutrients.SetCalories(runningTotal);
    };
    /** Returns nutrient info from dailyNutrients */
    string GetNutrients() const 
    {
        std::stringstream out;
        out << dailyNutrients.GetNetCarbs() << "g Net Carbs, " << dailyNutrients.GetProtein() << "g Protein, ";
        out << dailyNutrients.GetTotalFat() << "g Fat, " << dailyNutrients.GetCalories() << " kcals";
        return out.str();
    }

    string GetMealNutrients(int selectMeal)
    {
        std::stringstream out;
        switch (selectMeal)
        {
        case 1: out << breakfast.allNutrients.GetNetCarbs() << "g Net Carbs, " << breakfast.allNutrients.GetProtein() << "g Protein";
            if (bfServing > 1) { out << " (" << bfServing << " Servings)"; }
            break;
        case 2: out << lunch.allNutrients.GetNetCarbs() << "g Net Carbs, " << lunch.allNutrients.GetProtein() << "g Protein";
            if (lunchServing > 1) { out << " (" << lunchServing << " Servings)"; }
            break;
        case 3: out << dinner.allNutrients.GetNetCarbs() << "g Net Carbs, " << dinner.allNutrients.GetProtein() << "g Protein";
            if (dinnerServing > 1) {out << " (" << dinnerServing << " Servings)"; }
            break;
        }
        return out.str();
    }
};
#endif // !DAY_H