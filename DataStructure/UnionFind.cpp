struct UnionFind
{
	vi root;

	UnionFind ( int N ){
		root.resize(N);
		rep(i, N) root[i] = i;
	}

	int check_root ( int x )
	{
		if( root[x] == x ) return x;
		return root[x] = check_root(root[x]);
	}
	
	void unite ( int x, int y )
	{
		int root_x = check_root(x), root_y = check_root(y);

		if( root_x == root_y ) return;
		root[root_y] = root_x;
	}
	
	bool check ( int x, int y  )
	{
		int root_x = check_root(x), root_y = check_root(y);

		return root_x == root_y;
	}
};
