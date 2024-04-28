#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsackTopDown(int W, int weights[], int values[], int n, vector<vector<int>>& memo) {
    // If either the number of items or the capacity of the knapsack is 0, return 0
    if (n == 0 || W == 0)
        return 0;

    // If the result for the current state is already computed, return it from the memo table
    if (memo[n][W] != -1)
        return memo[n][W];

    // If the weight of the current item exceeds the capacity of the knapsack,
    // skip it and move to the next item
    if (weights[n - 1] > W)
        return memo[n][W] = knapsackTopDown(W, weights, values, n - 1, memo);

    // Otherwise, choose the maximum of including the current item and excluding it
    return memo[n][W] = max(values[n - 1] + knapsackTopDown(W - weights[n - 1], weights, values, n - 1, memo),
                             knapsackTopDown(W, weights, values, n - 1, memo));
}

int main() {
    int W; // Capacity of the knapsack
    cout << "Enter the capacity of the knapsack: ";
    cin >> W;

    int n; // Number of items
    cout << "Enter the number of items: ";
    cin >> n;

    int values[n]; // Values of the items
    int weights[n]; // Weights of the items

    cout << "Enter the values and weights of the items:\n";
    for (int i = 0; i < n; ++i) {
        cout << "Value of item " << i+1 << ": ";
        cin >> values[i];
        cout << "Weight of item " << i+1 << ": ";
        cin >> weights[i];
    }

    // Initialize memoization table with -1
    vector<vector<int>> memo(n + 1, vector<int>(W + 1, -1));

    // Call the knapsackTopDown function with the initial parameters
    int max_value = knapsackTopDown(W, weights, values, n, memo);

    cout << "Maximum value that can be obtained: " << max_value << endl;

    return 0;
}
