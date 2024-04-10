struct C {
    P o; T r;
    // circle-line intersection, assuming it exists
    // points are sorted along the direction of the line
    pair<P, P> line_inter(L l) const {
        P c = l.closest_to(o); T c2 = (c - o).magsq();
        P e = l.d * sqrt(max(r*r - c2, T()) / l.d.magsq());
        return {c - e, c + e};
    }
    // check the type of line-circle collision
    // <0: 2 inters, =0: 1 inter, >0: 0 inters
    T line_collide(L l) const {
        T c2 = (l.closest_to(o) - o).magsq();
        return c2 - r * r;
    }
    // calculates the two intersections between two circles
    // the circles must intersect in one or two points!
    pair<P, P> inter(C h) const {
        P d = h.o - o;
        T c = (r * r - h.r * h.r) / d.magsq();
        return h.line_inter({(1 + c) / 2 * d, d.rot()});
    }
    // check if the given circles intersect
    bool collide(C h) const {
        return (h.o - o).magsq() <= (h.r + r) * (h.r + r);
    }
    // get one of the two tangents that go through the point
    // the point must not be inside the circle
    // a = -1: cw (relative to the circle) tangent
    // a =  1: ccw (relative to the circle) tangent
    P point_tangent(P p, T a) const {
        T c = r * r / p.magsq();
        return o + c*(p-o) - a*sqrt(c*(1-c))*(p-o).rot();
    }
    // get one of the 4 tangents between the two circles
    // a =  1: exterior tangents
    // a = -1: interior tangents (requires no area overlap)
    // b =  1: ccw tangent
    // b = -1: cw tangent
    // the line origin is on this circumference, and the
    // direction is a unit vector towards the other circle
    L tangent(C c, T a, T b) const {
        T dr = a * r - c.r;
        P d = c.o - o;
        P n = (d*dr+b*d.rot()*sqrt(d.magsq()-dr*dr)).unit();
        return {o + n * r, -b * n.rot()};
    }
    // circumcircle of a **non-degenerate** triangle
    static C thru_points(P a, P b, P c) {
        b = b - a, c = c - a;
        P p = (b*c.magsq() - c*b.magsq()).rot() / (b%c*2);
        return {a + p, p.mag()};
    }
    // find the two circles that go through the given point,
    // are tangent to the given line and have radius `r`
    // the point-line distance must be at most `r`!
    // the circles are sorted in the direction of the line
    static pair<C, C> thru_point_line_r(P a, L t, T r) {
        P d = t.d.rot().unit();
        if (d * (a - t.o) < 0) d = -d;
        auto p = C(a, r).line_inter({t.o + d * r, t.d});
        return {{p.first, r}, {p.second, r}};
    }
    // find the two circles that go through the given points
    // and have radius `r`
    // circles sorted by angle from the first point
    // the points must be at most at distance `r`!
    static pair<C, C> thru_points_r(P a, P b, T r) {
        auto p = C(a, r).line_inter({(a+b)/2, (b-a).rot()});
        return {{p.first, r}, {p.second, r}};
    }
    vector<P> linecol(L l){
        vector<P> s;P p=l.closest_to(o);double d=(p-o).norm();
        if(d-EPS>r)return s;
        if(abs(d-r)<=EPS){s.pb(p);return s;}
        d=sqrt(r*r-d*d); s.pb(p+l.pq.unit()*d); s.pb(p-l.pq.unit()*d);
        return s;
    }
	double intertriangle(P a,P b){ // intersection with oab
		if(abs((o-a)%(o-b))<=EPS)return 0.;
		vector<P> q={a},w=linecol(L{a,b-a});
		if(w.size()==2)for(auto p:w)if((a-p)*(b-p)<-EPS)q.pb(p);
		q.pb(b);
		if(q.size()==4&&(q[0]-q[1])*(q[2]-q[1])>EPS)swap(q[1],q[2]);
		double s=0;
		fore(i,0,q.size()-1){
			if(!has(q[i])||!has(q[i+1]))s+=r*r*(q[i]-o).angle(q[i+1]-o)/2;
			else s+=abs((q[i]-o)%(q[i+1]-o)/2);
		}
		return s;
	}
};