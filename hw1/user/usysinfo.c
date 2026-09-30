#include "types.h"
#include "stat.h"
#include "user/user.h"

int usysinfo(int param) {
    if(param>=0 && param<=2)// total number of active processes
    {
        return sysinfo(param);
    }   
    else{
        return -1;
    }
    return 0;
}