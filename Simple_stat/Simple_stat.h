#ifndef Simple_stat_h
#define Simple_stat_h


#include <iostream>
#include "llist.h"

template <typename E> class Simple_stat {
private:
    double mode;
    double mean;
    double median;
    double SD;
    double min;
    double max;
    int sum = 0;
    int sq_sum = 0;
    int count = 0;
    int unique_count = 0;
    std::pair<int,int> highest_mode = std::make_pair(0, 0);
    LList<std::tuple <int,int,int>> data_list;
public:
    Simple_stat(){
        LList<std::tuple <int,int,int>> data_list;
    }

    std::pair<int,int> new_mode(std::tuple <int,int,int> data){
        if (std::get<1>(data)>highest_mode.second) {
            return std::make_pair(std::get<0>(data), std::get<1>(data));
        }
        return highest_mode;
    }
    
    void append(int data){
        data_list.moveToStart();
        sum += data;
        sq_sum += data*data;
        count++;

        for (int n=0;n<data_list.length(); n++) {
            if (data<std::get<0>(data_list.getValue())) {
                std::tuple <int,int,int> dataset;
                dataset = std::make_tuple(data,1,count);
                data_list.insert(dataset);
                data_list.moveToStart();
                unique_count++;
                highest_mode = new_mode(dataset);
                calc_data();
                return;
            }
            if (data==std::get<0>(data_list.getValue())){
                std::tuple <int,int,int> dataset;
                dataset = std::make_tuple(std::get<0>(data_list.getValue()),std::get<1>(data_list.getValue())+1,std::get<2>(data_list.getValue()));
                data_list.remove();
                data_list.insert(dataset);
                highest_mode = new_mode(dataset);
                calc_data();
                return;
            }
            data_list.next();
        }
        std::tuple <int,int,int> dataset;
        dataset = std::make_tuple(data,1,count);
        data_list.insert(dataset);
        highest_mode = new_mode(dataset);
        unique_count++;
        calc_data();
    }
    
    void removen (int data, int quantity){
        data_list.moveToStart();
        count-=quantity;
        for (int n=0;n<data_list.length(); n++) {
            if (data==std::get<0>(data_list.getValue())) {
                std::tuple <int,int,int> dataset;
                dataset = std::make_tuple(std::get<0>(data_list.getValue()),std::get<1>(data_list.getValue())-quantity,std::get<2>(data_list.getValue()));
                data_list.remove();
                if (std::get<1>(dataset)>0) {
                    data_list.insert(dataset);
                }
                else{
                    unique_count--;
                }
                sum-=data*quantity;
                if (data == mode) {
                    highest_mode = std::make_pair(0, 0);
                    data_list.moveToStart();
                    for (int n=0;n<data_list.length(); n++) {
                        highest_mode = new_mode(data_list.getValue());
                        data_list.next();
                    }
                }
                calc_data();
                return;
            }
            data_list.next();
        }
        std::cout<<"No selected data found";
    }
    
    int size(){
        return unique_count;
    }
    
    void calc_mean(){
        mean = sum/(double)count;
    }
    void calc_sd(){
        SD = sqrt(sq_sum/(double)count-mean*mean);
    }
    
    void calc_mode(){
        mode = highest_mode.first;
    }
    
    void calc_min(){
        data_list.moveToStart();
        min = std::get<0>(data_list.getValue());
    }
    
    void calc_max(){
        data_list.moveToPos(data_list.length()-1);
        max = std::get<0>(data_list.getValue());
    }
    
    void calc_data(){
        calc_min();
        calc_max();
        calc_mean();
        calc_sd();
        calc_mode();
    }
    
    int get_min(){
        return min;
    }
    
    int get_max(){
        return max;
    }
    
    double get_mean(){
        return mean;
    }
    
    double get_sd(){
        return SD;
    }
    
    int get_mode(){
        return mode;
    }
    
    int length_unique(){
        return unique_count;
    }
    
    int length_total(){
        return count;
    }
    
    double sqrt(double number){
        double temp=0;
        double result=number/2;
        while(result != temp){
            temp = result;
            result = (number/temp+temp)/2;
        }
        return result;
    }
    
    void print(){
        if (count==0) {
            std::cout<<"Data set is empty.\n";
            return;
        }
        data_list.moveToStart();
        if (data_list.length()==0) {
            std::cout<<"Data set is empty.\n";
            return;
        }
        for (int i=0; i<data_list.length(); i++) {
            std::cout<<std::get<1>(data_list.getValue())<<" copies of "<<std::get<0>(data_list.getValue())<<", first appeared at index "<<std::get<2>(data_list.getValue())-1<<"\n";
            data_list.next();
        }
    }
    
    void print_stats(){
        std::cout<<"\nTotal length: "<<length_total();
        std::cout<<"\nUnique length: "<<length_unique();
        std::cout<<"\nMax: "<<get_max();
        std::cout<<"\nMin: "<<get_min();
        std::cout<<"\nMean: "<<get_mean();
        std::cout<<"\nMode: "<<get_mode();
        std::cout<<"\nSD: "<<get_sd();
        if (count==0) {
            std::cout<<"\nData set is empty.";
        }
        std::cout<<"\n";
    }
    
    void search(int data){
        data_list.moveToStart();
        for (int i=0; i<data_list.length(); i++) {
            if (std::get<0>(data_list.getValue())==data) {
                std::cout<<data<<" is first found at index "<<std::get<2>(data_list.getValue())-1<<" with "<<std::get<1>(data_list.getValue())<<" copies in the dataset\n";
                return;
            }
            data_list.next();
        }
        std::cout<<data<<" is not found in the dataset\n";
    }
    
    int operator[](int index){
        data_list.moveToPos(index);
        return std::get<0>(data_list.getValue());
    }
    
    template<typename T>
    void feed(T datas){
        for (int data:datas) {
            append(data);
        }
    }
    
    void empty(){
        data_list.~LList();
        min = max = mean = mean = mode = SD = count = unique_count =0;
    }
    
};


#endif /* Simple_stat_h */
