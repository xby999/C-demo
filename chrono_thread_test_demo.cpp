/*
*该demo的用途：我用于练手的。
*以后可以直接搬过去用来计算线程的运行效率
*/

#include<iostream>
#include<thread>

using namespace std;

template <class T>      //模板类泛型
void measure(T&& func){          //用于计算传入的函数指针func运行的时间
    using namespace std::chrono;
    auto start = system_clock::now();     //chrono库中的方法，该库里的方法大多于时间有关
    func();
    duration<double> diff = system_clock::now()-start;
    cout<<"elapsed:"<< diff.count()<<endl;  //输出运行时间
}

void count_func(){          //随便写的测试函数，单纯用来计时的
    long long s = 0;
    for(int i=0;i<100000000;i++){
        s += i;
    }
    cout<< s <<endl;
}

int main(){
    // thread th_0 = thread(mythread_func);
    // th_0.join();
    measure(count_func);
    return 0;
}