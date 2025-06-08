# ifndef REGISTER_H
# define REGISTER_H

# include "byte.h"

template<typename T>
class Register {
    protected:
    T value;

    public:
    Register() : value(0) {}
    virtual void write(T byte);
    virtual T read() const;
    virtual ~Register() = default;
};

typedef Register<Byte> Reg;

class AddressReg : public Register<Address> {
    public:
    virtual void write(Address byte);
    virtual Address read() const;
};

class FlagReg : public Reg {
    public:
    void write_flag(Bit bit);
    Bit read_flag() const;
};

#endif