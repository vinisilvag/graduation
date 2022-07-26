#include "google_password.hpp"

#include <iostream>

void GooglePassword::insert(const std::string& url,
                            const std::string& login,
                            const std::string& password) {
  if(this->checkPassword(password)) {
    Usuario user(login, password);

    this->m_passwords.insert(std::pair<std::string, Usuario>(url, user));
  }
}

void GooglePassword::remove(const std::string& url) {
  std::map<std::string, Usuario>::iterator it;
  bool is_removed = false;

  for (it = this->m_passwords.begin(); it != this->m_passwords.end() and is_removed != true; it++){
    if(it->first == url) {
      this->m_passwords.erase(it);
      is_removed = true;
    }
  }
}


void GooglePassword::update(const std::string& url,
                            const std::string& login,
                            const std::string& old_password,
                            const std::string& password) {
  std::map<std::string, Usuario>::iterator it;

  for (it = this->m_passwords.begin(); it != this->m_passwords.end(); it++){
    if(it->first == url) {
      if(old_password == it->second.getPassword()) {
        if(this->checkPassword(password)) {
          it->second.setPassword(password);          
          it->second.setLogin(login);          
        }
      }
    }
  }
}

void GooglePassword::printPasswords() {
  std:: cout << this->m_passwords.size() << std::endl;

  for(auto const& it : this->m_passwords) {
    std::cout << it.first << ": " << it.second.getLogin() << " and " << it.second.getPassword() << std::endl;
  }
}

bool GooglePassword::checkPassword(const std::string& password) const {
  if(password.size() < 6)
    return false;

  if(password.size() > 50)
    return false;

  for(unsigned i = 0; i < password.size(); i++) {
    if(password[i] == ' ')
      return false;
  }

  int aux = 0;

  for(unsigned i = 0; i < password.size(); i++) {
    if(password[i] - '0' == aux + 1)
      aux++;
    else
      aux = 0;

    if(aux == 6)
      return false;
  }

  return true;
}
