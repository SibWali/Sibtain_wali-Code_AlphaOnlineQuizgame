#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <conio.h>
using namespace std;
struct Question
{
    string question;
    vector<string> choices;
    int correctAnswerIndex;
};
string getHiddenPassword()
{
    string password;
    char ch;
    while (true) {
        ch = _getch();  
        if (ch == 13) {  
            cout << endl;
            break;
        }
        else if (ch == 8) {  
            if (!password.empty()) {
                password.pop_back();
                cout << "\b \b";  
            }
        }
        else {
            password.push_back(ch);
            cout << '*';  
        }
    }
    return password;
}
void registerUser(unordered_map<string, string>& users)
{
    string username, password;
    cout << "Register\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    password = getHiddenPassword();
    users[username] = password;
    cout << "User registered successfully!\n\n";
}
bool loginUser(const unordered_map<string, string>& users, string& loggedInUser)
{
    string username, password;
    cout << "Login\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    password = getHiddenPassword();

    auto it = users.find(username);
    if (it != users.end() && it->second == password) {
        cout << "Login successful!\n\n";
        loggedInUser = username;
        return true;
    }
    else {
        cout << "Invalid username or password.\n\n";
        return false;
    }
}
int takeQuiz(const vector<Question>& questions) 
{
    int score = 0;
    int answer;

    for (const auto& question : questions) {
        cout << question.question << endl;
        for (size_t i = 0; i < question.choices.size(); ++i) {
            cout << i + 1 << ". " << question.choices[i] << endl;
        }
        cout << "Your answer: ";
        cin >> answer;

        if (answer - 1 == question.correctAnswerIndex) {
            cout << "Correct!\n\n";
            ++score;
        }
        else {
            cout << "Incorrect. The correct answer is: " << question.choices[question.correctAnswerIndex] << "\n\n";
        }
    }

    return score;
}
void giveFeedback(int score, int totalQuestions)
{
    cout << "You scored " << score << " out of " << totalQuestions << "!\n";

    if (score <= 5) {
        cout << "Feedback: Bad\n";
    }
    else if (score == 6) {
        cout << "Feedback: Average\n";
    }
    else if (score == 7) {
        cout << "Feedback: Above Average\n";
    }
    else if (score == 8) {
        cout << "Feedback: Good Score\n";
    }
    else if (score == 9) {
        cout << "Feedback: Very Good\n";
    }
    else if (score == 10) {
        cout << "Feedback: Excellent\n";
    }
    cout << endl;
}
int main() {
    unordered_map<string, string> users;  
    vector<Question> questions = {
        {"What is the capital of France?", {"Paris", "London", "Berlin", "Madrid"}, 0},
        {"What is 2 + 2?", {"3", "4", "5", "6"}, 1},
        {"Who wrote 'Hamlet'?", {"Shakespeare", "Hemingway", "Fitzgerald", "Orwell"}, 0},
        {"What is the largest planet in our solar system?", {"Earth", "Mars", "Jupiter", "Venus"}, 2},
        {"Which element has the chemical symbol 'O'?", {"Oxygen", "Gold", "Iron", "Hydrogen"}, 0},
        {"What is the powerhouse of the cell?", {"Nucleus", "Mitochondria", "Ribosome", "Golgi apparatus"}, 1},
        {"What is the most abundant gas in the Earth's atmosphere?", {"Oxygen", "Nitrogen", "Carbon Dioxide", "Helium"}, 1},
        {"Which planet is known as the Red Planet?", {"Venus", "Saturn", "Mars", "Mercury"}, 2},
        {"What is the chemical symbol for water?", {"O", "H2O", "CO2", "H2"}, 1},
        {"Who developed the theory of relativity?", {"Isaac Newton", "Galileo Galilei", "Nikola Tesla", "Albert Einstein"}, 3}
    };

    string loggedInUser;

    while (true) {
        cout << "1. Register\n2. Login\n3. Exit\n";
        int choice;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            registerUser(users);
        }
        else if (choice == 2) {
            if (loginUser(users, loggedInUser)) {
                int score = takeQuiz(questions);
                giveFeedback(score, questions.size());
            }
        }
        else if (choice == 3) {
            break;
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }
    system("pause");
    return 0;
}
