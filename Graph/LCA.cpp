class LCA {
public:
    void init ( const int n, const vector<int>& parent ) {
        size = n;

        log_size = 0;
        while ( (1 << log_size) < size ) ++log_size;

        doubling_parent.resize((log_size+1)*size);
        dist.resize(size);

        rep(i, size) {
            doubling_parent[0*size + i] = parent[i];
        }

        rep(i, size) dist[i] = -1;
        rep(i, size) {
            if ( dist[i] == -1 ) calc_dist(i);
        }

        rep(k, log_size-1) {
            rep(i, size) {
                if ( doubling_parent[k*size + i] < 0 ) {
                    doubling_parent[(k+1)*size + i] = doubling_parent[k*size + i];
                } else {
                    doubling_parent[(k+1)*size + i] = doubling_parent[k*size + doubling_parent[k*size + i]];
                }
            }
        }
    }

    int query ( int x, int y ) {
        if ( dist[x] < dist[y] ) swap(x, y);

        rep(k, log_size) {
            if ( ((dist[x] - dist[y]) >> k) & 1 ) {
                x = doubling_parent[k*size + x];
            }
        }

        if ( x == y ) return x;
        irep(k, log_size) {
            if ( doubling_parent[k*size + x] != doubling_parent[k*size + y] ) {
                x = doubling_parent[k*size + x];
                y = doubling_parent[k*size + y];
            }
        }

        return doubling_parent[0*size + x];
    }
private:
    int size;
    int log_size;
    vector<int> doubling_parent;
    vector<int> dist;

    int calc_dist ( int id ) {
        if ( id == -2 ) return 0;
        if ( dist[id] != -1 ) return dist[id]+1;

        dist[id] = calc_dist(doubling_parent[0*size + id]);
        return dist[id] + 1;
    }
};
