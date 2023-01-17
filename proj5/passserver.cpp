#include <iostream>
#include "passserver.h"

using namespace cop4530;

PassServer::PassServer(size_t size) : server(size) {

}

PassServer::~PassServer() {
    server.clear();
}

bool PassServer::load(const char *filename) {
    return server.load(filename);
}

bool PassServer::addUser(std::pair<std::string, std::string> & kv) {
    return server.insert(std::make_pair(kv.first, encrypt(kv.second)));
}

bool PassServer::addUser(std::pair<std::string, std::string> && kv) {
    return server.insert(std::move(std::make_pair(kv.first, encrypt(kv.second))));
}

bool PassServer::removeUser(const std::string & k) {
    return server.remove(k);
}

bool PassServer::changePassword(const std::pair<std::string, std::string> &p, const std::string &newpassword) {
    if (server.match(std::make_pair(p.first, encrypt(p.second))) == true && encrypt(p.second) != encrypt(newpassword)) {
            server.insert(std::make_pair(p.first, encrypt(newpassword)));
        return true;
    }

    return false;
}

bool PassServer::find(const std::string & user) const {
    return server.contains(user);
}

void PassServer::dump() {
    return server.dump();
}

size_t PassServer::size() const {
    return server.size();
}

bool PassServer::write_to_file(const char *filename) {
    return server.write_to_file(filename);
}

std::string PassServer::encrypt(const std::string & str) {
    char salt[] = "$1$########";
	char * password = new char [100];

    return strcpy(password, crypt(str.c_str(), salt));
}