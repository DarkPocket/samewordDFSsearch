#ifndef TIMING_FUNCTION_H
#define TIMING_FUNCTION_H


#include <time.h>

#include<malloc.h>

#include <iostream>
using namespace std;

class timing
{

        clock_t start ;
        clock_t finish;
        double duration;
};


class Timing_function
{

public:
        clock_t start ;
        clock_t finish;
        double duration;

       clock_t    Timing_start( ) ;

        clock_t Timing_finish(   );
        void Timing_init(      );
        void Timing_show (    );




        Timing_function();
        virtual ~Timing_function();

private:
};

#endif // TIMING_FUNCTION_H
