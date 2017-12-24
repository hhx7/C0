//
// Created by pi on 17-12-15.
//

#ifndef C0_LIST_NODE_H
#define C0_LIST_NODE_H

#include <memory>



template <typename DataType>
class abstract_node : public std::enable_shared_from_this<abstract_node<DataType>>,public virtual operation_code{


public:

    abstract_node()= default;
    abstract_node(Operation_code);
    abstract_node(DataType data);
    abstract_node(Operation_code ,DataType data);
    abstract_node(Operation_code ,DataType data,std::shared_ptr<abstract_node<DataType>> parent);
    abstract_node(Operation_code ,DataType data,std::shared_ptr<abstract_node<DataType>> parent,std::shared_ptr<abstract_node<DataType>> leftmost_brother);
    abstract_node(Operation_code ,DataType data,std::shared_ptr<abstract_node<DataType>> parent,std::shared_ptr<abstract_node<DataType>> leftmost_brother,std::shared_ptr<abstract_node<DataType>> right_brother);


    std::shared_ptr<abstract_node<DataType>> make_siblings(std::shared_ptr<abstract_node<DataType>>  n);
    std::shared_ptr<abstract_node<DataType>> adopt_children(std::shared_ptr<abstract_node<DataType>> n);

    void set_data(DataType data);
    void set_parent(std::shared_ptr<abstract_node<DataType>> parent);
    void set_leftmost_brother(std::shared_ptr<abstract_node<DataType>> leftmost_brother);
    void set_right_brother(std::shared_ptr<abstract_node<DataType>> right_brother);
    void set_leftmost_child(std::shared_ptr<abstract_node<DataType>> leftmost_child);

    DataType get_data()const;
    std::shared_ptr<abstract_node<DataType>> get_parent()const;
    std::shared_ptr<abstract_node<DataType>> get_leftmost_brother()const;
    std::shared_ptr<abstract_node<DataType>> get_right_brother()const;
    std::shared_ptr<abstract_node<DataType>> get_leftmost_child()const;


private:
    Operation_code type_;
public:
    void setType(operation_code::Operation_code type_);

private:
    DataType data_;
public:
    Operation_code getType() const;

private:
    std::shared_ptr<abstract_node<DataType>> parent_;
    std::shared_ptr<abstract_node<DataType>> leftmost_child_;
    std::shared_ptr<abstract_node<DataType>> leftmost_brother_;
    std::shared_ptr<abstract_node<DataType>> right_brother_;

};



template <typename DataType>
inline abstract_node<DataType>::abstract_node(Operation_code type,DataType data,std::shared_ptr<abstract_node<DataType>> parent)
        :type_(type),data_(data),parent_(parent){}


template <typename DataType>
inline abstract_node<DataType>::abstract_node(Operation_code type,DataType data,std::shared_ptr<abstract_node<DataType>> parent,std::shared_ptr<abstract_node<DataType>> leftmost_brother)
        : type_(type),data_(data),parent_(parent),leftmost_brother_(leftmost_brother){}

template <typename DataType>
inline abstract_node<DataType>::abstract_node(Operation_code type,DataType data,std::shared_ptr<abstract_node<DataType>> parent,std::shared_ptr<abstract_node<DataType>> leftmost_brother,std::shared_ptr<abstract_node<DataType>> right_brother)
        :type_(type),data_(data),parent_(parent),leftmost_brother_(leftmost_brother),right_brother_(right_brother){}

template <typename DataType>
inline void abstract_node<DataType>::set_parent(std::shared_ptr<abstract_node<DataType>> parent){
    parent_=parent;
}

template <typename DataType>
inline void abstract_node<DataType>::set_leftmost_brother(std::shared_ptr<abstract_node<DataType>> leftmost_brother){
    leftmost_brother_=leftmost_brother;
}

template <typename DataType>
inline void abstract_node<DataType>::set_right_brother(std::shared_ptr<abstract_node<DataType>> right_brother){
    right_brother_=right_brother;
}

