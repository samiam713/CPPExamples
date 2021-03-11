//
//  main.cpp
//  GroceryStoreProblem
//
//  Created by Samuel Donovan on 3/5/21.
//

#include <iostream>
#include <utility>
#include <vector>

using namespace std;

enum Decision {
BuyGroceries,
BuyMeal,
GetFreeMeal
};

typedef pair<int,Decision> CostDecision;

int main(int argc, const char * argv[]) {
    // you are planning your food plan for the next int "N" days
    // you are given vector<bool> "freeFood" tracking days you can get food for free
    
    // you output a vector of FoodChoices
    
    vector<bool> freeFood;
    vector<CostDecision> decisions(freeFood.size() + 6);
    
    int calculatingDay = (int)freeFood.size() - 7;
    while (calculatingDay >= 0) {
        const CostDecision buyMeal = decisions[calculatingDay + 1];
        if (freeFood[calculatingDay]) decisions[calculatingDay] = CostDecision(buyMeal.first,Decision::GetFreeMeal);
        const CostDecision buyGroceries = decisions[calculatingDay + 7];
        
        const int buyMealCost = 3 + buyMeal.first;
        const int buyGroceriesCost = 10 + buyGroceries.first;
        
        if (buyMealCost <= buyGroceriesCost) {
            decisions[calculatingDay] = CostDecision(buyMealCost, Decision::BuyMeal);
        } else {
            decisions[calculatingDay] = CostDecision(buyGroceriesCost, Decision::BuyGroceries);
        }
        
        calculatingDay--;
    }

}
