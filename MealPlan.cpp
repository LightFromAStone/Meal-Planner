#include "MealPlan.h"

MealPlan::MealPlan()
{
    maxNetCarbs = 20; // 20g Net Carbs is the maximum for a Keto diet
    maxProtein = 90; // determined by user's age, height, weight, and calorie deficit.
    Day newDay;
    for (int i = 0; i < 7; ++i) // 7 for days in a week
    {
        daysOfWeek.push_back(newDay);
    }
    Nutrition noNutr;
    Recipe inttFast("Intermittant Fasting", 0, 0, "No", noNutr, "None", "NotSet");
    InterFasting = inttFast;
}


void MealPlan::AddRecipe(Recipe newRecipe)
{
    if (newRecipe.GetMealClass() == Breakfast) { breakfastList.push_back(newRecipe); }
    else if (newRecipe.GetMealClass() == Lunch) { lunchList.push_back(newRecipe); }
    else { dinnerList.push_back(newRecipe); }
}


string MealPlan::AddLeftover(unsigned int typeIndex, unsigned int mealNum, unsigned  int numServings)
{
    if (typeIndex == 1)
    {
        if (mealNum < 1 || mealNum > breakfastList.size()) { return "Unable to find meal in Breakfast list!"; }
        mealNum -= 1;
        Recipe newLeftover;
        newLeftover = breakfastList.at(mealNum);
        string leftoverAdded = breakfastList.at(mealNum).GetName() + " has been added as a leftover!";
        newLeftover.ToggleLeftover();
        newLeftover.SetNumServings(numServings);
        if ((newLeftover.mealServing <= numServings) && (newLeftover.mealServing > 1)) { newLeftover.mealServing /= 2; }
        leftoverMeals.push(newLeftover);
        return leftoverAdded;
    }
    else if (typeIndex == 2)
    {
        if (mealNum < 1 || mealNum > lunchList.size()) { return "Unable to find meal in Lunch list!"; }
        mealNum -= 1;
        Recipe newLeftover;
        newLeftover = lunchList.at(mealNum);
        string leftoverAdded = lunchList.at(mealNum).GetName() + " has been added as a leftover!";
        newLeftover.ToggleLeftover();
        newLeftover.SetNumServings(numServings);
        if ((newLeftover.mealServing <= numServings) && (newLeftover.mealServing > 1)) { newLeftover.mealServing /= 2; }
        leftoverMeals.push(newLeftover);
        return leftoverAdded;
    }
    else if (typeIndex == 3)
    {
        if (mealNum < 1 || mealNum > dinnerList.size()) { return "Unable to find meal in Dinner list!"; }
        mealNum -= 1;
        Recipe newLeftover;
        newLeftover = dinnerList.at(mealNum);
        string leftoverAdded = dinnerList.at(mealNum).GetName() + " has been added as a leftover!";
        newLeftover.ToggleLeftover();
        newLeftover.SetNumServings(numServings);
        if ((newLeftover.mealServing <= numServings) && (newLeftover.mealServing > 1)) { newLeftover.mealServing /= 2; }
        leftoverMeals.push(newLeftover);
        if(dinnerList.size() > 7) { dinnerList.erase(dinnerList.begin() + mealNum); } // Must have at least 7 dinners
        return leftoverAdded;
    }
    return "Unable to find meal in Breakfast, Lunch, or Dinner list!";
}


bool MealPlan::AssessMeal(int dayIndex, int recipeIndex, int mealType) const
{
    if (mealType == Dinner)
    {
        if (dayIndex != 0)
        {   // For days other than the first day, checks if meal's protein type is the same as the previous days //
            if (dinnerList.at(recipeIndex).GetProteinType() == daysOfWeek.at(dayIndex - 1).dinner.GetProteinType()) { return false; }
        }
        if (((dinnerList.at(recipeIndex).allNutrients.GetNetCarbs() * dinnerList.at(recipeIndex).mealServing)
            + daysOfWeek.at(dayIndex).dailyNutrients.GetNetCarbs() < maxNetCarbs) && ((dinnerList.at(recipeIndex).allNutrients.GetProtein()
                * dinnerList.at(recipeIndex).mealServing) + daysOfWeek.at(dayIndex).dailyNutrients.GetProtein() < maxProtein)) { return true; }
    }
    else if (mealType == Lunch)
    {
        if (((lunchList.at(recipeIndex).allNutrients.GetNetCarbs() * lunchList.at(recipeIndex).mealServing)
            + daysOfWeek.at(dayIndex).dailyNutrients.GetNetCarbs() < maxNetCarbs) && ((lunchList.at(recipeIndex).allNutrients.GetProtein()
                * lunchList.at(recipeIndex).mealServing) + daysOfWeek.at(dayIndex).dailyNutrients.GetProtein() < maxProtein)) { return true; }
    }
    return false;
}


