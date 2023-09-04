#ifndef USERDATABASE_INCLUDED
#define USERDATABASE_INCLUDED

#include <string>
#include <vector>
#include "treemm.h"

class User;

class UserDatabase
{
  public:
    UserDatabase();
    ~UserDatabase();
    bool load(const std::string& filename);
    User* get_user_from_email(const std::string& email) const;

  private:
    std::vector<User*> m_users;
    TreeMultimap<std::string, User*> m_useremail_tree;
};

#endif // USERDATABASE_INCLUDED
