class SegTree
{
	SegTree ( const int N, const int init_val = IINF )
	{
		auto p = calc_upper_pow2(N);
		pow2 = p.sc;

		n = 1 << pow2;
		v = vi((1 << (p.sc+1)), init_val);
	}

	void add ( int i, int x )
	{
		int idx = i+(1 << pow2);
		v[idx] = x;

		add_impl(idx/2);
	}

	int sum ( int l, int r )
	{
		return sum_impl(l, r, 1, 0, n);
	}

	void print_tree ()
	{
		int idx = 1;
		rep(i, pow2+1){
			rep(j, 1 << i){
				cout << v[idx] << " ";
				++idx;
			}
			cout << endl;
		}
	}

private:
	int pow2;
	int n;
	vi v;

	pii calc_upper_pow2 ( int x )
	{
		pii ret = mp(1, 0);
		rep(i, 31){
			if( x < ret.fs ){
				ret.sc = i;
				break;
			}
			ret.fs *= 2;
		}
		return ret;
	}

	void add_impl ( int i )
	{
		if( i == 0 ) return;

		v[i] = v[i*2] + v[i*2+1];
		add_impl( i/2 );
	}

	int sum_impl( int a, int b, int idx, int l, int r )
	{
		if( r <= a || b <= l ) return 0;
		if( a <= l && r <= b ) return v[idx];
		else{
			int yl = sum_impl(a, b, 2*idx, l, (l+r)/2);
			int yr = sum_impl(a, b, 2*idx+1, (l+r)/2, r);

			return yl+yr;
		}
	}
};
