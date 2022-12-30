#include "Blocks.h"
#include "Creature.h"

#include <Windows.h>
#include <thread>
#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;

HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

void RunMember(Member* _memb, Block** _road, size_t szRoad, float* results);
int FromToR(int _f, int _t);

int main()
{
    srand(time(0));

    //---[Генерация Участников]---
    enum LIMITS_OF_POSSIBILITY
    {
        //В сантиметрах
        MAX_S = 15,
        MIN_S = 7,

        //В метрах
        MAX_J = 70,
        MIN_J = 30,
    };

    Member _membs[] =
    {
        {"Human", (unsigned)FromToR(MIN_S, MAX_S), (unsigned)FromToR(MIN_J, MAX_J)},
        {"Robot", (unsigned)FromToR(MIN_S, MAX_S), (unsigned)FromToR(MIN_J, MAX_J)},
        {"Cat", (unsigned)FromToR(MIN_S, MAX_S), (unsigned)FromToR(MIN_J, MAX_J)},
    };
    const size_t szMembs = sizeof(_membs) / sizeof(Member);

    for (Member& _m : _membs) 
    { 
        _m.SetCol(rand() % 16); 
        SetConsoleTextAttribute(handle, _m.GetCol());
        cout << _m.GetName() << " Ready!" << endl;
        Sleep(100);
    }

    cout << endl;

    //---[Генерация Трассы]---
    enum LIMITS_OF_BLOCK
    {
        //В сантиметрах
        MAX_W = 500,
        MIN_W = 200,

        //В метрах
        MAX_T = 50,
        MIN_T = 20,
    };

    const size_t szRoad = 10;
    Block* Road[szRoad];

    for (int i = 0; i < szRoad; ++i)
    {
        i % 2 ?
            Road[i] = new Wall(FromToR(MIN_W, MAX_W)) :
            Road[i] = new Track(FromToR(MIN_T, MAX_T));
    }

    //---[Симуляция Забега]---
    float Results[szMembs]{};
    
    thread* Runs[szMembs];
    for (int i = 0 ; i < szMembs; ++i)
    {
        Runs[i] = new thread(RunMember, &(_membs[i]), Road, szRoad, &(Results[i]));
    }

    for (int i = 0; i < szMembs; ++i)
    {
        Runs[i]->join();
    }

    //---[Результат Забега]---
    cout << endl << endl << "Results: " << endl;
    for (int i = 0; i < szMembs; ++i)
    {
        SetConsoleTextAttribute(handle, _membs[i].GetCol());
        cout << _membs[i].GetName() << ": " << Results[i] << endl;
    }
}


void RunMember(Member* _memb, Block** _road, size_t szRoad, float* results)
{
    float res = _road[0]->OvercomeBy(*_memb);
    Sleep(res * 1000);

    for (int i = 1; i < szRoad; ++i)
    {
        float y = _road[i]->OvercomeBy(*_memb);

        SetConsoleTextAttribute(handle, _memb->GetCol());
        cout << "A runner named " << _memb->GetName() << " ran obstacle " << i << " in " << y << " seconds." << endl;
        
        res += y;
        Sleep(y * 1000);
    }

    SetConsoleTextAttribute(handle, _memb->GetCol());
    cout << "A runner named " << _memb->GetName() << " ran to the end!" << endl;
    *results = res;
}

int FromToR(int _f, int _t)
{
    return _f + rand() % (_t - _f + 1);
}
