#include "./decisionTree.h"  // NOLINT(build/include)
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <limits>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using std::string;
using std::pair;
using std::vector;
using std::unordered_map;
using std::make_shared;

// structura unui nod din decision tree
// splitIndex = dimensiunea in functie de care se imparte
// split_value = valoarea in functie de care se imparte
// is_leaf si result sunt pentru cazul in care avem un nod frunza
Node::Node() {
    is_leaf = false;
    left = nullptr;
    right = nullptr;
}

void Node::make_decision_node(const int index, const int val) {
    split_index = index;
    split_value = val;
}

void Node::make_leaf(const vector<vector<int>> &samples,
                     const bool is_single_class) {
    // is_single_class = true -> toate testele au aceeasi clasa (acela e result)
    // is_single_class = false -> se alege clasa care apare cel mai des
    this->is_leaf = true;
    if (is_single_class == true) {
        this->result = samples[0][0];
    }
    else
    {
        vector<int> count(10, 0);  // vector de frecventa
        int val_max = 0, ind_max = 0;
        for (int i = 0; i < samples.size(); i++) {
            count[samples[i][0]]++;
        }
        // cautam valoarea predominanta din vector, cat si indexul acesteia
        for (int i = 1; i < 10; i++) {
            if (count[i] > val_max) {
                val_max = count[i];
                ind_max = i;
            }
        }
        this->result = ind_max;
    }
}

pair<int, int> find_best_split(const vector<vector<int>> &samples,
                               const vector<int> &dimensions) {
    // Intoarce cea mai buna dimensiune si valoare de split dintre testele
    // primite. Prin cel mai bun split (dimensiune si valoare)
    // ne referim la split-ul care maximizeaza IG
    // pair-ul intors este format din (split_index, split_value)

    int splitIndex = -1, splitValue = -1;
    float IG = 0.0f, ent, max = 0.0f, ent_stanga = 0;
    float ent_dreapta = 0, ent_copii;
    ent = get_entropy(samples);  // entropia parintelui
    pair<vector<int>, vector<int>> pereche;  // copiii
    for (int i = 0; i < dimensions.size(); i++) {
        vector<int> unic = compute_unique(samples, dimensions[i]);
        // pentru fiecare unic generat calculam entropia copiilor
        for (int j = 0; j < unic.size(); j++) {
        pereche = get_split_as_indexes(samples, dimensions[i], unic[j]);
        if (pereche.first.size() != 0 && pereche.second.size() != 0) {
            ent_stanga = get_entropy_by_indexes(samples, pereche.first);
            ent_dreapta = get_entropy_by_indexes(samples, pereche.second);

	    ent_copii = (pereche.first.size()*ent_stanga +
	        pereche.second.size()*ent_dreapta)/(pereche.first.size() +
                    pereche.second.size());

            IG = ent - ent_copii;
            // cautam splitul care maximizeaza IG
            if (IG > max) {
                max = IG;
                splitIndex = dimensions[i];
                splitValue = unic[j];
            }
        }
        }
    }

    return pair<int, int>(splitIndex, splitValue);
}

void Node::train(const vector<vector<int>> &samples) {
    // Antreneaza nodul curent si copii sai, daca e nevoie
    // 1) verifica daca toate testele primite au aceeasi clasa (raspuns)
    // Daca da, acest nod devine frunza, altfel continua algoritmul.
    // 2) Daca nu exista niciun split valid, acest nod devine frunza. Altfel,
    // ia cel mai bun split si continua recursiv
    int a, b;
    pair<int, int> bs = find_best_split(samples,
        random_dimensions(samples[0].size()));
    a = bs.first;
    b = bs.second;
    if (same_class(samples) == true){
        this->make_leaf(samples, true);
        return;
    }
    else if (a == -1 && b == -1)
    {
        this->make_leaf(samples, false);
        return;
    }
    else
    {
        make_decision_node(a, b);
        pair <vector<vector<int>>, vector<vector<int>>> pereche;
        pereche = split(samples, a, b);
        left = make_shared<Node>();
        right = make_shared<Node>();
        this->left->train(pereche.first);
        this->right->train(pereche.second);
    }
}

