#include"code.h"
int solution(int n, int num[], int f[])
{
    int ans=0;
    for (int i = 1; i <= n; i++)
    {
        if (num[i] > f[i - 1] + num[i])f[i] = num[i];
        else f[i] = f[i - 1] + num[i];
        if (i == 1)ans = f[1];
        if (f[i] >= ans)ans=f[i];
    }
    if (ans < 0)ans = 0;
    return ans;
}
int main()
{
    int f[100];
    memset(f, 0, sizeof f);
    int num2[6] = { 0,-1,-2 };
    std::cout << solution(2, num2, f);
    return 0;
}
