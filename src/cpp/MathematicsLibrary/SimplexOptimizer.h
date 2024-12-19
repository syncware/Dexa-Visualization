#include <iostream>
#include <vector>
#include <limits>

using namespace std;

const double EPSILON = 1e-6;

class SimplexOptimizer
{
private:
    int m, n;                       // m - number of constraints, n - number of variables
    vector<vector<double>> tableau; // Simplex tableau
    vector<int> basis;              // Basis indices

public:
    SimplexOptimizer(const vector<vector<double>> &A, const vector<double> &b, const vector<double> &c)
    {
        m = b.size();
        n = c.size();

        // Initialize the tableau with slack variables
        tableau.assign(m + 1, vector<double>(n + m + 1));
        basis.resize(m);

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
                tableau[i][j] = A[i][j];
            tableau[i][n + i] = 1;
            tableau[i][n + m] = b[i];
            basis[i] = n + i;
        }

        for (int j = 0; j < n; ++j)
            tableau[m][j] = c[j];
    }

    // Perform a pivot operation
    void pivot(int row, int col)
    {
        for (int i = 0; i <= m; ++i)
        {
            for (int j = 0; j <= n + m; ++j)
            {
                if (i != row && j != col)
                    tableau[i][j] -= tableau[row][j] * tableau[i][col] / tableau[row][col];
            }
        }

        for (int i = 0; i <= m; ++i)
        {
            if (i != row)
                tableau[i][col] = 0;
        }

        for (int i = 0; i <= n + m; ++i)
        {
            if (i != col)
                tableau[row][i] /= tableau[row][col];
        }

        tableau[row][col] = 1;
    }

    // Perform the simplex algorithm
    double optimize()
    {
        while (true)
        {
            int pivot_col = -1;
            for (int j = 0; j <= n + m; ++j)
            {
                if (tableau[m][j] < -EPSILON)
                {
                    pivot_col = j;
                    break;
                }
            }
            if (pivot_col == -1)
                break; // Optimal solution found

            int pivot_row = -1;
            double min_ratio = numeric_limits<double>::infinity();
            for (int i = 0; i < m; ++i)
            {
                if (tableau[i][pivot_col] > EPSILON)
                {
                    double ratio = tableau[i][n + m] / tableau[i][pivot_col];
                    if (ratio < min_ratio)
                    {
                        min_ratio = ratio;
                        pivot_row = i;
                    }
                }
            }
            if (pivot_row == -1)
                return numeric_limits<double>::infinity(); // Unbounded problem

            pivot(pivot_row, pivot_col);
            basis[pivot_row] = pivot_col;
        }

        return -tableau[m][n + m]; // Optimal value
    }

    // Get the optimal solution
    vector<double> getSolution()
    {
        vector<double> solution(n, 0);
        for (int i = 0; i < m; ++i)
        {
            if (basis[i] < n)
            {
                solution[basis[i]] = tableau[i][n + m];
            }
        }
        return solution;
    }
};