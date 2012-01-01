#include <iostream>
#include <algorithm>
#include <vector>
#include <assert.h>

using namespace std;

template <typename T>
void compute_permutations(vector<T> &vec, vector< vector<T> > &permutations, vector<T> &currentPermutation, int depth, int start_pos)
{
    for (int i = start_pos, i < vec.size(); ++i)
    {
        vector<T> tmpVec1 = currentPermutation;
        tmpVec1.push_back(vec[i]); tmpVec1.push_back(vec[i+1]);
        vector<T> tmpVec2 = currentPermutation;
        tmpVec2.push_back(vec[i+1]); tmpVec2.push_back(vec[i]);

        if (vec.size() - depth == 2)
        {
            permutations.push_back(tmpVec1);
            permutations.push_back(tmpVec2);
        }
        else
            compute_permutations(vec, permutations, tmpVec1, depth + 1, start_pos
    }
}

template <typename T>
void compute_combinations(vector<T> &vec, vector< vector<T> > &combinations, vector<T> &currentCombination, int depth, int start_pos, int comb_size)
{
    for (int i = start_pos; i < vec.size(); ++i)
    {
        vector<T> tmpVec = currentCombination;
        tmpVec.push_back(vec[i]);
     
        if (comb_size - (depth) == 1)
            combinations.push_back(tmpVec);
        else
            compute_combinations(vec, combinations, tmpVec, depth + 1, i+1, comb_size);
    }
}

const unsigned long num_elements = 7;
const unsigned long comb_len = 6;

template <typename T>
void display_combination(vector<T> combinations)
{
    for (int i = 0; i < combinations.size(); ++i)
        cout << combinations[i];
    cout << endl;
}

int main(void)
{
    vector<char> elements(num_elements);
    char elements_str[num_elements + 1] = "abcdefg";
    copy(elements_str, elements_str + num_elements, elements.begin());

    // permutations(elements, comb_len);
    vector< vector<char> > combinations;
    vector<char> currentCombination;
    compute_combinations<char>(elements, combinations, currentCombination, 0, 0, 3);
    
    cout << "Total Combinations: " << combinations.size() << endl;

    for (int i = 0; i < combinations.size(); ++i)
        display_combination(combinations[i]);

    return 0;
}
