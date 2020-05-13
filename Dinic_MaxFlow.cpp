struct edge{
	int v,flow,cap,rev;
	edge(const int& V, const int& passing_flow, 
		 const int& capacity, const int& reverse_edge_index)
	{
		v = V, flow = passing_flow, 
		cap = capacity, rev = reverse_edge_index;
	}
};
class graph{
	int n;
	int *level;
	vt<edge> *adjlist;
public:
	graph(const int& N)
	{
		adjlist = new vt<edge>[N];
		n = N;
		level = new int[N];
	}
	
	void add(const int &u, const int &v, const int& cap)
	{
		adjlist[u].pb(edge(v,0,cap,adjlist[v].size()));
		adjlist[v].pb(edge(u,0,0,adjlist[u].size()-1));
	}
	
	queue<int> q;
	bool bfs(const int& s, const int& t)
	{
		fill(level, level+n, -1);
		q.push(s); level[s] = 0;
		vt<edge>::iterator i;
		while(!q.empty())
		{
			int u = q.front(); q.pop();
			for(i = adjlist[u].begin(); i != adjlist[u].end(); ++i)
			{
				edge &e = *i;
				if (level[e.v] < 0 && e.flow < e.cap)
				{
					level[e.v] = level[u] + 1;
					q.push(e.v);
				}
			}
		}
		return !(level[t] < 0);
	}
	
	int send_flow(const int& u, const int& t, int node[],
				int flow)
	{
		if (u ^ t)
		{
			for(; node[u] < adjlist[u].size(); ++node[u])
			{
				edge &e = adjlist[u][node[u]];
				if (level[e.v] == level[u]+1 && e.flow < e.cap)
				{
					int	temp = send_flow(e.v, t, node, 
								min(flow, e.cap - e.flow));
					if (temp > 0)
					{
						e.flow += temp,
						adjlist[e.v][e.rev].flow = e.flow;
						return temp;
					}
				}
			}
			return 0;
		}
		return flow;
	}
	
	int dinic_max_flow(const int& s, const int& t)
	{
		if (s ^ t)
		{
			int ans = 0;
			while(bfs(s,t))
			{
				int *node = new int[n+1];
				fill(node, node + n, 0);
				while(int flow = send_flow(s,t,node,INT_MAX))
				{
					ans += flow;
				}
			}
			return ans;
		}
		return -1;
	}
};
