#include "UserDatabase.h"
#include "User.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <vector>
#include "treemm.h"

using namespace std;

UserDatabase::UserDatabase()
{
    // Replace this line with correct code.
}

UserDatabase::~UserDatabase() { //delete dynamically allocated users in the vector
    for (auto user : m_users) {
            delete user;
        }
    m_users.clear();
}

bool UserDatabase::load(const string& filename) {
    ifstream infile(filename); // used to process .txt files
    if (!infile) {
      cerr << "Error: cannot open file " << filename << endl;
      return false;
    }

    string line;
    string full_name;
    string email;
    vector<string> watch_history;

    while (getline(infile, full_name)) {
//        cout << full_name << endl;
        getline(infile, email);
//        cout << email << endl;
        getline(infile, line); // the number of movies watched
//        cout << line << endl;
        while (getline(infile, line) && line != "") { //iterate until a blank line
            string line2 = line;
        //    cout << line2 << endl;
            watch_history.push_back(line2);
        }
        
        
        User* user = new User(full_name, email, watch_history); //create a new User with the data we got from .txt file
        m_users.push_back(user);
        m_useremail_tree.insert(email, user); //error here?
        watch_history.clear(); // clear history so we can restart with another user
        
    }
    
   // cerr << "got here" << endl;
    return true;
}

User* UserDatabase::get_user_from_email(const string& email) const {
    auto it = m_useremail_tree.find(email); //user treemm find function to find using email
    if (!it.is_valid()) {
        return nullptr;
    } else {
        return it.get_value();
    }
}
