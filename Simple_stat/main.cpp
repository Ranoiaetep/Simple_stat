#include "Simple_stat.h"

#include <iostream>
#include <vector>


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


    stats.print_stats();
    
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
    
    stats.print_stats();
    
    std::cout<<"\n\nAccessing unique elemetns through [] operator:\n";
    for (int i=0; i<stats.size(); i++) {
        std::cout<<stats[i]<<"\n";
    }
    
    
    std::cout<<"\n\nFeeding std::vector:";
    std::vector<int> v {3,3,5,5,8};
    stats.feed(v);
    stats.print_stats();
    
    stats.empty();
    stats.print_stats();    
}
