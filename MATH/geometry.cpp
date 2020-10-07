typedef long double val;

struct point // 점
{
	val x;
	val y;
	val dx,dy; // 좌표정렬에 필요한 성분

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

point geteq(vec a, vec b) // 직선 교차점 좌표 반환 -> 선분교차 판단 시 교차하는지 여부 먼저 파악
{
	point ret = a.sp;
	val p = outerP(b, findV(a.sp, b.sp)) / outerP(a, b);

	ret.x += p * (a.dx);
	ret.y += p * (a.dy);
	if (!ccw(b, findV(b.sp, ret)))
	{
		return ret;
	}
	else
	{
		ret = a.sp;
		ret.x -= p * (a.dx);
		ret.y -= p * (a.dy);
		return ret;
	}
	return a.sp;
}

/*Convex_Hull*/

int n;
int arr[max_v];

bool cmp(point a,point b)
{
	if(a.dx * b.dy != a.dy * b.dx) return a.dy * b.dx < a.dx * b.dy;

	if(a.y != b.y) return a.y < b.y;
	return a.x < b.x;
}

void graham_scan() // 맨 좌측 하단 점을 기준으로 기준점과 각 점의 기울기가 낮은것 부터 점을 정렬한다.
{
	sort(arr,arr+n,cmp);
	arr[0].dx = 1;
	fa(i,1,n)
	{
		arr[i].dx = arr[i].x - arr[0].x;
		arr[i].dy = arr[i].y - arr[0].y;
 	}
	sort(arr,arr+n,cmp);
	return;
}


int convex(void) // 점들의 좌표를 입력받고 볼록각형을 생성 뒤 넓이를 구하는 예제
{
	cin >> n;
	fa(i,0,n) cin >> arr[i].x >> arr[i].y;

	if(n<=2)
	{
		cout << 0;
		return 0;
	}

	graham_scan();
	stack <int> st;
	st.push(0);
	st.push(1);

	int nxt = 2;

	while(nxt < n)
	{
		while(st.size() >=2)
		{
			int A,B;
			B = st.top(); st.pop();
			A = st.top();

			if(ccw(findV(arr[A],arr[B]),findV(arr[A],arr[nxt]))== 1)
			{
				st.push(B); break;
			}
		}
		st.push(nxt++);
	}


	/* 스택에 남아있는 정점들이 볼록다각형을 이루는 정점들의 번호 */

	point sp = arr[st.top()]; st.pop();
	vec sl = findV(sp,arr[st.top()]); st.pop();

	double ans = 0;

	while(!st.empty())
	{
		vec curl = findV(sp,arr[st.top()]); st.pop();
		ans += abs(outerP(sl,curl))/2;
		sl = curl;
	}

	return ans;
}	


