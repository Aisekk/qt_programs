#include <iostream>
using namespace std;
//Раздел 8.1, Глава 8. Слияние и сортировка слиянием
//двухпутевое слияние
//(не обменное, требуется дополнительный объем памяти - массив c[N+M])
//неадаптивное, неустойчивое!
//O ~ N+M, если на каждую операцию поиска наименьшего элемента уходит одно и то же время
template <class Item>
void mergeAB(Item c[], Item a[], int N, Item b[], int M)
{
    for(int i = 0, j = 0, k = 0; k < N+M; k++)
    {
        if(i == N) { c[k] = b[j++]; continue; }
        if(j == M) { c[k] = a[i++]; continue; }
        c[k] = (a[i] < b[j]) ? a[i++] : b[j++];
    }
}
int main()
{
    int i, N = 10, M = 6, sw = 1;
    int a[N], b[M], c[N+M];
    //ordered arrays
    if(sw){ for(i = 0; i < N; i++) a[i] = 2*i; for(i = 0; i < M; i++) b[i] = 2*i+1; }
    else { N = 0; while(cin >> a[N]) N++;}
    cout << "Ordered array A: ";
    for(i = 0; i < N; i++) cout << a[i] << " ";
    cout << endl;
    cout << "Ordered array B: ";
    for(i = 0; i < M; i++) cout << b[i] << " ";
    cout << endl;
    //sorted array after merging:
    cout << "Two-way merging of A and B: ";
    mergeAB(c, a, N, b, M);
    for(i = 0; i < N+M; i++) cout << c[i] << " ";
    cout << endl;
    //---------------------------------------------------------------------------------------------
    system("pause");
    return 0;
}
