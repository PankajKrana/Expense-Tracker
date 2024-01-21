#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// Define a structure to represent an expense entry
struct Expense {
  string date;
  string description;
  double amount;
};

const int MAX_EXPENSES = 100; // Maximum number of expenses

// Function to read expenses from a CSV file
int readExpenses(Expense expenses[], const string &filename) {
  ifstream file(filename);
  int count = 0;

  if (file.is_open()) {
    string line;
    while (count < MAX_EXPENSES && getline(file, line)) {
      stringstream ss(line);
      getline(ss, expenses[count].date, ',');
      getline(ss, expenses[count].description, ',');
      ss >> expenses[count].amount;
      count++;
    }

    file.close();
  }

  return count;
}

// Function to write expenses to a CSV file (append mode)
void writeExpenses(Expense expenses[], int count, const string& filename) {
    ofstream file(filename, ios::out | ios::app);  // Open the file in append mode

    if (file.is_open()) {
        for (int i = 0; i < count; ++i) {
            file << expenses[i].date << ',' << expenses[i].description << ',' << expenses[i].amount << '\n';
        }

        file.close();
    } else {
        cerr << "Error opening file: " << filename << endl;
    }
}

int main() {
  // Sample expenses
  Expense expenses[MAX_EXPENSES];
  int numExpenses = 0;

  // Get user input for expenses
  cout << "Enter expenses. Type 'done' when finished.\n";

  string addMore;
  do {
    cout << "Expense #" << numExpenses + 1 << ":\n";

    cout << "Date: ";
    getline(cin, expenses[numExpenses].date);

    if (expenses[numExpenses].date == "done" || expenses[numExpenses].description == "done") {
      break;
    }

    cout << "Description: ";
    getline(cin, expenses[numExpenses].description);

    cout << "Amount: ";
    cin >> expenses[numExpenses].amount;
    cin.ignore(); // Consume the newline character

    numExpenses++;

    // Ask the user if they want to add more expenses
    cout << "Do you want to add more expenses? (yes/no): ";
    getline(cin, addMore);
  } while (addMore == "yes");

  // File to store expenses
  const string filename = "expenses.csv";

  // Write expenses to the CSV file
  writeExpenses(expenses, numExpenses, filename);

  // Read expenses from the CSV file
  int readCount = readExpenses(expenses, filename);

  // Display the read expenses
  cout << "Read Expenses:\n";
  for (int i = 0; i < readCount; ++i) {
    cout << "Date: " << expenses[i].date << ", Description: " << expenses[i].description << ", Amount: " << expenses[i].amount << "\n";
  }

  return 0;
}
