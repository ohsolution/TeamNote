typedef long double val;

struct point // 점
{
	val x;
	val y;

	bool operator >(point& b)
	{
		return x == b.x ? y > b.y : x > b.x;
	}
};

struct vec //벡터 시작점,끝점,방향
{
	point sp;
	point ep;
	val dx, dy;
};

inline vec findV(point a, point b) { return {a,b, b.x - a.x ,b.y - a.y }; } //  vec a,b 반환
inline val ptp(point a, point b) { return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y); } // 점 점 거리

inline val outerP(vec v , vec u) // 벡터 외적
{
	return v.dx * u.dy - u.dx * v.dy;
}

int dotP(point v, point u) // 벡터 내적
{
	val temp = (v.x * u.x + v.y * u.y);
	if (temp > 0) return 1; // 벡터 정방향
	else if (temp == 0) return 0; // 벡터 수직
	else return -1; // 벡터 역방향
}

int ccw(vec v, vec u) // ccw
{
	val temp = outerP(v, u);
	if (temp > 0) return 1; // 반시계
	else if (temp == 0) return 0; // 평행
	else return -1; // 시계
}

bool Isintersect(vec v, vec u) // 선분교차 판정
{	
	int ab = ccw(v, findV(v.sp,u.sp)) * ccw(v, findV(v.sp,u.ep));
	int cd = ccw(u, findV(u.sp,v.sp)) * ccw(u,findV(u.sp,v.ep));

	if (ab == 0 && cd == 0) {
		
		if (v.sp > v.ep) swap(v.sp, v.ep);
		if (u.sp > u.ep) swap(u.sp, u.ep);
		return !(u.sp > v.ep || v.sp > u.ep);
	}
	return ab <= 0 && cd <= 0;
}
