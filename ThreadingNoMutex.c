#include <iostream>
#include <thread>
#include <string>

using namespace std;

void work1 (string msg)
{
    cout << "work1 says: " << msg << "\n";
}

void work2(string msg)
{
    cout << "work2 says: " << msg << "\n";
}

int main(){
    thread w1(work1,"Hello");
    thread w2(work2,"World!");

    w1.join(); // Note, These dont work the right way round 100% of the time.
    w2.join();
}