int Node::predict(const vector<int> &image) const {
    // Intoarce rezultatul prezis de catre decision tree
    // parcurgem tree-ul in functie de best_split pana ajungem la o frunza
    // returnam valoarea din frunza
    if (this->is_leaf == true) {
        return this->result;
    }
    if (image[this->split_index] <= this->split_value){
        this->left->predict(image);
    }
    else
        this->right->predict(image);
}

bool same_class(const vector<vector<int>> &samples) {
    // Verifica daca testele primite ca argument au toate aceeasi
    // clasa(rezultat). Este folosit in train pentru a determina daca
    // mai are rost sa caute split-uri
    int first_class;
    first_class = samples[0][0];
    for (int i = 1; i < samples.size(); i++) {
        if (first_class != samples[i][0]) {
            return false;
        }
    }
    return true;
}

float get_entropy(const vector<vector<int>> &samples) {
    // Intoarce entropia testelor primite
    assert(!samples.empty());
    vector<int> indexes;

    int size = samples.size();
    for (int i = 0; i < size; i++) indexes.push_back(i);

    return get_entropy_by_indexes(samples, indexes);
}

float get_entropy_by_indexes(const vector<vector<int>> &samples,
                             const vector<int> &index) {
    // Intoarce entropia subsetului din setul de teste total(samples)
    // Cu conditia ca subsetul sa contina testele ale caror indecsi se gasesc in
    // vectorul index (Se considera doar liniile din vectorul index)
    vector<float> p(10, 0);
    int r = index.size();
    // calculam frecventa fiecarui rezultat
    for (int i = 0; i < r; i++) {
        p[samples[index[i]][0]]++;
    }
    for (int i = 0; i < 10; i++){
        p[i] /= r;
    }
    float entropy = 0;
    // aplicam formula data pentru entropie
    for (int i = 0; i < 10; i++) {
        if (p[i] != 0) {
            entropy -= p[i]*log2(p[i]);
        }
    }

    return entropy;
}

vector<int> compute_unique(const vector<vector<int>> &samples, const int col) {
    // Intoarce toate valorile (se elimina duplicatele)
    // care apar in setul de teste, pe coloana col
    vector<int> uniqueValues;
    // verificam daca fiecare valoare posibila exista
    vector<bool> values(256, false);
    for (int i = 0; i < samples.size(); i++) {
        values[samples[i][col]] = true;
    }
    for (int i = 0; i <= 255; i++) {
        if (values[i] == true) {
            uniqueValues.push_back(i);
        }
    }
    return uniqueValues;
}

pair<vector<vector<int>>, vector<vector<int>>> split(
    const vector<vector<int>> &samples, const int split_index,
    const int split_value) {
    // Intoarce cele 2 subseturi de teste obtinute in urma separarii
    // In functie de split_index si split_value
    vector<vector<int>> left, right;

    auto p = get_split_as_indexes(samples, split_index, split_value);
    for (const auto &i : p.first) left.push_back(samples[i]);
    for (const auto &i : p.second) right.push_back(samples[i]);

    return pair<vector<vector<int>>, vector<vector<int>>>(left, right);
}

pair<vector<int>, vector<int>> get_split_as_indexes(
    const vector<vector<int>> &samples, const int split_index,
    const int split_value) {
    // Intoarce indecsii sample-urilor din cele 2 subseturi obtinute in urma
    // separarii in functie de split_index si split_value
    vector<int> left, right;
    for (int i = 0; i < samples.size(); i++){
        if (samples[i][split_index] <= split_value)
            left.push_back(i);
        else
            right.push_back(i);
    }
    return make_pair(left, right);
}

vector<int> random_dimensions(const int size) {
    // Intoarce sqrt(size) dimensiuni diferite pe care sa caute splitul maxim
    // Precizare: Dimensiunile gasite sunt > 0 si < size
    vector<int> rez;
    // initializam un vector astfel incat rez[i] = i
    for (int i = 1; i < size; i++) {
        rez.push_back(i);
    }
    // aplicam functia shuffle pe vectorul creat
    std::random_shuffle(rez.begin(), rez.end());
    // stergem valori din vector pentru a ajunge la dimensiunea necesara
    for (int i = 0; i < size - floor(sqrt(size)+1); i++) {
        rez.pop_back();
    }
    return rez;
}
