#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <random>

using namespace std;

const int INGR = 100;

class Pizza {
public:
    int index;
    set<string> ingredients;
    bitset<INGR> ingrBitset;

    Pizza(int _index) : index(_index) {
    }

    friend ostream &operator<<(ostream &os, const Pizza &p);

    //ATTENZIONE OPERATORE AL CONTRARIO
    bool operator<(const Pizza &p) const {
        return ingredients.size() > p.ingredients.size();
    }
};

ostream &operator<<(ostream &os, const Pizza &p) {
    os << "index: " << p.index << ", " << p.ingredients.size();
    for (const auto &ingr : p.ingredients) {
        os << " " << ingr;
    }
    return os;
}

class Team {
public:
    int size;
    vector<Pizza> pizzas;

    Team(int _size, vector<Pizza> _pizzas) : size(_size), pizzas(_pizzas) {}

    int getScore() {
        set<string> ingredients;
        for (auto &pizza : pizzas) {
            ingredients.insert(pizza.ingredients.begin(), pizza.ingredients.end());
        }
        return (int) ingredients.size() * ingredients.size();
    }
};


int M;
int T2;
int T3;
int T4;
int maxIngredients = 0;

vector<Pizza> pizzas;
vector<Team> teams;
set<string> globalIngredients;
bitset<INGR> globalIngrBitset(0);
vector<Team> teams2;
vector<Team> teams3;
vector<Team> teams4;

void readFile(string inputFilePath) {
    ifstream in(inputFilePath, ios::in);

    cout << "Reading file " << inputFilePath << endl;

    in >> M >> T2 >> T3 >> T4;

    cout << "Number of pizzas M = " << M << endl;
    cout << "Number of teams (T2, T3, T4) = (" << T2 << ", " << T3 << ", " << T4 << ")" << endl;

    int numIngTmp;
    for (int i = 0; i < M; i++) {
        in >> numIngTmp;
        Pizza pizza(i);

        string tmpStr;
        for (int j = 0; j < numIngTmp; j++) {
            in >> tmpStr;

            pizza.ingredients.insert(tmpStr);
            globalIngredients.insert(pizza.ingredients.begin(), pizza.ingredients.end());
            maxIngredients = max(maxIngredients, (int) pizza.ingredients.size());
        }
        pizzas.push_back(pizza);
        cout << pizza << endl;
    }

    cout << "Total number of ingredients = " << globalIngredients.size() << endl;
    cout << "Maximum number of ingredients per pizza = " << maxIngredients << endl;

    // populate global Ingredients Bitset
    int i = 0;
    for (auto &ingr : globalIngredients) {
        globalIngrBitset[i] = 1;
        i++;
    }


    int index = 0;
    map<string, int> mappaIngredienti;
    for (auto &ingr : globalIngredients) {
        mappaIngredienti[ingr] = index;
        index++;
    }

    for (auto &pizza: pizzas) {
        for (auto &ingr: pizza.ingredients) {
            pizza.ingrBitset[mappaIngredienti[ingr]] = 1;
        }
    }
}

void basicAlgorithm() {
    int i = 0;
    while (i < pizzas.size()) {
        if (teams4.size() < T4 && i + 3 < pizzas.size()) {
            teams4.push_back(Team(4, {pizzas[i], pizzas[i + 1], pizzas[i + 2], pizzas[i + 3]}));
            i += 3;
        } else if (teams3.size() < T3 && i + 2 < pizzas.size()) {
            teams3.push_back(Team(3, {pizzas[i], pizzas[i + 1], pizzas[i + 2]}));
            i += 2;
        } else if (teams2.size() < T2 && i + 1 < pizzas.size()) {
            teams2.push_back(Team(2, {pizzas[i], pizzas[i + 1]}));
            i += 1;
        }
        i += 1;
        /*for (const auto& team :teams4) {
            cout << teams4
        }*/
    }
}

