#include <iostream>
#include <bits/stdc++.h>

using namespace std;

int knapsack(int W, int weights[], int values[], int n) {
    int dp[n + 1][W + 1];

    for (int i = 0; i <= n; ++i) {
        for (int w = 0; w <= W; ++w) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
            else if (weights[i - 1] <= w)
                dp[i][w] = max(values[i - 1] + dp[i - 1][w - weights[i - 1]], dp[i - 1][w]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }

    return dp[n][W];
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

    int max_value = knapsack(W, weights, values, n);
    cout << "Maximum value that can be obtained: " << max_value << endl;

    return 0;
}
