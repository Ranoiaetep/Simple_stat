#include "Simple_stat.h"

#include <iostream>


int main(int argc, char *argv[])
{
    
    Simple_stat<int> stats;
    stats.append(5);
    stats.append(3);
    stats.append(5);
    stats.append(10);
    stats.append(8);
    stats.append(12);
    stats.append(10);
    stats.append(4);
    stats.append(4);
    stats.append(4);
    stats.append(3);
    stats.append(10);
    stats.append(10);



    std::cout<<"\nMax: "<<stats.get_max();
    std::cout<<"\nMin: "<<stats.get_min();
    std::cout<<"\nMean: "<<stats.get_mean();
    std::cout<<"\nMode: "<<stats.get_mode();
    
    std::cout<<"\n";
    stats.print();
    std::cout<<"\n";

    stats.removen(3, 2);
    stats.removen(10, 4);
    stats.print();
    std::cout<<"\n";

    stats.search(5);
    stats.search(7);
    std::cout<<"\n";

    for (int i=0; i<stats.size(); i++) {
        std::cout<<stats[i]<<"\n";
    }
    
    std::cout<<"\nMax: "<<stats.get_max();
    std::cout<<"\nMin: "<<stats.get_min();
    std::cout<<"\nMean: "<<stats.get_mean();
    std::cout<<"\nMode: "<<stats.get_mode();
    
}
