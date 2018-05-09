#ifndef QTBASIC_HPP
#define QTBASIC_HPP

#include <QString>

inline QString operator ""_qs(const char * a,std::size_t b){
    return QString::fromUtf8(a,static_cast<int>(b));
}

Q_CONSTEXPR inline QLatin1String operator ""_q1s(const char * a,std::size_t b){
    return QLatin1String{a,static_cast<int>(b)};
}

#endif // QTBASIC_HPP
