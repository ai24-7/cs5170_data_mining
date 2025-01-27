#include <iostream>
#include <vector>
#include <ctime>
#include <fstream>

std::vector<int> coin_change_combinations_1(std::vector<int> coins, int amount) {
    int num_coins = coins.size();
    
    std::vector<int> ways(amount + 1, 0);
    
    ways[0] = 1;
    
    for (int i = 0; i < num_coins; i++) {
        int coin_value = coins[i];
        
        for (int j = coin_value; j <= amount; j++) {
            ways[j] += ways[j - coin_value];
        }
    }
    
    return ways;
}

void generate_combinations(int index, int remaining_amount, std::vector<int> coins, std::vector<int> current_combination, std::vector<std::vector<int>>& combinations) {
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
        
        generate_combinations(i, remaining_amount - coin, coins, current_combination, combinations);
        
        current_combination.pop_back();
    }
}

std::vector<std::vector<int>> coin_change_combinations_2(std::vector<int> coins, int amount) {
    std::vector<std::vector<int>> combinations;
    generate_combinations(0, amount, coins, std::vector<int>(), combinations);
    return combinations;
}

std::vector<double> run_experiment(std::vector<int> coins, std::vector<int> amounts, std::vector<int> (*method)(std::vector<int>, int)) {
    std::vector<double> runtimes;
    for (int amount : amounts) {
        clock_t start_time = clock();
        std::vector<int> res = method(coins, amount);
        double elapsed_time = (double)(clock() - start_time) / CLOCKS_PER_SEC;
        runtimes.push_back(elapsed_time);
    }
    return runtimes;
}

int main() {
    std::vector<int> coins = {1, 5, 10, 25, 50, 100, 200, 500, 1000, 2000};
    std::vector<int> coins_2 = {1, 29, 493};
    std::vector<int> experiment_amounts_2ab = {10, 50, 100, 500, 1000, 1500, 2000, 3000, 5000};
    std::vector<int> experiment_amounts_2c = {10, 25, 50, 100};
    
    std::vector<double> runtimes_2a = run_experiment(coins, experiment_amounts_2ab, coin_change_combinations_1);
    std::vector<double> runtimes_2b = run_experiment(coins_2, experiment_amounts_2ab, coin_change_combinations_1);
    std::vector<std::vector<int>> runtimes_2ca = run_experiment(coins, experiment_amounts_2c, coin_change_combinations_2);
    std::vector<std::vector<int>> runtimes_2cb = run_experiment(coins_2, experiment_amounts_2c, coin_change_combinations_2);
    
    std::ofstream csv_file("runtime_results.csv");
    csv_file << "Experiment,Amount,Runtime\n";
    
    for (int i = 0; i < experiment_amounts_2ab.size(); i++) {
        csv_file << "2a," << experiment_amounts_2ab[i] << "," << runtimes_2a[i] << "\n";
        csv_file << "2b," << experiment_amounts_2ab[i] << "," << runtimes_2b[i] << "\n";
    }
    
    for (int i = 0; i < experiment_amounts_2c.size(); i++) {
        csv_file << "2ca," << experiment_amounts_2c[i] << ",";
        for (int j = 0; j < runtimes_2ca[i].size(); j++) {
            csv_file << runtimes_2ca[i][j];
            if (j != runtimes_2ca[i].size() - 1) {
                csv_file << ",";
            }
        }
        csv_file << "\n";
        
        csv_file << "2cb," << experiment_amounts_2c[i] << ",";
        for (int j = 0; j < runtimes_2cb[i].size(); j++) {
            csv_file << runtimes_2cb[i][j];
            if (j != runtimes_2cb[i].size() - 1) {
                csv_file << ",";
            }
        }
        csv_file << "\n";
    }
    
    csv_file.close();
    
    std::cout << "Runtime results saved to runtime_results.csv" << std::endl;
    
    return 0;
}


