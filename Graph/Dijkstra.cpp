struct Edge
{
	int cost, to;
	Edge( int cost = 0, int to = 0 ) :cost(cost), to(to) {}
};

const int N = 1100;
int d[N], from[N];
vector<Edge> edge[N];

void dijkstra ( int beg )
{
	typedef tuple<int, int, int> T;
	priority_queue<T, vector<T>, greater<T>> que;
	que.push( make_tuple(0, beg, -1) );

	rep(i, N) d[i] = IINF;
	
	bool visit[N] = { false };
	while( !que.empty() ){
		auto p = que.top(); que.pop();

		int id, p_id, cost;
		tie(cost, id, p_id) = p;
		
		if( visit[id] ) continue;
		visit[id] = true;
		d[id] = cost;
		from[id] = p_id;

		rep(i, edge[id].size()){
			if( d[edge[id][i].to] < cost + edge[id][i].cost ) continue;
			que.push( make_tuple(cost + edge[id][i].cost, edge[id][i].to, id) );
		}
	}
}
