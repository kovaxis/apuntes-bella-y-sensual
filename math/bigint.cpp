#include "../common.h"

using u32 = uint32_t;
using u64 = uint64_t;

// signed bigint
struct bigint {
    vector<u32> digits;
    u32 neg;

    bigint() : neg(0) {}
    bigint(ll x) : digits{lo(x), hi(x)}, neg(x < 0 ? ~0 : 0) { this->trim(); }
    bigint(vector<u32> d) : digits(d), neg(0) {}

    static u32 lo(u64 dw) { return (u32)dw; }
    static u32 hi(u64 dw) { return (u32)(dw >> 32); }

    // remove leading zeros from representation
    void trim() {
        while (digits.size() && digits.back() == neg) digits.pop_back();
    }

    void add(const bigint &rhs, u32 c = 0) {
        int ls = digits.size();
        int rs = rhs.digits.size();
        rep(i, max(ls, rs)) {
            if (i >= ls) digits.push_back(neg);
            u64 r = (u64)digits[i] + (i < rs ? rhs.digits[i] : rhs.neg) + c;
            digits[i] = lo(r), c = hi(r);
        }
        u64 ec = (u64)c + neg + rhs.neg;
        neg = ((hi(ec) ^ neg ^ rhs.neg) & 1 ? ~0 : 0);
        if (lo(ec) != neg) digits.push_back(lo(ec));
    }
    bigint &operator+=(const bigint &rhs) {
        this->add(rhs);
        return *this;
    }
    bigint &operator+=(u32 rhs) {
        this->add({}, rhs);
        return *this;
    }

    void negate() {
        rep(i, digits.size()) digits[i] = ~digits[i];
        neg = ~neg;
        this->add({}, 1);
    }

    bigint negated() const {
        bigint out = *this;
        out.negate();
        return out;
    }

    bigint &operator-=(const bigint &rhs) {
        this->negate();
        *this += rhs;
        this->negate();
        return *this;
    }

    bigint &operator*=(bigint &rhs) {
        static bigint lhs;
        swap(*this, lhs), digits.clear(), neg = 0;
        u32 r = rhs.neg, s = 0;
        if (lhs.neg) s ^= lhs.neg, lhs.negate();
        if (rhs.neg) s ^= rhs.neg, rhs.negate();
        rep(j, rhs.digits.size()) {
            u64 c = 0;
            int ls = digits.size();
            int rs = lhs.digits.size();
            repx(i, j, max(ls, rs + j)) {
                if (i >= ls) digits.push_back(0);
                u64 r =
                    (u64)digits[i] +
                    (u64)(i - j < rs ? lhs.digits[i - j] : 0) * rhs.digits[j] +
                    c;
                digits[i] = lo(r), c = hi(r);
            }
            if (c != 0) digits.push_back(c);
        }
        if (r) rhs.negate();
        if (s) negate();
        return *this;
    }

    bigint &operator/=(bigint &rhs) {
        divmod(rhs);
        return *this;
    }
    bigint &operator%=(bigint &rhs) {
        *this = divmod(rhs);
        return *this;
    }

    int divmod_trunc(int rhs) {
        u32 s = (rhs < 0 ? ~0 : 0) ^ this->neg, q = abs(rhs);
        u64 r = 0;
        if (this->neg) this->negate();
        invrep(i, digits.size()) {
            r = (r << 32) | digits[i];
            digits[i] = r / q, r %= q;
        }
        if (s) {
            this->negate();
            return -(int)r;
        }
        return (int)r;
    }

    // compares `this` with `rhs`
    //  `this < rhs`: -1
    //  `this == rhs`: 0
    //  `this > rhs`: 1
    int cmp(const bigint &rhs) const {
        if (neg && !rhs.neg) return -1;
        if (!neg && rhs.neg) return 1;
        int ls = digits.size(), rs = rhs.digits.size();
        invrep(i, max(ls, rs)) {
            u32 l = i < ls ? digits[i] : neg;
            u32 r = i < rs ? rhs.digits[i] : rhs.neg;
            if (l < r) return -1;
            if (l > r) return 1;
        }
        return 0;
    }

    bool operator==(const bigint &rhs) const { return cmp(rhs) == 0; }
    bool operator!=(const bigint &rhs) const { return cmp(rhs) != 0; }
    bool operator<(const bigint &rhs) const { return cmp(rhs) == -1; }
    bool operator>=(const bigint &rhs) const { return cmp(rhs) != -1; }
    bool operator>(const bigint &rhs) const { return cmp(rhs) == 1; }
    bool operator<=(const bigint &rhs) const { return cmp(rhs) != 1; }

    friend ostream &operator<<(ostream &s, const bigint &self) {
        if (self == bigint()) return s << "0";
        bigint x = self;
        if (x.neg) {
            x.negate();
            s << "-";
        }
        vector<int> digs;
        while (x != bigint()) digs.push_back(x.divmod_trunc(10));
        invrep(i, digs.size()) s << digs[i];
        return s;
    }

    // truncating division and modulo
    bigint divmod(bigint &rhs) {
        assert(rhs != bigint());
        u32 sr = rhs.neg, s = neg ^ rhs.neg;
        if (neg) negate();
        if (sr) rhs.negate();
        bigint l = 0, r = *this, x;
        r += 1u;
        while (l != r) {
            bigint m = l;
            m += r;
            rep(i, m.digits.size()) m.digits[i] =
                (m.digits[i] >> 1) |
                (i + 1 < m.digits.size() ? m.digits[i + 1] << 31 : 0);
            x = m, x *= rhs;
            if (x <= *this) {
                l = (m += 1);
            } else {
                r = m;
            }
        }
        l -= 1, swap(l, *this);
        r = *this, r *= rhs, l -= r;
        trim(), l.trim();
        if (sr) rhs.negate();
        if (s) negate(), l.negate();
        return l;
    }
};
