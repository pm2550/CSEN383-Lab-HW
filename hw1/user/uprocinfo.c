#include "types.h"
#include "stat.h"
#include "procinfo.h"
#include "user/user.h"

int uprocinfo(struct pinfo *in) {
    return procinfo(in);
}
