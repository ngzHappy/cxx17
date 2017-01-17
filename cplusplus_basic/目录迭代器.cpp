#include <list>
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include <filesystem>

namespace xxx {

namespace _pns_fs=std::experimental::filesystem;
template<typename _T_>using _t_list=std::list<_T_>;
template<typename _T_>using _t_vector=std::vector<_T_>;
using _t_size=std::size_t;
using _t_string=std::string;

class CallBack {
protected:
    using path=_pns_fs::path;
    using size_type=_t_size;
public:
    virtual ~CallBack()=default;
    virtual void seek_file(
        const path &/*rootdir*/,
        const path &/*rpath*/,
        const path &/*filename*/,
        size_type /**/) {
    }
};

class Node {
public:
    Node * parent=nullptr;
    _t_size deepth=0;
    _pns_fs::path dirname;
};

class State {
public:
    _t_vector<Node*> tmp;
    Node* rootNode=nullptr;
    CallBack * callBack=nullptr;
    _t_list<Node> all_dir_nodes;
    _t_list<Node>::iterator current_pos;
};

inline _pns_fs::path part_name(State * state,Node * node) {

    if (node->deepth<2) {
        return{};
    }

    if (node->deepth<3) {
        return node->dirname;
    }

    if (state->tmp.size()<node->deepth) {
        state->tmp.resize(8+node->deepth);
    }

    {
        auto varPos=state->tmp.rbegin();
        for (Node * varNode=node; varNode; varNode=varNode->parent) {
            *varPos=varNode;
            ++varPos;
        }
    }

    auto varPosEnd=state->tmp.end();
    auto varPos=varPosEnd-(node->deepth-1);
    _pns_fs::path varAns=(*varPos)->dirname;
    for (++varPos; varPos!=varPosEnd; ++varPos) {
        varAns/=(*varPos)->dirname;
    }
    return std::move(varAns);

}

inline _pns_fs::path full_name(State * state,Node * node) {

    if (node->deepth<2) {
        return node->dirname;
    }

    if (state->tmp.size()<node->deepth) {
        state->tmp.resize(8+node->deepth);
    }

    {
        auto varPos=state->tmp.rbegin();
        for (Node * varNode=node; varNode; varNode=varNode->parent) {
            *varPos=varNode;
            ++varPos;
        }
    }

    auto varPosEnd=state->tmp.end();
    auto varPos=varPosEnd-(node->deepth);
    _pns_fs::path varAns=(*varPos)->dirname;
    for (++varPos; varPos!=varPosEnd; ++varPos) {
        varAns/=(*varPos)->dirname;
    }
    return std::move(varAns);

}

template<typename ... _FileNames_>
inline void seek_dir(State * state,_FileNames_&&...arg) {
    _pns_fs::directory_iterator varEnd;
    _pns_fs::directory_iterator varP(std::forward<_FileNames_>(arg)...);

    const auto varPartName=part_name(state,&(*state->current_pos));
    const auto varDeepth=state->current_pos->deepth-1;

    for (; varEnd!=varP; ++varP) {
        auto && varStatus=varP->status();
        if (_pns_fs::is_directory(varStatus)) {
            state->all_dir_nodes.emplace_back();
            auto & varNode=*state->all_dir_nodes.rbegin();
            varNode.parent=&(*state->current_pos);
            varNode.deepth=varNode.parent->deepth+1;
            varNode.dirname=varP->path().filename();
        }
        else if (_pns_fs::is_regular_file(varStatus)) {

            state->callBack->seek_file(
                state->rootNode->dirname,
                varPartName,
                varP->path().filename(),
                varDeepth);

        }

    }

}

inline void rseek_dir(_t_string dirName,CallBack * callBack) {
    if (callBack==nullptr) { return; }

    State state;
    state.callBack=callBack;
    state.all_dir_nodes.emplace_back();

    {
        auto & var=*state.all_dir_nodes.rbegin();
        var.dirname=dirName;
        var.deepth=1;
        state.current_pos=state.all_dir_nodes.begin();
        state.rootNode=&var;
    }

    for (; state.current_pos!=state.all_dir_nodes.end();
        ++state.current_pos) {
        seek_dir(&state,full_name(&state,&(*state.current_pos)));
    }

}

}/*namespace*/

int main() {

    class Xcallback :public xxx::CallBack {
    public:
        virtual void seek_file(
            const path & a,
            const path & b,
            const path & c,
            size_type d)override {
            path full=a/b/c;
            using namespace std::experimental::filesystem;
            std::cout<<d<<std::boolalpha<<exists(full)<<full<<std::endl;
        }
    };
    Xcallback test;

    xxx::rseek_dir("D:/x/m/bd3/baidu3",&test);
    system("pause");
}

