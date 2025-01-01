//
// Created by apin on 20.12.2024.
//

#ifndef VINS_FOCUS_NODE_HPP
#define VINS_FOCUS_NODE_HPP


#include <iostream>


namespace vins {
namespace core {
namespace transport {

class Node {
    public:
        /*********Public fields*********/


        /*********Public methods*********/
        explicit Node(const std::string &name) : _name(name) {};

        virtual ~Node() = default;

        virtual void init() = 0;

        virtual void run() = 0;


    protected:
        /*********Protected fields*********/


        /*********Protected methods*********/


    private:
        /*********Private fields*********/
        std::string _name;


        /*********Private methods*********/

};

}; // namespace transport
}; // namespace core
}; // namespace vins


#endif //VINS_FOCUS_NODE_HPP
