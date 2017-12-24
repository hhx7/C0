#include "syntax_analysis/syntax_analysis.h"
#include "simulator/simulator.h"
#include <queue>

void bfs(std::queue<std::shared_ptr<abstract_node<symbol::Token_name >>> &q) {
    std::cout << std::endl << "----------------------------Start Printing Abstract Syntax Tree-------------------"
              << std::endl;
    std::queue<std::shared_ptr<abstract_node<symbol::Token_name >>> level_temp;
    while(!q.empty()){
        auto n=q.front(); q.pop();
        auto d=n->get_data();

        std::cout << d << " " << std::flush;
        auto  h=n->get_leftmost_child();
        while (h!= nullptr){
            level_temp.push(h);
            h=h->get_right_brother();
        }
        if (q.empty()) {
            std::cout << std::endl;
            q = level_temp;
            while (!level_temp.empty()) {
                level_temp.pop();
            }
        }
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
    bfs(q);
    std::cout<<std::endl;
    st.print();
    cg.print();
    simulator simulator1(codes);
    simulator1.run();
    return 0;
}
