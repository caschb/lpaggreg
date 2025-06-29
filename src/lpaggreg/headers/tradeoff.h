#ifndef TRADEOFF_H
#define TRADEOFF_H

#include <memory>
#include "quality.h"

using namespace std;

namespace lpaggreg{

    class Tradeoff
    {

    private:

        shared_ptr<Quality> quality;
        lp_quality_type value;

    public:
        Tradeoff();
        //Tradeoff(Tradeoff &tradeoff);
        Tradeoff(shared_ptr<Quality> quality);
        Tradeoff(lp_quality_type value, shared_ptr<Quality> quality);
        Tradeoff(shared_ptr<Quality> quality, float p);

        void computePIC(float p);

        Tradeoff &operator+=(const Tradeoff &tradeoff);
        Tradeoff &operator-=(const Tradeoff &tradeoff);
        Tradeoff &operator*=(const Tradeoff &tradeoff);
        Tradeoff &operator/=(const Tradeoff &tradeoff);

        void set(shared_ptr<Quality> quality, float p);

        shared_ptr<Quality> getQuality() const;
        lp_quality_type getValue() const;
    };

Tradeoff operator+(const Tradeoff &tradeoff1, const Tradeoff &tradeoff2);
Tradeoff operator-(const Tradeoff &tradeoff1, const Tradeoff &tradeoff2);
Tradeoff operator*(const Tradeoff &tradeoff1, const Tradeoff &tradeoff2);
Tradeoff operator/(const Tradeoff &tradeoff1, const Tradeoff &tradeoff2);
bool operator==(const Tradeoff &tradeoff1, const Tradeoff &tradeoff2);
bool operator!=(const Tradeoff &tradeoff1, const Tradeoff &tradeoff2);
bool operator<(const Tradeoff &tradeoff1, const Tradeoff &tradeoff2);
bool operator>(const Tradeoff &tradeoff1, const Tradeoff &tradeoff2);
bool operator<=(const Tradeoff &tradeoff1, const Tradeoff &tradeoff2);
bool operator>=(const Tradeoff &tradeoff1, const Tradeoff &tradeoff2);

}

#endif // TRADEOFF_H
