#ifndef PASSSERVER_H
#define PASSSERVER_H

#include <iostream>
#include <unistd.h>
#include "hashtable.h"

class PassServer {
        public:
            PassServer(size_t size = 101); // Constructor
            ~PassServer(); // Destructor
            bool load(const char *filename); // Load password file into HashTable object
            bool addUser(std::pair<std::string, std::string> & kv); // Add new username and password
            bool addUser(std::pair<std::string, std::string> && kv); // Move version of addUser(...)
            bool removeUser(const std::string & k); // Delete existing user
            bool changePassword(const std::pair<std::string, std::string> &p,
                                const std::string &newpassword); // Chnage existing user's password
            bool find(const std::string & user) const; // Check if user exists
            void dump(); // Display structure and contents of HashTable object
            size_t size() const; // Returns size of HashTable object
            bool write_to_file(const char *filename); // Save username and password combination into a file

        private:
            std::string encrypt(const std::string & str); // Encrypt the parameter
            cop4530::HashTable<std::string, std::string> server;

    };

#endif
