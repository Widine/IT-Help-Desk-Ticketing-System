
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

// Ticket information
class Ticket {
public:
    int ticketID;
    string userName;
    string problem;
    string status;

    Ticket(int id, string name, string description) {
        ticketID = id;
        userName = name;
        problem = description;
        status = "New";
    }

    void displayTicket() {
        cout << "\nTicket Submitted Successfully!" << endl;
        cout << "-----------------------------" << endl;
        cout << "Ticket ID: " << ticketID << endl;
        cout << "Name: " << userName << endl;
        cout << "Problem: " << problem << endl;
        cout << "Status: " << status << endl;
    }
};

// Find the next ticket number
int getNextTicketID() {
    ifstream file("tickets.txt");
    string line;
    int lastID = 0;

    while (getline(file, line)) {
        if (line.rfind("Ticket ID: ", 0) == 0) {
            try {
                int id = stoi(line.substr(11));
                if (id > lastID) {
                    lastID = id;
                }
            } catch (...) {
                // Skip invalid ticket IDs
            }
        }
    }

    return lastID + 1;
}

// Save ticket to file
bool saveTicket(const Ticket& ticket) {
    ofstream file("tickets.txt", ios::app);

    if (!file.is_open()) {
        return false;
    }

    file << "Ticket ID: " << ticket.ticketID << endl;
    file << "Name: " << ticket.userName << endl;
    file << "Problem: " << ticket.problem << endl;
    file << "Status: " << ticket.status << endl;
    file << "-----------------------------" << endl;

    return file.good();
}

int main() {
    string name;
    string problem;

    cout << "================================" << endl;
    cout << "   IT HELP DESK TICKETING SYSTEM" << endl;
    cout << "================================" << endl;

    cout << "\nEnter your name: ";
    getline(cin, name);

    if (name.find_first_not_of(" \t") == string::npos) {
        cout << "Error: Name cannot be empty." << endl;
        return 1;
    }

    cout << "Describe your technology problem: ";
    getline(cin, problem);

    if (problem.find_first_not_of(" \t") == string::npos) {
        cout << "Error: Problem cannot be empty." << endl;
        return 1;
    }

    int ticketID = getNextTicketID();

    Ticket newTicket(ticketID, name, problem);

    if (saveTicket(newTicket)) {
        newTicket.displayTicket();
    } else {
        cout << "Error: Ticket could not be saved." << endl;
        return 1;
    }

    cout << "\nThank you for using the IT Help Desk!" << endl;

    return 0;
}