string MealPlan::ListAllMeals()
{
    std::stringstream out;
    out << "1. Breakfast:" << endl;
    for (unsigned int i = 0; i < breakfastList.size(); ++i)
    {
        out << "\t" << i + 1 << ". " << breakfastList.at(i).GetName() << " - " << breakfastList.at(i).allNutrients.GetNetCarbs();
        out << "g Net Carbs, " << breakfastList.at(i).allNutrients.GetProtein() << "g Protein" << endl;
    }
    out << endl << "2. Lunch:" << endl;
    for (unsigned int i = 0; i < lunchList.size(); ++i)
    {
        out << "\t" << i + 1 << ". " << lunchList.at(i).GetName() << " - " << lunchList.at(i).allNutrients.GetNetCarbs();
        out << "g Net Carbs, " << lunchList.at(i).allNutrients.GetProtein() << "g Protein" << endl;
    }
    out << endl << "3. Dinner:" << endl;
    for (unsigned int i = 0; i < dinnerList.size(); ++i)
    {
        out << "\t" << i + 1 << ". " << dinnerList.at(i).GetName() << " - " << dinnerList.at(i).allNutrients.GetNetCarbs();
        out << "g Net Carbs, " << dinnerList.at(i).allNutrients.GetProtein() << "g Protein" << endl;
    }
    return out.str();
}

