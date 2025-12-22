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
