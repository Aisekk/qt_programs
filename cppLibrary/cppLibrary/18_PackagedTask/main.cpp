#include <iostream>
#include <future>
using namespace std;

double compute(int x, int y)
{ return (double)(x/y); }

int main()
{
    packaged_task<double(int,int)> task(compute);//создаем задачу
    std::future<double> f = task.get_future();//получаем ее фьючерс

    task(7,5);//запускаем задачу (обычно в отдельном потоке)
    cout << "result: " << f.get() << endl;
    return 0;
}
