struct flow_edge{
	int v,flow,cap,rev;
	flow_edge(const int& V, const int& passing_flow, 
		 const int& capacity, const int& reverse_edge_index_in_adjlist)
	{
		v = V, flow = passing_flow, 
		cap = capacity, rev = reverse_edge_index_in_adjlist;
	}
};
ostream& operator << (ostream &stream, const flow_edge& e){
	return stream << "connected to node " << e.v << " with (" << e.flow << '/' << e.cap << ')';
}
class flow_graph{
	int n;
	vi level;
public:
	vt<vt<flow_edge> > adjlist;
	flow_graph(int N) {n = N, adjlist = vt<vt<flow_edge> >(N), level = vi(N);}
	flow_graph(const vt<vi> &other)    {n = other.size(), adjlist = vt<vt<flow_edge> >(n), level = vi(n); for(int i = 0; i < other.size(); ++i) for(int j: other[i]) add(i,j);};
	flow_graph(const vt<vpii> &other)  {n = other.size(), adjlist = vt<vt<flow_edge> >(n), level = vi(n); for(int i = 0; i < other.size(); ++i) for(pii j: other[i]) add(i,j.fi, j.se);};
	flow_graph(const flow_graph &other){n = other.adjlist.size(), adjlist = other.adjlist, level = vi(n);}
	flow_graph& operator= (const flow_graph& other){n = other.adjlist.size(), adjlist = other.adjlist, level = vi(n); return *this;}
	
	void add(const int &u, const int &v, const int& cap = 1,
			const int& currflow = 0)
	{
		adjlist[u].pb(flow_edge(v, currflow,cap,adjlist[v].size()));
		adjlist[v].pb(flow_edge(u,-currflow,0,adjlist[u].size()-1));
	}
	
	queue<int> q;
	bool bfs(const int& s, const int& t)
	{
		fill(level.begin(), level.end(), -1);
		q.push(s); level[s] = 0;
		vt<flow_edge>::iterator i;
		while(!q.empty())
		{
			int u = q.front(); q.pop();
			for(i = adjlist[u].begin(); i != adjlist[u].end(); ++i)
			{
				flow_edge &e = *i;
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
				const int& flow = INT_MAX)
	{
		if (u ^ t)
		{
			for(; node[u] < adjlist[u].size(); ++node[u])
			{
				flow_edge e = adjlist[u][node[u]];
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
				while(int flow = send_flow(s,t,node))
				{
					ans += flow;
				}
			}
			return ans;
		}
		return -1;
	}
};
