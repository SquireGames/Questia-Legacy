#ifndef TOGGLER_H
#define TOGGLER_H

namespace utl
{

class Toggler
{
public:
    Toggler(bool initValue = true);
    ~Toggler();

    bool toggle();
private:
    bool value;
};

}

#endif // TOGGLER_H
