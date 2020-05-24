#include <cstdlib>
#include <ctime>

namespace sqlearn
{
    void fill_random(char *buffer, int size)
    {
        srand((unsigned int) time(NULL));
        for (int i = 0; i != size; ++i) {
            buffer[i] = rand();
        }
    }
}
