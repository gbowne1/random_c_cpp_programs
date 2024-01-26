#include "permissions.h"

#include <algorithm>

User::User(const std::string& userId) 
    : userId(userId) 
{
}

bool User::hasPermission(Permission permission) {
    return (std::find(this->permissions.begin(), this->permissions.end(), permission) 
                != this->permissions.end());
}

bool User::ownsResource(std::shared_ptr<Resource> resource) {
    return resource->isOwnedBy(this->userId);
}