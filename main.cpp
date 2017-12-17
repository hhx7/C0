#include "syntax_analysis/syntax_analysis.h"
#include <queue>

void walk(std::queue<std::shared_ptr<abstract_node<symbol::Token_name >>>& q){
    while(!q.empty()){
        auto n=q.front(); q.pop();
        auto d=n->get_data();
        if(d==symbol::Token_name::nul)
            std::cout<<std::endl;
        else
            std::cout<<(int)d<<" "<<std::flush;
        auto  h=n->get_leftmost_child();
        while (h!= nullptr){
            q.push(h);
            h=h->get_right_brother();
        }

    }
}

void f1(std::shared_ptr<abstract_node<symbol::Token_name >> h){
    if(h!= nullptr){
        std::cout<<(int)h->get_data()<<" "<<std::flush;
        auto q=h->get_leftmost_child();
        while (q!= nullptr){
            f1(q);
            q=q->get_right_brother();
        }
    }else{
        return;
    }
}

int main() {
    std::string filename="/home/pi/C++/C0/lexer/test";
    symbol_table st;
    syntax_analysis syntax_analysis1(filename,st);
    syntax_analysis1.run();
    auto head=syntax_analysis1.root_->get_leftmost_child();
    std::queue<decltype(head)> q;
    q.push(head);
   f1(head);

    return 0;
}
