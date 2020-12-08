#include <iostream>
#include <vector>
#include "Simplex.hpp"

using namespace std;

bool debug = true;

// вывод решения
void PrintSolve(SimplexSolve solve, int n, char varName, char funcName, char funcName2) {
    Fraqtion invF = Fraqtion(1) / solve.f;

    for (int i = 0; i < n; i++)
        cout << varName << (i + 1) << ": " << solve.x[i] << ", x" << (i + 1) << ": " << invF * solve.x[i] << endl;

    cout << funcName << ": " << solve.f << ", " << funcName2 << ": " << invF << endl;
}


int main() {
    // vector<vector<Fraqtion>> matrix = {
    //     { 1, 3, 9, 6 },
    //     { 2, 6, 2, 3 },
    //     { 7, 2, 6, 5 },
    // };

    vector<vector<Fraqtion>> matrix = {
        { 12, 6, 3, 17, 9 },
        { 0, 5, 16, 0, 15 },
        { 16, 19, 12, 18, 11 },
        { 19, 12, 7, 2, 13 }
    };

    int na = matrix.size(); // количество для игрока A
    int nb = matrix[0].size(); // количество для игрока B

    vector<vector<Fraqtion>> aa(nb, vector<Fraqtion>(na));
    vector<Fraqtion> ba(nb);
    vector<Fraqtion> ca(na);

    vector<vector<Fraqtion>> ab(na, vector<Fraqtion>(nb));
    vector<Fraqtion> bb(na);
    vector<Fraqtion> cb(nb);

    for (int i = 0; i < na; i++) {
        for (int j = 0; j < nb; j++) {
            aa[j][i] = -matrix[i][j];
            ab[i][j] = matrix[i][j];
        }

        bb[i] = 1;
        ca[i] = 1;
    }

    for (int i = 0; i < nb; i++) {
        ba[i] = -1;
        cb[i] = 1;
    }

    SimplexMode modea = SimplexMode::Min;
    SimplexMode modeb = SimplexMode::Max;

    Simplex simplexA(aa, ba, ca, modea, 'u', 'W');
    Simplex simplexB(ab, bb, cb, modeb, 'v', 'Z');

    cout << "Player A:" << endl;
    simplexA.PrintTask();
    simplexA.Solve(debug);
    SimplexSolve solveA = simplexA.GetSolve();

    PrintSolve(solveA, na, 'u', 'W', 'g');

    cout << endl << endl << "Player B:" << endl;
    simplexB.PrintTask();
    simplexB.Solve(debug);
    SimplexSolve solveB = simplexB.GetSolve();
    PrintSolve(solveB, nb, 'v', 'Z', 'h');
}
