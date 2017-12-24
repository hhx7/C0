#include "syntax_analysis/syntax_analysis.h"
#include "simulator/simulator.h"
#include <queue>

void dfs(std::queue<std::shared_ptr<abstract_node<symbol::Token_name >>> &q) {
    while(!q.empty()){
        auto n=q.front(); q.pop();
        auto d=n->get_data();
        if(d==symbol::Token_name::nul)
            std::cout<<std::endl;
        else
            std::cout << d << " " << std::flush;
        auto  h=n->get_leftmost_child();
        while (h!= nullptr){
            q.push(h);
            h=h->get_right_brother();
        }

    }
}

void bfs(std::shared_ptr<abstract_node<symbol::Token_name >> h) {
    if(h!= nullptr){
        std::cout << h->get_data() << " " << std::flush;
        auto q=h->get_leftmost_child();
        while (q!= nullptr){
            bfs(q);
            q=q->get_right_brother();
        }
    }else{
        return;
    }
}

int main() {
    std::string filename="/home/pi/C++/C0/test";
    symbol_table st;
    std::vector<instruction> codes;
    code_generator cg(st,codes);
    syntax_analysis syntax_analysis1(filename,cg,st);
    syntax_analysis1.run();
    auto head=syntax_analysis1.root_->get_leftmost_child();
    std::queue<decltype(head)> q;
    q.push(head);
    bfs(head);
    std::cout<<std::endl;
    st.print();
    cg.print();
    simulator simulator1(codes);
    simulator1.run();
    return 0;
}
