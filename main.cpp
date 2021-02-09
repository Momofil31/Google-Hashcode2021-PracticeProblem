#include <iostream>
#include <set>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class Pizza {
public:
    int index;
    int numIng;
    set<string> ingredients;

    Pizza(int _index, int _numIng) : index(_index), numIng(_numIng) {
    }

    friend ostream &operator<<(ostream &os, const Pizza &p);

    bool operator<(const Pizza &p) const {
        return numIng < p.numIng;
    }
};

ostream &operator<<(ostream &os, const Pizza &p) {
    os << "index: " << p.index << ", " << p.numIng;
    for (const auto &ingr : p.ingredients) {
        os << " " << ingr;
    }
    return os;
}

vector<Pizza> pizzas;
int M;
int numTeam2;
int numTeam3;
int numTeam4;

void readFile() {
    ifstream in("a_example", ios::in);

    in >> M >> numTeam2 >> numTeam3 >> numTeam4;
    int numIngTmp;
    for (int i = 0; i < M; i++) {
        in >> numIngTmp;
        pizzas.push_back(Pizza(i, numIngTmp));

        string tmpStr;
        for (int j = 0; j < numIngTmp; j++) {
            in >> tmpStr;
            pizzas[i].ingredients.insert(tmpStr);
        }
    }

}

void printInput() {
    for (const auto &elem: pizzas) {
        cout << elem << endl;
    }
}

void solve() {

}

int main() {
    readFile();
    printInput();
    solve();

    return 0;
}