void MealPlan::CreatePlan()
{
    int bfIndex = 0;
    int lunchIndex = 0;
    int bfMaxIndex = breakfastList.size();
    int lunchMaxIndex = lunchList.size();
    // Step 0 - Shuffle Recipe Vectors //
    srand(unsigned(time(0)));
    random_shuffle(breakfastList.begin(), breakfastList.end());
    random_shuffle(lunchList.begin(), lunchList.end());
    random_shuffle(dinnerList.begin(), dinnerList.end());

    for (unsigned int d = 0; d < daysOfWeek.size(); ++d)
    {// Step 1 - Check for and assign leftovers //
        if (leftoverMeals.size() != 0)
        {
            daysOfWeek.at(d).SetLunch(leftoverMeals.front());
            daysOfWeek.at(d).lunchServing = daysOfWeek.at(d).lunch.mealServing;
            if (leftoverMeals.front().mealServing * 2 == leftoverMeals.front().numServings) { leftoverMeals.pop(); }
            else { leftoverMeals.front().numServings -= (leftoverMeals.front().mealServing * 2); }
            daysOfWeek.at(d).lunchServing = daysOfWeek.at(d).lunch.mealServing;
            daysOfWeek.at(d).UpdateNutrients();
        }
        // Step 2 - assign Breakfast //
        daysOfWeek.at(d).SetBreakfast(breakfastList.at(bfIndex));
        daysOfWeek.at(d).bfServing = breakfastList.at(bfIndex).mealServing;
        bfIndex += 1;
        if (bfIndex == bfMaxIndex) { bfIndex = 0; }
        daysOfWeek.at(d).UpdateNutrients();
        // Step 3 - assign Dinner //
        int cycleLeftovers = leftoverMeals.size(); 
        for (unsigned int i = dinnerList.size() - 1; i >= 0; --i) // ideally want to remove items from end of vector
        {   
            if (AssessMeal(d, i, Dinner))
            {
                daysOfWeek.at(d).SetDinner(dinnerList.at(i));
                daysOfWeek.at(d).dinnerServing = dinnerList.at(i).mealServing;
                daysOfWeek.at(d).UpdateNutrients();
                double currentServings = dinnerList.at(i).GetNumServings();
                currentServings -= (dinnerList.at(i).mealServing * 2); // Based on a meal plan created for two people
                if (currentServings > 0)
                {
                    dinnerList.at(i).SetNumServings(currentServings);
                    dinnerList.at(i).ToggleLeftover();
                    if (dinnerList.at(i).mealServing > 1) { dinnerList.at(i).mealServing /= 2; }
                    leftoverMeals.push(dinnerList.at(i));
                    cycleLeftovers = leftoverMeals.size();
                }
                dinnerList.erase(dinnerList.begin() + i); // Removes dinner so it won't be used again
                break;
            }
            else if (i == 0)
            {
                // If lunch is set, moves it to leftover queue //
                if (daysOfWeek.at(d).GetLunch() != "No Name")
                {
                    leftoverMeals.push(daysOfWeek.at(d).lunch); // Add current lunch to leftover queue
                    if (cycleLeftovers == 0) // No remaining leftovers to choose from
                    {
                        Recipe noLunch;
                        daysOfWeek.at(d).SetLunch(noLunch); // removes lunch from current day
                        daysOfWeek.at(d).lunchServing = 0;
                        daysOfWeek.at(d).UpdateNutrients();
                    }
                    else
                    {
                        daysOfWeek.at(d).SetLunch(leftoverMeals.front()); // set lunch to next leftover in queue
                        daysOfWeek.at(d).lunchServing = daysOfWeek.at(d).lunch.mealServing;
                        daysOfWeek.at(d).UpdateNutrients();
                        leftoverMeals.pop();
                        --cycleLeftovers;
                    }
                    i = dinnerList.size(); // resets i so that loop will check for new dinner if there is no lunch
                }
            }
        }//------------------Implement Dinner Queue for Leftovers that are dinner portions but can't be used for lunch---------------------//
         // Step 4 - Fill in Missing Lunches //
        if (daysOfWeek.at(d).GetLunch() == "No Name")
        {
            for (int i = lunchList.size() - 1; i >= 0; --i)
            {
                if (AssessMeal(d, i, Lunch))
                {
                    daysOfWeek.at(d).SetLunch(lunchList.at(i));
                    daysOfWeek.at(d).lunchServing = daysOfWeek.at(d).lunch.mealServing;
                    daysOfWeek.at(d).UpdateNutrients();

                    double currentServings = lunchList.at(i).GetNumServings();
                    currentServings -= (lunchList.at(i).mealServing * 2); // Based on a meal plan created for two people
                    if (currentServings > 0)
                    {
                        lunchList.at(i).SetNumServings(currentServings);
                        lunchList.at(i).ToggleLeftover();
                        if (lunchList.at(i).mealServing > 1) { lunchList.at(i).mealServing /= 2; }
                        leftoverMeals.push(lunchList.at(i));
                        lunchList.erase(lunchList.begin() + i); // Removes lunch so it won't be used again
                    }
                }
            }
        }
    }
    
}


string MealPlan::PrintMealPlan()
{
    std::stringstream out;
    for (unsigned int i = 0; i < daysOfWeek.size(); ++i)
    {
        switch (i)
        {
        case 0: out << "Sunday"; 
            break;
        case 1: out << "Monday";
            break;
        case 2: out << "Tuesday";
            break;
        case 3: out << "Wednesday";
            break;
        case 4: out << "Thursday";
            break;
        case 5: out << "Friday";
            break;
        case 6: out << "Saturday";
            break;
        }
        out << " - " << daysOfWeek.at(i).GetNutrients() << endl;
        out << std::setw(18) << std::right << "Breakfast: ";
        out << daysOfWeek.at(i).GetBreakfast() << " - " << daysOfWeek.at(i).GetMealNutrients(1) << endl;
        out << std::setw(18) << std::right << "Lunch: ";
        out << daysOfWeek.at(i).GetLunch() << " - " << daysOfWeek.at(i).GetMealNutrients(2) << endl;
        out << std::setw(18) << std::right << "Dinner: ";
        out << daysOfWeek.at(i).GetDinner() << " - " << daysOfWeek.at(i).GetMealNutrients(3) << endl << endl;
    }
    if (leftoverMeals.size() > 0)
    {
        out << "Leftovers: ";
        for (unsigned int j = leftoverMeals.size(); j > 0; --j)
        {
            out << leftoverMeals.front().numServings << " Servings of " << leftoverMeals.front().GetName();
            if (j != 1) { out << ", "; }
            else { out << endl << endl; }
            leftoverMeals.pop();
        }
    }
    return out.str();
}