#ifndef NUTRITION_H
#define NUTRITION_H

class Nutrition
{
private:
    double netCarbs;
    double totalFat;
    double protein;
    double calories;
public:
    Nutrition()
    {
        netCarbs = 0;
        totalFat = 0;
        protein = 0;
        calories = 0;
    };
    Nutrition(double setCarbs, double setFat, double setProtein, double setCals)
    {
        netCarbs = setCarbs;
        totalFat = setFat;
        protein = setProtein;
        calories = setCals;
    };
    /** Sets netCarbs equal to @param setCarbs */
    void SetNetCarbs(double setCarbs) { netCarbs = setCarbs; }
    /** Returns netCarbs */
    double GetNetCarbs() const { return netCarbs; };
    
    /** Sets totalFat equal to @param setFat */
    void SetTotalFat(double setFat) { totalFat = setFat; }
    /** Returns totalFat */
    double GetTotalFat() const { return totalFat; };
    
    /** Sets protein equal to @param proteinToSet */
    void SetProtein(double proteinToSet) { protein = proteinToSet; }
    /** Returns protein*/
    double GetProtein() const { return protein; };
    
    /** Sets calories equal to @param calsToSet */
    void SetCalories(double calsToSet) { calories = calsToSet; }
    /** Returns calories*/
    double GetCalories() const { return calories; };
};
#endif // !NUTRITION_H



