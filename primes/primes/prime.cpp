#include "prime.h"
static const int N = 10000;

void Eratosfen()
{
    QTime time; time.start();
    //std::time t;
    int i, a[N];
    for(i = 2; i < N; i++) a[i] = 1;
    for(i = 2; i < N; i++)
        if(a[i])
            for(int j = i; j*i < N; j++) a[i*j] = 0;
    cout << "Eratosfen: " << time.elapsed() << endl;
    //qDebug("Eratosfen: %d ms", time.elapsed());
    int count = 0;
    for(i = 2; i < N; ++i) if(a[i]) { //cout << " " << i;
        ++count; }
    cout << endl << "Eratosfen array size: " << count << endl << endl;
}
void Atkin()
{
    QTime time; time.start();
    int limit = N;
    int sqr_lim;
    bool is_prime[N+1];
    int x2, y2;
    int i, j;
    int n;

    // Инициализация решета
    sqr_lim = (int)sqrt((long double)limit);
    for (i = 0; i <= limit; i++) is_prime[i] = false;
    is_prime[2] = true;
    is_prime[3] = true;

    // Предположительно простые — это целые с нечётным числом
    // представлений в данных квадратных формах.
    // x2 и y2 — это квадраты i и j (оптимизация).
    x2 = 0;
    for (i = 1; i <= sqr_lim; i++) {
        x2 += 2 * i - 1;
        y2 = 0;
        for (j = 1; j <= sqr_lim; j++) {
            y2 += 2 * j - 1;

            n = 4 * x2 + y2;
            if ((n <= limit) && (n % 12 == 1 || n % 12 == 5))
                is_prime[n] = !is_prime[n];

            // n = 3 * x2 + y2;
            n -= x2; // Оптимизация
            if ((n <= limit) && (n % 12 == 7))
                is_prime[n] = !is_prime[n];

            // n = 3 * x2 - y2;
            n -= 2 * y2; // Оптимизация
            if ((i > j) && (n <= limit) && (n % 12 == 11))
                is_prime[n] = !is_prime[n];
        }
    }

    // Отсеиваем кратные квадратам простых чисел в интервале [5, sqrt(limit)].
    // (основной этап не может их отсеять)
    for (i = 5; i <= sqr_lim; i++) {
        if (is_prime[i]) {
            n = i * i;
            for (j = n; j <= limit; j += n) {
                is_prime[j] = false;
            }
        }
    }
    cout << "Atkin: " << time.elapsed() << endl;

    // Вывод списка простых чисел в консоль.
    int count = 0;
    //printf(" 2 3 5");
    for (i = 6; i <= limit; i++) {  // добавлена проверка делимости на 3 и 5. В оригинальной версии алгоритма потребности в ней нет.
        if ((is_prime[i]) && (i % 3 != 0) && (i % 5 !=  0)){
           //printf(" %d", i);
           ++count; }
    }
    cout << endl << "Atkin array size: " << count+3 << endl << endl;
}

void Loop()
{
    QTime time; time.start();
    int i, a[N];
    for(i = 2; i < N; i++) a[i] = 1;
    for(i = 4; i < N; i+=2) a[i] = 0;

    int sqrN = (int)sqrt((long double)N);
    int e[sqrN+1];
    for(i = 2; i < sqrN+1; ++i)
        if(e[i]) for(int j = i; j*i < sqrN; j++) e[i*j] = 0;

    for(int i = 3; i < sqrN+1; ++i)
        if(e[i]) for(int j = i*i; j < N; j+= (i+i)) a[j] = 0;

//    for(i = 9; i < N; i+=6) a[i] = 0;
//    for(i = 25; i < N; i+=10) a[i] = 0;
//    for(i = 49; i < N; i+=14) a[i] = 0;
//    for(i = 121; i < N; i+=22) a[i] = 0;
//    for(i = 169; i < N; i+=26) a[i] = 0;
//    for(i = 17*17; i < N; i+=17*2) a[i] = 0;
//    for(i = 19*19; i < N; i+=19*2) a[i] = 0;
//    for(i = 23*23; i < N; i+=23*2) a[i] = 0;
//    for(i = 29*29; i < N; i+=29*2) a[i] = 0;
//    for(i = 31*31; i < N; i+=31*2) a[i] = 0;

    cout << "Loop: " << time.elapsed() << endl;
    int count = 0;
    for(i = 2; i < N; ++i) if(a[i]) { //cout << " " << i;
        ++count; }
    cout << endl << "Loop array size: " << count << endl << endl;
}
