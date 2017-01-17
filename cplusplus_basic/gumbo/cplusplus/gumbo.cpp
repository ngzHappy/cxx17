#include "gumbo.hpp"

namespace gumbo {

namespace __private {
namespace  {

using _GumboNodes=std::list<GumboNode*,memory::Allocator<int>>;
void getAllJavaScript(
        const char*varBegin,
        const char*varEnd,
        string_list &varAns){

    class _Gumbo final{
        GumboOutput * _m_Parser;
    public:
        _Gumbo(const char * d,int s){
            _m_Parser=gumbo_parse_with_options(defaultOptions(),d,s);
        }
        ~_Gumbo(){
            gumbo_destroy_output(defaultOptions(),_m_Parser);
        }
        operator GumboOutput *(){return _m_Parser;}
        operator const GumboOutput *()const {return _m_Parser;}

        GumboOutput *operator->(){return _m_Parser;}
        const GumboOutput *operator->() const {return _m_Parser;}
    };

    _Gumbo varParser{varBegin,int(varEnd-varBegin)};
    _GumboNodes varNodes;

    if (nullptr==varParser->root) { return; }
    varNodes.push_front(varParser->root);

    while (varNodes.empty()==false) {

        GumboNode * node=varNodes.front();
        varNodes.pop_front();

        if(node->type==GumboNodeType::GUMBO_NODE_ELEMENT){
            auto & varElement=node->v.element;

            /*如果这是js node*/
            if(varElement.tag==GumboTag::GUMBO_TAG_SCRIPT){
                auto & varChildren=varElement.children;
                for(decltype(varChildren.length) i=0;i<varChildren.length;++i){
                    GumboNode* varNode=reinterpret_cast<GumboNode*>(varChildren.data[i]);
                    if(varNode->type==GumboNodeType::GUMBO_NODE_TEXT){
                        auto & varJS=varNode->v.text;
                        varAns.emplace_back(varJS.text);
                    }
                }
            }else{
                auto & varChildren=varElement.children;
                for(decltype(varChildren.length) i=0;i<varChildren.length;++i){
                    GumboNode* varNode=reinterpret_cast<GumboNode*>(varChildren.data[i]);
                    if (varNode==nullptr) { continue; }
                    varNodes.push_back(varNode);
                }
            }
        }


    }


}/*void getAllJavaScript(...)*/

}/*namespace*/
}/*namespace __private */

string_list getAllJavaScript(const char*varBegin,const char*varEnd){

    string_list varAns;

    if(varEnd>varBegin){
        __private::getAllJavaScript(varBegin,varEnd,varAns);
    }

    return std::move(varAns);

}

}/*namespace gumbo*/





















