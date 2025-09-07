#include <iostream>
#include <fstream>
#include <string>
#include <vector> // Necesitas esta biblioteca para la forma más eficiente

using namespace std;

string readF(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "El archivo " << filename << " no se ha encontrado." << endl;
        return "";
    }
    string content((istreambuf_iterator<char>(file)),
                     istreambuf_iterator<char>());
    return content;
}

// Función parte 1
void buscarSubsecuencias(const string& transmission, const string& mcode) {
    size_t posicion = transmission.find(mcode);

    if (posicion != string::npos) {
        cout << "true " << posicion << endl;
    } else {
        cout << "false" << endl;
    }
}

// Funcion auxiliar para encontrar un palindromo
pair<int, int> centro(const string& s, int left, int right) {
    while (left >= 0 && right < s.size()) {
        // Se ignoran los espacios en blanco en ambos lados
        while (left >= 0 && isspace(s[left])) {
            left--;
        }
        while (right < s.size() && isspace(s[right])) {
            right++;
        }
        if (left >= 0 && right < s.size() && s[left] == s[right]) {
            left--;
            right++;
        } else {
            break; 
        }
    }
    return {left + 1, right - 1};
}

// Función principal para encontrar el palíndromo más largo
void Palindromomo(const string& transmission) {
    if (transmission.empty()) {
        cout << "0 0" << endl;
        return;
    }

    int start = 0, maxLength = 1;

    for (int i = 0; i < transmission.size(); ++i) {
        // Palíndromo de longitud impar (centro en i)
        pair<int, int> odd = centro(transmission, i, i);
        int len_odd = odd.second - odd.first + 1;
        if (len_odd > maxLength) {
            maxLength = len_odd;
            start = odd.first;
        }

        // Palíndromo de longitud par (centro entre i y i+1)
        pair<int, int> even = centro(transmission, i, i + 1);
        int len_even = even.second - even.first + 1;
        if (len_even > maxLength) {
            maxLength = len_even;
            start = even.first;
        }
    }
    // Output
    int final_pos = start + maxLength - 1;
    cout << start + 1 << " " << final_pos + 1 << endl;
}

int main() {
    // Leer los archivos
    string transmission1 = readF("transmission1.txt");
    string transmission2 = readF("transmission2.txt");
    string mcode1 = readF("mcode1.txt");
    string mcode2 = readF("mcode2.txt");
    string mcode3 = readF("mcode3.txt");

    cout << "1.- Subsecuencias " << endl;
    // Búsqueda en archivos
    buscarSubsecuencias(transmission1, mcode1);
    buscarSubsecuencias(transmission1, mcode2);
    buscarSubsecuencias(transmission1, mcode3);
    buscarSubsecuencias(transmission2, mcode1);
    buscarSubsecuencias(transmission2, mcode2);
    buscarSubsecuencias(transmission2, mcode3);

    cout << "2.- Palindromos " << endl;
    Palindromomo(transmission1);
    Palindromomo(transmission2);


    return 0;
}