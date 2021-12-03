// #include <sstream>
#include <WString.h>

namespace std
{
    struct stringstream
    {
        stringstream() = default;
        stringstream(String arg) :
            s(arg) { }

        const String& str() const
        {
            return s;
        }

        // Arithmetic types: int, float, ...
        template <class T>
        stringstream operator<<(T arg)
        {
            s += String(arg);
            return *this;
        }

        stringstream operator<<(const char* arg)
        {
            s += arg;
            return *this;
        }

        stringstream operator<<(const String arg)
        {
            s += arg;
            return *this;
        }

        // Single char: 'a', '\n', ...
        stringstream& operator<<(char arg)
        {
            s += arg;
            return *this;
        }

      private:
        String s;
    };
} // namespace std
