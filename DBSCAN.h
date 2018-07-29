#include <vector>
#include <set>
#include <queue>
#include <cfloat>
#include <map>
#include <assert.h> 
#include <algorithm>
using namespace std;


void DBSCAN_cy(int c, int n,
               int * X_core,
               int * neighbors_pts,
               int * num_neighbors,
               int * result) {
    /*
        Cluster the core points using density-based methods

        Parameters
        ----------
        c: Number of core points
        n: Size of original dataset
        X_core: (c, ) array of the indices of the core points
        neighbors: array of indices to each neighbor within eps_clustering
                   distance for all core points
        num_neighbors: (c, ) number of neighbors for each core point, to
                       be used for indexing into neighbors array
        result: (n, ) array of cluster results to be calculated
    */

    // these literally don't work?
    assert(X_core.size() == c);
    assert(num_neighbors.size() == c);
    assert(result.size() == n);

    queue<int> q = queue<int>();
    int neighbor, start_ind, end_ind, point, cnt = 0;

    for (int i = 0; i < c; i++) {
        q = queue<int>();
        if (result[X_core[i]] == -1) {
            q.push(i);

            while (!q.empty()) {
                point = q.front();
                q.pop();

                start_ind = 0;
                if (point != 0) {
                    start_ind = num_neighbors[point - 1];
                }
                end_ind = num_neighbors[point];

                for (int j = start_ind; j < end_ind; j++) {
                    neighbor = neighbors[j];
                    if (result[X_core[neighbor]] == -1) {
                        q.push(neighbor);
                        result[X_core[neighbor]] = cnt;
                    }
                }
            }

            cnt ++;
        }
    }
}
