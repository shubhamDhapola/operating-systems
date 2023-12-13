#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int minVehicles( vector<int> &weight, int limit)
{
    int n = weight.size();
    vector<bool> visited(n, false);
    sort(weight.begin(), weight.end());

    int vehicles = 0;

    for (int i = n - 1; i >= 0; --i)
    {
        if (!visited[i])
        {
            int remWeight = limit - weight[i];
            visited[i] = true;
            ++vehicles;

            for (int j = 0; j < i; ++j)
            {
                if (!visited[j] && weight[j] <= remWeight)
                {
                    visited[j] = true;
                    break; 
                }
            }
        }
    }

    return vehicles;
}

int main()
{

    vector<int> weight = {1, 2, 3, 4, 5};
    int limit = 6;

    int result = minVehicles(weight, limit);

    cout << result;

    return 0;
}
