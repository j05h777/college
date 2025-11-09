#include <iostream>
#include <string>
using namespace std;
int main() {
    int num;
    cout << "Enter number of productions: ";
    cin >> num;
    string productions[20];
    for (int i = 0; i < num; i++) {
        cout << "Enter production " << i + 1 << ": ";
        cin >> productions[i];
    }
    cout << "\nEliminating Left Recursion\n";
    cout << "Note: '#' represents epsilon (empty string)\n";
    for (int i = 0; i < num; i++) {
        string prod = productions[i];
        char non_terminal = prod[0];
        string right = prod.substr(3);
        string alphas[10], betas[10];
        int alpha_count = 0, beta_count = 0;
        string temp = "";
        for (int k = 0; k < right.length(); k++) {
            if (right[k] == '|') {
                if (temp[0] == non_terminal)
                    alphas[alpha_count++] = temp.substr(1);
                else
                    betas[beta_count++] = temp;
                temp = "";
            } else {
                temp += right[k];
            }
        }
        if (!temp.empty()) {
            if (temp[0] == non_terminal)
                alphas[alpha_count++] = temp.substr(1);
            else
                betas[beta_count++] = temp;
        }
        if (alpha_count > 0) {
            cout << "\nLeft recursion found in production: " << prod << endl;
            cout << "New Grammar:\n";
            if (beta_count == 0) {
                betas[beta_count++] = "#"; // epsilon represented as #
            }
            for (int j = 0; j < beta_count; j++) {
                if (betas[j] == "#")
                     cout << non_terminal << " -> " << non_terminal << "'\n";
                else
                    cout << non_terminal << " -> " << betas[j] <<
non_terminal << "'\n";
            }
            cout << non_terminal << "' -> ";
            for (int j = 0; j < alpha_count; j++) {
                cout << alphas[j] << non_terminal << "'";
                if (j != alpha_count - 1)
                    cout << " | ";
            }
            cout << " | #\n";
        } else {
            cout << "\nNo left recursion in production: " << prod << endl;
        }
    }
    return 0;
}
