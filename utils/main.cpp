#include <iostream>
#include <vector>
#include <ctime>

int coin_change_combinations_1(std::vector<int>& coins, int amount) {
    int num_coins = coins.size();
    
    std::vector<int> ways(amount + 1, 0);
    
    ways[0] = 1;
    
    for (int i = 0; i < num_coins; i++) {
        int coin_value = coins[i];
        
        for (int j = coin_value; j <= amount; j++) {
            ways[j] += ways[j - coin_value];
        }
    }
    
    return ways[amount];
}

void generate_combinations(std::vector<int>& coins, int index, int remaining_amount, std::vector<int>& current_combination, std::vector<std::vector<int>>& combinations) {
    if (remaining_amount == 0) {
        combinations.push_back(current_combination);
        return;
    }
    
    for (int i = index; i < coins.size(); i++) {
        int coin = coins[i];
        
        if (remaining_amount < coin) {
            continue;
        }
        
        current_combination.push_back(coin);
        
        generate_combinations(coins, i, remaining_amount - coin, current_combination, combinations);
        
        current_combination.pop_back();
    }
}

std::vector<std::vector<int>> coin_change_combinations_2(std::vector<int>& coins, int amount) {
    std::vector<std::vector<int>> combinations;
    std::vector<int> current_combination;
    
    generate_combinations(coins, 0, amount, current_combination, combinations);
    
    return combinations;
}

std::vector<double> run_experiment(std::vector<int>& coins, std::vector<int>& amounts, int (*method)(std::vector<int>&, int)) {
    std::vector<double> runtimes;
    
    for (int amount : amounts) {
        clock_t start_time = clock();
        int res = method(coins, amount);
        double elapsed_time = (clock() - start_time) / (double)CLOCKS_PER_SEC;
        runtimes.push_back(elapsed_time);
    }
    
    return runtimes;
}
