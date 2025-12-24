#include "storage/serializer.h"
#include <cstring>

std::vector<char> serializeUser(const User& u) {
    std::vector<char> buf;

    int32_t name_len = static_cast<int32_t>(u.name.size());
    buf.resize(sizeof(int32_t) * 3 + name_len);

    char* p = buf.data();

    memcpy(p, &u.id, sizeof(int32_t));
    p += sizeof(int32_t);

    memcpy(p, &name_len, sizeof(int32_t));
    p += sizeof(int32_t);

    memcpy(p, u.name.data(), name_len);
    p += name_len;

    memcpy(p, &u.age, sizeof(int32_t));

    return buf;
}


User deserializeUser(const char* data) {
    User u;
    const char* p = data;

    memcpy(&u.id, p, sizeof(int32_t));
    p += sizeof(int32_t);

    int32_t name_len;
    memcpy(&name_len, p, sizeof(int32_t));
    p += sizeof(int32_t);

    u.name.resize(name_len);
    memcpy(u.name.data(), p, name_len);
    p += name_len;

    memcpy(&u.age, p, sizeof(int32_t));

    return u;
}