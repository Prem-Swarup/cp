#include <iostream>
#include <vector>
#include <cmath>


template<typename T=long long>
T func(T a, T b){
  
  return a+b;
}

template<typename T=long long>
class SparseTable {
private:
    std::vector<std::vector<T>> table;
    T stVal;
public:
    SparseTable(const std::vector<T>& arr) {
        T n = arr.size();
        T logN = log2(n) + 1;
        table.resize(n, std::vector<T>(logN));
        stVal = 0;
        // Initialize the table with values from the original array
        for (T i = 0; i < n; i++) {
            table[i][0] = arr[i];
        }

        // Build the sparse table
        for (T j = 1; (1 << j) <= n; j++) {
            for (T i = 0; i + (1 << j) - 1 < n; i++) {
                table[i][j] = func(table[i][j - 1], table[i + (1 << (j - 1))][j - 1]);
            }
        }
    }

    T query(T left, T right) {
        T sum = stVal;

        for (T j = log2(right - left + 1); j >= 0; j--) {
            if ((1 << j) <= (right - left + 1)) {
                sum = func(sum, table[left][j]);
                left += (1 << j);
            }
        }

        return sum;
    }

    T query2(T L, T R) {
      int j = (int)log2(R - L + 1);
      return func(table[L][j], table[R - (1 << j) + 1][j]);
    }
      
};

int main() {
    std::vector<long long> arr = {1, 3, 5, 7, 9, 11, 13, 15};

    SparseTable st(arr);

    // Example range queries
    std::cout << "Range sum from index 2 to 5: " << st.query(2, 5) << std::endl;
    std::cout << "Range sum from index 1 to 7: " << st.query(1, 7) << std::endl;

    return 0;
}
