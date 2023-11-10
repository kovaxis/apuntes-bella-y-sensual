// a segment or an infinite line
// does not handle point segments correctly!
struct L {
    P o, d;

    static L from_eq(P ab, T c) {
        return L{ab.rot(), ab * -c / ab.magsq()};
    }
    pair<P, T> line_eq() { return {-d.rot(), d.rot() * o}; }

    // on which side of the line is the point
    // negative: left, positive: right
    T side(P r) const { return (r - o) % d; }

    // returns the intersection coefficient
    // in the range [0, d % r.d]
    // if d % r.d is zero, the lines are parallel
    T inter(L r) const { return (r.o - o) % r.d; }

    // get the single intersection point
    // lines must not be parallel
    P intersection(L r) const {return o+d*inter(r)/(d%r.d);}

    // check if lines are parallel
    bool parallel(L r) const { return abs(d % r.d) <= EPS; }

    // check if segments intersect
    bool seg_collide(L r) const {
        T z = d % r.d;
        if (abs(z) <= EPS) {
            if (abs(side(r.o)) > EPS) return false;
            T s = (r.o - o) * d, e = s + r.d * d;
            if (s > e) swap(s, e);
            return s <= d * d + EPS && e >= -EPS;
        }
        T s = inter(r), t = -r.inter(*this);
        if (z < 0) s = -s, t = -t, z = -z;
        return s>=-EPS && s<=z+EPS && t>=-EPS && t<=z+EPS;
    }

    // full segment intersection
    // makes a point segment if the intersection is a point
    // however it does not handle point segments as input!
    bool seg_inter(L r, L *out) const {
        T z = d % r.d;
        if (abs(z) <= EPS) {
            if (abs(side(r.o)) > EPS) return false;
            if (r.d * d < 0) r = {r.o + r.d, -r.d};
            P s = o * d < r.o * d ? r.o : o;
            P e = (o+d)*d < (r.o+r.d)*d ? o+d : r.o+r.d;
            if (s * d > e * d) return false;
            return *out = {s, e - s}, true;
        }
        T s = inter(r), t = -r.inter(*this);
        if (z < 0) s = -s, t = -t, z = -z;
        if (s>=-EPS && s<=z+EPS && t>=-EPS && t<=z+EPS)
            return *out = {o + d * s / z, {0, 0}}, true;
        return false;
    }

    // check if the given point is on the segment
    bool point_on_seg(P r) const {
        if (abs(side(r)) > EPS) return false;
        if ((r - o) * d < -EPS) return false;
        if ((r - o - d) * d > EPS) return false;
        return true;
    }

    // point in this line that is closest to a given point
    P closest_to(P r) const {
        P dr = d.rot(); return r + dr*((o-r)*dr)/d.magsq();
    }
};
