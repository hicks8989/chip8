# include "register.h"

template<typename T>
void Register<T>::write(T val) {
    value = val;
}

template<typename T>
T Register<T>::read() const {
    return value;
}

void FlagReg::write_flag(Bit bit) {
    value = (value & ~1) | (bit ? 1 : 0);
}

Bit FlagReg::read_flag() const {
    return value & 1;
}

void AddressReg::write(Address addr) {
    value = addr & 0x0FFF;
}

Address AddressReg::read() const {
    return value & 0x0FFF;
}
