#include <iostream>
#include <vector>

using namespace std;

class SimplexSolver
{
private:
    vector<vector<double>> tableau;

public:
    int M; // Number of constraints
    int N; // Number of variables
    SimplexSolver(const vector<vector<double>> &A, const vector<double> &b, const vector<double> &c);
    void pivot(int row, int col);
    bool solve();
    double getOptimalValue();
    vector<double> getOptimalSolution();
};

SimplexSolver::SimplexSolver(const vector<vector<double>> &A, const vector<double> &b, const vector<double> &c)
{
    N = A.size();
    M = c.size();
    tableau.resize(M + 1, vector<double>(N + M + 1, 0));

    // Populate coefficients of objective function
    for (int j = 0; j < N; ++j)
    {
        tableau[0][j] = c[j];
    }

    // Populate coefficients of constraints
    for (int i = 1; i <= M; ++i)
        for (int j = 0; j < N; ++j)
            tableau[i][j] = A[i - 1][j];

    // Populate slack variables and right-hand side
    for (int i = 1; i <= M; ++i)
    {
        tableau[i][N + i - 1] = 1;
        tableau[i][N + M] = b[i - 1];
    }
}

void SimplexSolver::pivot(int row, int col)
{
    for (int i = 0; i <= M; ++i)
    {
        for (int j = 0; j <= N + M; ++j)
        {
            if (i != row && j != col)
            {
                tableau[i][j] -= tableau[row][j] * tableau[i][col] / tableau[row][col];
            }
        }
    }

    for (int i = 0; i <= M; ++i)
    {
        if (i != row)
            tableau[i][col] = 0;
    }

    for (int i = 0; i <= N + M; ++i)
    {
        if (i != col)
            tableau[row][i] /= tableau[row][col];
    }

    tableau[row][col] = 1;
}

bool SimplexSolver::solve()
{
    while (true)
    {
        // Find entering variable
        int pivot_col = -1;
        for (int j = 0; j <= N + M; ++j)
        {
            if (tableau[0][j] > 0)
            {
                pivot_col = j;
                break;
            }
        }
        if (pivot_col == -1) // Optimal solution found
            return true;

        // Find leaving variable
        int pivot_row = -1;
        double min_ratio = numeric_limits<double>::infinity();
        for (int i = 1; i <= M; ++i)
        {
            if (tableau[i][pivot_col] > 0)
            {
                double ratio = tableau[i][N + M] / tableau[i][pivot_col];
                if (ratio < min_ratio)
                {
                    min_ratio = ratio;
                    pivot_row = i;
                }
            }
        }
        if (pivot_row == -1) // Unbounded problem
            return false;

        pivot(pivot_row, pivot_col);
    }
}

double SimplexSolver::getOptimalValue()
{
    return -tableau[0][N + M]; // Optimal value is the negative of the value in the last column
}

vector<double> SimplexSolver::getOptimalSolution()
{
    vector<double> solution(N);
    for (int i = 1; i <= M; ++i)
    {
        if (tableau[i][N + M] != 0)
        {
            for (int j = 0; j < N; ++j)
            {
                if (tableau[i][j] == 1)
                    solution[j] = tableau[i][N + M];
            }
        }
    }
    return solution;
}