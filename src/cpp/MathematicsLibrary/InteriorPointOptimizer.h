#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

// const double EPSILON = 1e-9; // Tolerance for convergence
const double ALPHA = 0.1; // Step size factor

class InteriorPointOptimizer
{
private:
    vector<vector<double>> A; // Coefficients of constraints
    vector<double> b;         // Right-hand side of constraints
    vector<double> c;         // Coefficients of the objective function
    int m, n;                 // Number of constraints (m) and variables (n)
    double mu;                // Barrier parameter

public:
    InteriorPointOptimizer(const vector<vector<double>> &constraints, const vector<double> &rhs, const vector<double> &objective)
    {
        A = constraints;
        b = rhs;
        c = objective;
        m = constraints.size();
        n = objective.size();
        mu = 10.0; // Initial value of barrier parameter
    }

    // Check if all elements of a vector are non-negative
    bool nonNegative(const vector<double> &x)
    {
        for (double xi : x)
        {
            if (xi < -EPSILON) // Assuming negative values are numerical errors
                return false;
        }
        return true;
    }

    // Compute the affine scaling direction
    vector<double> computeDirection(const vector<double> &x, const vector<double> &s, const vector<double> &y)
    {
        vector<double> dx(n);
        vector<double> ds(m);
        vector<double> dy(m);
        vector<double> r(m);

        // Calculate residuals
        for (int i = 0; i < m; ++i)
        {
            r[i] = b[i];
            for (int j = 0; j < n; ++j)
                r[i] -= A[i][j] * x[j];
            r[i] -= s[i];
        }

        // Compute direction components
        for (int j = 0; j < n; ++j)
        {
            dx[j] = c[j];
            for (int i = 0; i < m; ++i)
                dx[j] -= A[i][j] * y[i];
            for (int i = 0; i < m; ++i)
                dx[j] -= A[i][j] * s[i] / x[j];
        }

        for (int i = 0; i < m; ++i)
        {
            ds[i] = mu / x[i] - s[i] / x[i];
            dy[i] = -r[i];
        }

        vector<double> direction;
        direction.insert(direction.end(), dx.begin(), dx.end());
        direction.insert(direction.end(), ds.begin(), ds.end());
        direction.insert(direction.end(), dy.begin(), dy.end());

        return direction;
    }

    // Update the variables with the computed step
    void updateVariables(vector<double> &x, vector<double> &s, vector<double> &y, const vector<double> &direction, double alpha)
    {
        vector<double> dx(direction.begin(), direction.begin() + n);
        vector<double> ds(direction.begin() + n, direction.begin() + n + m);
        vector<double> dy(direction.begin() + n + m, direction.end());

        for (int i = 0; i < n; ++i)
            x[i] += alpha * dx[i];
        for (int i = 0; i < m; ++i)
            s[i] += alpha * ds[i];
        for (int i = 0; i < m; ++i)
            y[i] += alpha * dy[i];
    }

    // Compute the step size using a backtracking line search
    double computeStepSize(const vector<double> &x, const vector<double> &s, const vector<double> &direction)
    {
        double alpha = 1.0;
        double beta = 0.5;

        while (!nonNegative(x) || !nonNegative(s))
        {
            alpha *= beta;
            vector<double> newX(x);
            vector<double> newS(s);
            for (int i = 0; i < n; ++i)
                newX[i] = x[i] + alpha * direction[i];
            for (int i = 0; i < m; ++i)
                newS[i] = s[i] + alpha * direction[n + i];
            if (!nonNegative(newX) || !nonNegative(newS))
            {
                if (alpha < EPSILON) // Step size too small, unable to proceed
                    break;
            }
        }
        return alpha;
    }

    // Solve the linear programming problem using interior point method
    vector<double> solve()
    {
        vector<double> x(n, 1.0); // Initial feasible solution
        vector<double> s(m, 1.0); // Initial slack variables
        vector<double> y(m, 0.0); // Initial dual variables

        while (true)
        {
            // Compute direction
            vector<double> direction = computeDirection(x, s, y);

            // Compute step size
            double alpha = computeStepSize(x, s, direction);

            // Update variables
            updateVariables(x, s, y, direction, alpha);

            // Check convergence
            if (alpha < EPSILON) // Step size too small, unable to proceed
                break;

            // Update barrier parameter (optional, can be modified for better performance)
            mu *= 0.99;
        }

        return x;
    }
};