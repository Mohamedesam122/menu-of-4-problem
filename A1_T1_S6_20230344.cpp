// File:A1_T1_S6_20230344.cpp
// Purpose:program solve any problem between 4 problems.
// Author:Mohamed essam abdelmonaem
// Section:s6
// ID:20230344
// Date: 10 Oct 2024
// Detailed explanation of the file and how program works:processFile:
/* processFile:
   This section writes predefined sentences into a text file.
   It then reads the sentences, replaces certain words based on a substitution map,
   and writes the modified text into a new output file. */

/* dominoes_check:
   This section checks if a sequence of domino pieces can form a connected chain.
   It counts the occurrences of each number on the dominoes and determines
   if it's possible to connect them based on the odd occurrence count. */

/* readAndFormatInput:
   This section reads input from the user, ensuring it doesn't exceed 100 characters.
   It capitalizes the first letter of each sentence and converts the rest to lowercase
   while removing extra spaces. */

/* sieve:
   This section implements the Sieve of Eratosthenes to find all prime numbers
   up to a given limit. */

#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <limits> // إضافة هذه المكتبة

using namespace std;

const int maxLength = 100;

void processFile(const string& file_name, const unordered_map<string, string>& alternatives) {
    ofstream output(file_name);
    if (output.is_open()) {
        output << "إرهاب و فساد يؤثران على استقرار البلاد\n";
        output << "لا يمكن قبول تعذيب أو خداع لأي إنسان.\n";
        output << "كذب و كراهية يؤديان إلى تفاقم الأزمات.\n";
        output << "يسعى الجميع إلى سلام دائم و تغيير حقيقي.\n";
        output << "يؤثر دين على سياسة الكثير من الدول.\n";
        output << "تسبب حرب في تفشي فقر شديد بين السكان.\n";
        output << "قد تؤدي ثورة غير منظمة إلى تطرف في بعض الحالات.\n";
        output.close();
    } else {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    ifstream input(file_name);
    string s;

    ofstream output_changed("output_changed_" + file_name);

    if (input.is_open() && output_changed.is_open()) {
        while (getline(input, s)) {
            istringstream iss(s);
            string word;
            string modified_line;

            while (iss >> word) {
                if (alternatives.find(word) != alternatives.end()) {
                    word = alternatives.at(word);
                }
                modified_line += word + " ";
            }

            output_changed << modified_line << endl;
        }

        input.close();
        output_changed.close();
    } else {
        cout << "Error opening file for reading or writing!" << endl;
    }
}

struct Domino {
    int leftDots;
    int rightDots;
};

bool canFormChain(vector<Domino>& dominoes, vector<bool>& used, int currentRight, int count, vector<Domino>& result, int total) {
    if (count == total) {
        return true;
    }

    for (int j = 0; j < dominoes.size(); j++) {
        if (!used[j] && dominoes[j].leftDots == currentRight) {
            used[j] = true;
            result.push_back(dominoes[j]);

            if (canFormChain(dominoes, used, dominoes[j].rightDots, count + 1, result, total)) {
                return true;
            }

            used[j] = false;
            result.pop_back();
        }
    }
    return false;
}

void dominoes_function() {
    int n;
    cout << "Enter number of dominos: ";
    cin >> n;

    vector<Domino> dominoes(n);
    vector<bool> used(n, false);
    vector<Domino> result;

    for (int i = 0; i < n; i++) {
        cout << "Enter left and right dots for domino " << i + 1 << ": ";
        cin >> dominoes[i].leftDots >> dominoes[i].rightDots;
    }

    bool chainFound = false;

    for (int i = 0; i < n; i++) {
        used[i] = true;
        result.push_back(dominoes[i]);

        if (canFormChain(dominoes, used, dominoes[i].rightDots, 1, result, n)) {
            chainFound = true;
            break;
        }

        used[i] = false;
        result.pop_back();
    }

    if (chainFound) {
        cout << "true" << endl;
        for (size_t i = 0; i < result.size(); i++) {
            if (i > 0) {
                cout << " , ";
            }
            cout << result[i].leftDots << "|" << result[i].rightDots;
        }
        cout << endl;
    } else {
        cout << "false" << endl;
    }
}

string readAndFormatInput() {
    string s, temp;
    cout << "enter the text : " << endl;

    while (true) {
        getline(cin, temp);

        if (temp.length() > maxLength) {
            cout << "The input exceeds the maximum length of " << maxLength << " characters. Please try again." << endl;
            continue;
        }

        if (temp.find('.') != string::npos) {
            s += temp;
            break;
        }

        s += temp + " ";
    }

    if (s.empty()) {
        return "";
    }

    string name = "";
    bool firstChar = true;
    bool space = true;

    for (int i = 0; i < s.length(); i++) {
        char a = s[i];
        if (a != ' ') {
            if (firstChar) {
                name += toupper(a);
                firstChar = false;
                space = false;
            } else {
                name += tolower(a);
                space = false;
            }
        } else if (!space) {
            name += ' ';
            space = true;
        }
    }

    return name;
}

void sieve(int n) {
    bool arr[n + 1];

    for (int i = 0; i <= n; i++) {
        arr[i] = true;
    }

    for (int i = 2; i * i <= n; i++) {
        if (arr[i]) {
            for (int j = i * i; j <= n; j += i) {
                arr[j] = false;
            }
        }
    }

    for (int i = 2; i <= n; i++) {
        if (arr[i]) {
            cout << i << endl;
        }
    }
}

char getValidRetryInput() {
    string input;
    while (true) {
        cout << "Do you want to choose another option? (y/n): ";
        cin >> input;

        if (input == "y" || input == "Y") {
            return 'y';
        } else if (input == "n" || input == "N") {
            return 'n';
        } else {
            cout << "Invalid input. Please enter 'y' or 'n'." << endl; // رسالة الخطأ في حالة إدخال غير صحيح
        }
    }
}

void menu() {
    char retry;

    do {
        int choice;
        cout << "Choose a problem to run:" << endl;
        cout << "1. Process File" << endl;
        cout << "2. Dominoes" << endl;
        cout << "3. Read and Format Input" << endl;
        cout << "4. Sieve of Eratosthenes" << endl;

        while (true) {
            try {
                cout << "Enter your choice: ";
                cin >> choice;

                // تحقق من الإدخال (إدخال غير صحيح)
                if (cin.fail()) {
                    throw invalid_argument("Invalid choice. Please choose a number between 1 and 4.");
                }

                switch (choice) {
                    case 1: {
                        unordered_map<string, string> alternatives = {
                                {"إرهاب",   "تهديد"},
                                {"تعذيب",   "ألم"},
                                {"فساد",    "انحراف"},
                                {"خداع",    "تضليل"},
                                {"إغتصاب",  "اعتداء"},
                                {"مظاهرات", "احتجاجات"},
                                {"كذب",     "زور"},
                                {"كراهية",  "عداء"},
                                {"حرية",    "تحرر"},
                                {"سلام",    "هدنة"},
                                {"سياسة",   "إدارة"},
                                {"دين",     "معتقد"},
                                {"حرب",     "نزاع"},
                                {"فقر",     "عوز"},
                                {"تغيير",   "تحول"},
                                {"ثورة",    "انتفاضة"},
                                {"خيانة",   "غدر"},
                                {"تطرف",    "تشدد"},
                                {"سرقة",    "نهب"},
                                {"فوضى",    "اضطراب"},
                                {"ظلم",     "اضطهاد"},
                                {"اختصاب",  "اختطاف"},
                                {"الارضي",  "الأرضي"}
                        };

                        cout << "Enter the file name with (.txt): ";
                        string file_name;
                        cin >> file_name;
                        cin.ignore();
                        cout << "The new file is: output_changed_" + file_name << endl;

                        processFile(file_name, alternatives);
                        break;
                    }
                    case 2:
                        dominoes_function();
                        break;
                    case 3: {
                        string formattedName = readAndFormatInput();
                        cout << formattedName << endl;
                        break;
                    }
                    case 4: {
                        cout << "enter the num : " << endl;
                        int n;
                        cin >> n;
                        sieve(n);
                        break;
                    }
                    default:
                        throw invalid_argument("Invalid choice. Please choose a number between 1 and 4.");
                }
                break; // break out of the input loop if valid choice is made
            } catch (invalid_argument &e) {
                cout << e.what() << endl; // Print error message
                cin.clear(); // Clear the error flag
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            }
        }

        retry = getValidRetryInput();

    } while (retry == 'y');

    cout << "Exiting the program." << endl;
}

int main() {
    menu();
    return 0;
}