void greedyAlgorithm() {
    //ATTENZIONE REVERSE SORT (ordine decrescente)
    sort(pizzas.begin(), pizzas.end());
    while (pizzas.size() > 1) {
        cout << "Len(pizzas) = " << pizzas.size() << " " << M << endl;
        if (teams4.size() < T4 && pizzas.size() >= 4) {
            vector<Pizza> pizzasTeamList;
            set<string> ingredients;
            auto p1Iter = pizzas.begin();

            ingredients.insert(p1Iter->ingredients.begin(), p1Iter->ingredients.end());
            pizzas.erase(p1Iter);
            pizzasTeamList.push_back(*p1Iter);

            while (pizzasTeamList.size() < 4) {
                vector<Pizza>::iterator p2Iter;
                int maxValue = 0;

                for (auto it = pizzas.begin(); it != pizzas.end(); it++) {
                    auto ingredientsCopy = ingredients;
                    ingredientsCopy.insert(it->ingredients.begin(), it->ingredients.end());
                    auto tempValue = ingredientsCopy.size();
                    if (tempValue > maxValue) {
                        maxValue = tempValue;
                        p2Iter = it;
                    }
                }
                ingredients.insert(p2Iter->ingredients.begin(), p2Iter->ingredients.end());
                pizzas.erase(p2Iter);
                pizzasTeamList.push_back(*p2Iter);
            }
            teams4.push_back(Team(4, pizzasTeamList));
        } else if (teams3.size() < T3 && pizzas.size() >= 3) {
            vector<Pizza> pizzasTeamList;
            set<string> ingredients;
            auto p1Iter = pizzas.begin();

            ingredients.insert(p1Iter->ingredients.begin(), p1Iter->ingredients.end());
            pizzas.erase(p1Iter);
            pizzasTeamList.push_back(*p1Iter);

            while (pizzasTeamList.size() < 3) {
                vector<Pizza>::iterator p2Iter;
                int maxValue = 0;

                for (auto it = pizzas.begin(); it != pizzas.end(); it++) {
                    auto ingredientsCopy = ingredients;
                    ingredientsCopy.insert(it->ingredients.begin(), it->ingredients.end());
                    auto tempValue = ingredientsCopy.size();
                    if (tempValue > maxValue) {
                        maxValue = tempValue;
                        p2Iter = it;
                    }
                }
                ingredients.insert(p2Iter->ingredients.begin(), p2Iter->ingredients.end());
                pizzas.erase(p2Iter);
                pizzasTeamList.push_back(*p2Iter);
            }
            teams3.push_back(Team(3, pizzasTeamList));
        } else if (teams2.size() < T2 && pizzas.size() >= 2) {
            vector<Pizza> pizzasTeamList;
            set<string> ingredients;
            auto p1Iter = pizzas.begin();

            ingredients.insert(p1Iter->ingredients.begin(), p1Iter->ingredients.end());
            pizzas.erase(p1Iter);
            pizzasTeamList.push_back(*p1Iter);

            while (pizzasTeamList.size() < 2) {
                vector<Pizza>::iterator p2Iter;
                int maxValue = 0;

                for (auto it = pizzas.begin(); it != pizzas.end(); it++) {
                    auto ingredientsCopy = ingredients;
                    ingredientsCopy.insert(it->ingredients.begin(), it->ingredients.end());
                    auto tempValue = ingredientsCopy.size();
                    if (tempValue > maxValue) {
                        maxValue = tempValue;
                        p2Iter = it;
                    }
                }
                ingredients.insert(p2Iter->ingredients.begin(), p2Iter->ingredients.end());
                pizzas.erase(p2Iter);
                pizzasTeamList.push_back(*p2Iter);
            }
            teams2.push_back(Team(2, pizzasTeamList));
        }
    }
}


template<typename Iter>
Iter select_randomly(Iter start, Iter end) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, std::distance(start, end) - 1);
    std::advance(start, dis(gen));
    return start;
}

void randomOptimumSearch_1(int rounds) {
    for (int counter = 0; counter < rounds; counter++) {
        srand(10);

        auto t1Iter = select_randomly(teams4.begin(), teams4.end());
        auto t2Iter = select_randomly(teams3.begin(), teams3.end());

        int score = t1Iter->getScore() + t2Iter->getScore();
        auto p1Iter = select_randomly(t1Iter->pizzas.begin(), t1Iter->pizzas.end());
        auto p2Iter = select_randomly(t2Iter->pizzas.begin(), t2Iter->pizzas.end());

        iter_swap(p1Iter, p2Iter);

        int newScore = t1Iter->getScore() + t2Iter->getScore();
        if (newScore < score) {
            iter_swap(p1Iter, p2Iter);
        } else if (newScore > score) {
            cout << "Gain +" << newScore - score << endl;
        }
    }
}

void printInput() {
    for (const auto &elem: pizzas) {
        cout << elem << endl;
    }
}

int solve() {
    basicAlgorithm();

    teams.insert(teams.end(), teams2.begin(), teams2.end());
    teams.insert(teams.end(), teams3.begin(), teams3.end());
    teams.insert(teams.end(), teams4.begin(), teams4.end());

    int totScore = 0;
    for (auto &team : teams) {
        totScore += team.getScore();
    }
    cout << "Total score = " << totScore << endl;
    return totScore;
}

void printOutput(string outputFile) {
    ofstream out(outputFile, ios::out);
    out << teams.size() << endl;
    for (const auto &team : teams) {
        out << team.size;
        for (const auto &pizza : team.pizzas) {
            out << " " << pizza.index;
        }
        out << endl;
    }
}

int problem(string inputFile) {
    readFile(inputFile);
    //printInput();
    int totScore = solve();
    printOutput(inputFile.substr(0, inputFile.size() - 3) + ".out ");
    return totScore;
}

int main() {
    vector<string> files = {"a_example.in", "b_little_bit_of_everything.in", "c_many_ingredients.in",

                            "d_many_pizzas.in", "e_many_teams.in"};
    int totScore = 0;
    /*for (const string &filePath : files) {
        totScore += problem(filePath);
        cout << std::string(30, '-') << endl;
    }*/
    totScore += problem(files[0]);
    cout << "Global score = " << totScore << endl;

    return 0;
}
