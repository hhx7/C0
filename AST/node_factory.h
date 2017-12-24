//
// Created by pi on 17-12-12.
//

#ifndef C0_NODE_FACTORY_H
#define C0_NODE_FACTORY_H

#include "abstract_node.h"
#include <memory>

struct node_factory {
    template<typename DataType>
    static std::shared_ptr<abstract_node<DataType>> make_node(DataType n) {
        return std::make_shared<abstract_node<DataType>>(n);
    }

    template<typename DataType, typename... Args>
    static std::shared_ptr<abstract_node<DataType>> make_family(DataType op, Args &&... children) {

        auto parent = make_node(op);
        parent->adopt_children((children + ...));
        return parent;
    }

};

#endif //C0_NODE_FACTORY_H
