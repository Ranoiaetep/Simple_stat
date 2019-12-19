//
//  Simple_stat.h
//  Simple_stat
//
//  Created by Peter Cong on 11/4/19.
//  Copyright © 2019 Tianpeng Cong. All rights reserved.
//

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
        count++;

        for (int n=0;n<data_list.length(); n++) {
            if (data<std::get<0>(data_list.getValue())) {
                std::tuple <int,int,int> dataset;
                dataset = std::make_tuple(data,1,count);
                data_list.insert(dataset);
                data_list.moveToStart();
                unique_count++;
                highest_mode = new_mode(dataset);
                return;
            }
            if (data==std::get<0>(data_list.getValue())){
                std::tuple <int,int,int> dataset;
                dataset = std::make_tuple(std::get<0>(data_list.getValue()),std::get<1>(data_list.getValue())+1,std::get<2>(data_list.getValue()));
                data_list.remove();
                data_list.insert(dataset);
                highest_mode = new_mode(dataset);
                return;
            }
            data_list.next();
        }
        std::tuple <int,int,int> dataset;
        dataset = std::make_tuple(data,1,count);
        data_list.insert(dataset);
        highest_mode = new_mode(dataset);
        unique_count++;
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
                /*
                if (std::get<0>(dataset)==highest_mode.first) {
                    data_list.moveToStart();
                    int high = 0;
                    for (int i=0; i<data_list.length(); i++) {
                        int a = std::get<1>(data_list.getValue());
                        if (high<a) {
                            high=a;
                            std::cout<<std::get<0>(data_list.getValue())<<"hi\n";
                        }
                        data_list.next();
                    }
                    int index = 0;
                    for (int i=0; i<data_list.length(); i++) {
                        if (std::get<0>(data_list.getValue())==high) {
                            index = i;
                        }
                    }
                    std::cout<<index;
                    data_list.moveToPos(index);
                    new_mode(data_list.getValue());
                }
                 */
                return;
            }
            data_list.next();
        }
        std::cout<<"No selected data found";
    }
    
    int size(){
        return unique_count;
    }
    
    int get_min(){
        data_list.moveToStart();
        return std::get<0>(data_list.getValue());
    }
    
    int get_max(){
        data_list.moveToPos(data_list.length()-1);
        return std::get<0>(data_list.getValue());
    }
    
    double get_mean(){
        return sum/(double)count;
    }
    
    int get_mode(){
        return highest_mode.first;
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
        data_list.moveToStart();
        for (int i=0; i<data_list.length(); i++) {
            std::cout<<std::get<1>(data_list.getValue())<<" copies of "<<std::get<0>(data_list.getValue())<<", first appeared at index "<<std::get<2>(data_list.getValue())-1<<"\n";
            data_list.next();
        }
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

};


#endif /* Simple_stat_h */
