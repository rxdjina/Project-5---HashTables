#include <iostream>
#include <termios.h>
#include <unistd.h>
#include "hashtable.h"
#include "passserver.h"

using namespace cop4530;

void Menu() {
  std::cout << "\n\n";
  std::cout << "l - Load From File" << std::endl;
  std::cout << "a - Add User" << std::endl;
  std::cout << "r - Remove User" << std::endl;
  std::cout << "c - Change User Password" << std::endl;
  std::cout << "f - Find User" << std::endl;
  std::cout << "d - Dump HashTable" << std::endl;
  std::cout << "s - HashTable Size" << std::endl;
  std::cout << "w - Write to Password File" << std::endl;
  std::cout << "x - Exit program" << std::endl;
  std::cout << "\nEnter choice : ";
}

std::string getpassword() {
  /*
    References:
      * https://www.gnu.org/software/libc/manual/html_node/getpass.html
      * https://stackoverflow.com/questions/13694170/how-do-i-hide-user-input-with-cin-in-c
  */

  termios t_old;
  tcgetattr(STDIN_FILENO, &t_old);

  // Diasble Echo 
  termios t_new = t_old;
  t_new.c_lflag &= ~ECHO;
  tcsetattr(STDIN_FILENO, TCSANOW, &t_new);

  // Get Input
  std::string password;
  std::cin >> password;

  // Restore Terminal
  tcsetattr(STDIN_FILENO, TCSANOW, &t_old);
  return password;
}

int main(void) {
  unsigned int capacity;
  char choice = '\0';
  std::string filename, username, password, newPassword;

  std::cout << "HashTable Capacity: " << std::endl;
  std::cin >> capacity;
  std::cout << std::endl;

  PassServer server(capacity);

  while (choice != 'x') {
    Menu();
    std::cin >> choice;
    std::cout << std::endl;

    switch (choice) {
      case 'l': // Load File
        std::cout << "Filename: ";
        std::cin >> choice;
        std::cout << std::endl;

        if (!server.load(filename.c_str())) {
          std::cout << "ERROR: FILE COULD NOT BE OPENED" << std::endl;
        }

        break;

      case 'a': // Add User
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << std::endl;
      
        std::cout << "Password: ";
        password = getpassword();
        std::cout << std::endl;

        if (server.addUser(std::make_pair(username, password))) {
          std::cout << "USER SUCCESSFULLY ADDED" << std::endl;
        } else {
          std::cout << "ERROR: USER ALREADY EXISTS" << std::endl;
          std::cout << "ERROR: USER COULD NOT BE ADDED" << std::endl;
        }

        break;
      
      case 'r': // Remove User
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << std::endl;

        if (server.removeUser(username)) {
          std::cout << username << " SUCCESSFULLY REMOVED" << std::endl;
        } else {
          std::cout << "ERROR: USER NOT FOUND" << std::endl;
          std::cout << "ERROR: USER COULD NOT BE REMOVED" << std::endl;
        }

        break;
      
      case 'c': // Change User Password
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << std::endl;
      
        std::cout << "Password: ";
        password = getpassword();
        std::cout << std::endl;

        std::cout << "New Password: ";
        newPassword = getpassword();
        std::cout << std::endl;

        if (server.changePassword(std::make_pair(username, password), newPassword)) {
          std::cout << "PASSWORD SUCCESSFULLY CHANGED" << std::endl;
        } else {
          std::cout << "ERROR: PASSWORD COULD NOT BE CHANGES" << std::endl;
        }

        break;

      case 'f': // Find User
        std::cout << "Username: ";
        std::cin >> username;
        std::cout << std::endl;

        if (server.find(username)) {
          std::cout << username << " SUCESSFULLY FOUND" << std::endl;
        } else {
          std::cout << "USER NOT FOUND" << std::endl;
        }

        break;

      case 'd': // Dump HashTable
        server.dump();
        break;

      case 's': // HashTable Size
        std::cout << "HashTable Capacity: " << server.size() << std::endl;
        break;
      
      case 'w': // Write to Password File
        std::cout << "Enter Password Filename: ";
        std::cin >> filename;
        std::cout << std::endl;

        if (!server.write_to_file(filename.c_str())) {
          std::cout << "ERROR: COULD NOT WRITE TO FILE" << std::endl;
        }

        break;

      case 'x': // Exit Program
        return EXIT_SUCCESS;
        break;

      default:
        std::cout << "ERROR: INVALID INPUT, PLEASE TRY AGAIN" << std::endl;
        break;
    } 

  }

  return 0;
}