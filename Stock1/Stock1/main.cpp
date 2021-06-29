//
//  main.cpp
//  Stock1
//
//  Created by Samuel Donovan on 6/1/21.
//

#include <iostream>
#include <vector>

using namespace std;

struct StockData {
    int minPrice;
    int maxPrice;
    int maxProfit;
    
    StockData(int minPrice, int maxPrice, int maxProfit) :
    minPrice(minPrice), maxPrice(maxPrice), maxProfit(maxProfit) {};
};

class Solution {
public:
    StockData conquer(vector<int>& prices, int low, int high) {
        if (high-low <= 2) {
            if (high-low == 2) {
                bool increasing = prices[low] < prices[low+1];
                if (increasing) {
                    return StockData(prices[low],prices[low+1],prices[low+1]-prices[low]);
                } else {
                    return StockData(prices[low+1],prices[low],0);
                }
            } else {
                return StockData(prices[low],prices[low],0);
            }
        }
        
        int middle = (high+low)>>1;
        StockData left = conquer(prices, low, middle);
        StockData right = conquer(prices, middle, high);
        
        int maxProfit = max(max(left.maxProfit,right.maxProfit), right.maxPrice - left.minPrice);
        int maxPrice = max(left.maxPrice, right.maxPrice);
        int minPrice = min(left.minPrice,right.minPrice);
        
        return StockData(minPrice,maxPrice,maxProfit);
    }
    
    int maxProfit(vector<int>& prices) {
        return conquer(prices, 0, int(prices.size())).maxProfit;
    }
};

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