template<typename DataType>
inline auto abstract_node<DataType>::get_parent() const ->std::shared_ptr<abstract_node<DataType>>{
    return parent_;
}

template <typename DataType>
inline DataType abstract_node<DataType>::get_data() const{
    return data_;
}



template <typename DataType>
inline auto abstract_node<DataType>::get_leftmost_brother() const ->std::shared_ptr<abstract_node<DataType>>{
    return leftmost_brother_;
}

template <typename DataType>
inline auto abstract_node<DataType>::get_right_brother() const ->std::shared_ptr<abstract_node<DataType>>{
    return right_brother_;
}

template<typename DataType>
inline auto abstract_node<DataType>::make_siblings(std::shared_ptr<abstract_node<DataType>> y) ->std::shared_ptr<abstract_node<DataType>>{
    auto xsibs=this->shared_from_this();
    while(xsibs->right_brother_!= nullptr){
        xsibs=xsibs->right_brother_;
    }
    if(y == nullptr)
        return xsibs;
    if(y->leftmost_brother_== nullptr){
        y->leftmost_brother_=y;
    }
    if(xsibs->leftmost_brother_== nullptr){
        xsibs->leftmost_brother_=xsibs;
    }
    auto ysibs=(y->leftmost_brother_);
    xsibs->right_brother_=ysibs;
    ysibs->parent_=xsibs->parent_;
    ysibs->leftmost_brother_=xsibs->leftmost_brother_;
    while(ysibs->right_brother_!= nullptr){
        ysibs=ysibs->right_brother_;
        ysibs->leftmost_brother_=xsibs->leftmost_brother_;
        ysibs->parent_=xsibs->parent_;
    }
    return ysibs;
}

template<typename DataType>
inline auto abstract_node<DataType>::adopt_children(std::shared_ptr<abstract_node<DataType>> y)->std::shared_ptr<abstract_node<DataType>> {

    auto self=this->shared_from_this();
    if(y== nullptr)
        return self;
    if(y->leftmost_brother_== nullptr){
        y->leftmost_brother_=y;
    }
    if(self->leftmost_child_!= nullptr){
        self->leftmost_child_->make_siblings(y);
    }else{
        auto ysibs=y->leftmost_brother_;
        self->leftmost_child_=ysibs;
        while (ysibs!= nullptr){
            ysibs->parent_=self;
            ysibs=ysibs->right_brother_;
        }
    }
    return self;
}

template<typename DataType>
inline void abstract_node<DataType>::set_leftmost_child(std::shared_ptr<abstract_node<DataType>> leftmost_child) {
    leftmost_child_=leftmost_child;

}

template<typename DataType>
inline auto abstract_node<DataType>::get_leftmost_child() const->std::shared_ptr<abstract_node<DataType>> {
    return leftmost_child_;
}



template<typename DataType>
inline void abstract_node<DataType>::set_data(DataType data) {
    data_=data;
}

template<typename DataType>
abstract_node<DataType>::abstract_node(Operation_code code,DataType data):type_(code),data_(data) {

}


template<typename DataType>
abstract_node<DataType>::abstract_node(Operation_code code):type_(code) {

}

template<typename DataType>
abstract_node<DataType>::abstract_node(DataType data):data_(data) {
    type_=Operation_code::NUL;
}

template<typename DataType>
void abstract_node<DataType>::setType(operation_code::Operation_code type_) {
    abstract_node::type_ = type_;
}

template<typename DataType>
operation_code::Operation_code abstract_node<DataType>::getType() const {
    return type_;
}

template<typename DataType>
inline auto operator+(std::shared_ptr<abstract_node<DataType>> l,std::shared_ptr<abstract_node<DataType>> r)->std::shared_ptr<abstract_node<DataType>>{

    return (l== nullptr)? r :l->make_siblings(r);
}




#endif //C0_LIST_NODE_H
