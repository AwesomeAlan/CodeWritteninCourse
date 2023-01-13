#include<socket-wrapper.h>

std::ostream& operator<< (std::ostream& out , const SocketWrapper& object)
{
    object.print(out);
    return out;
}