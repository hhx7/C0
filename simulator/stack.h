//
// Created by pi on 17-12-11.
//

#ifndef C0_STACK_H
#define C0_STACK_H

#include <array>
inline constexpr int MAX_SIZE=10000;


template <typename T>
class stack{
public:
    stack():top_pointer_(0){}

    void push(T data){
        if( top_pointer_<MAX_SIZE)
            array_[top_pointer_++]=data;
        else{
            throw "no available space";
        }
    }
    T top()const {
        if(top_pointer_>=0)
            return array_.at(top_pointer_-1);
        else
            throw "empty";
    }
    void pop(){
        if(top_pointer_>=0){
            --top_pointer_;
        }
    }
    typename std::array<T,MAX_SIZE>::size_type get_top_pointer()const{

        return top_pointer_-1;
    };

    T& operator[](int index){

        return array_.at(index);
    }

    T operator[](int index)const{

        return array_.at(index);
    }

    bool alloc_space(typename std::array<T,MAX_SIZE>::size_type n){
        auto new_pos=top_pointer_+n;
        if(new_pos<MAX_SIZE){
            //available_space_pointer_=new_pos;
            top_pointer_=new_pos;
            return true;
        }
        return false;
    }

    bool jump_to(unsigned pos){
        if(pos >=0 && pos <MAX_SIZE){
            top_pointer_=pos+1;
            return true;
        }
        return false;
    }
    void reset(){
        top_pointer_=0;
    }

private:
    std::array<T,MAX_SIZE> array_;
    int top_pointer_;
};
#endif //C0_STACK_H
