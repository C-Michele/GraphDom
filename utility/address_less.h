#ifndef ADDRESS_LESS_H
#define ADDRESS_LESS_H

namespace MAIN_LIBRARY_NAMESPACE::utility {
    template <typename T>
    class address_less final {
        public:
            constexpr bool operator()(const T& left, const T& right) const {
                return &left < &right;
            }
    };
}

#endif //ADDRESS_LESS_H
