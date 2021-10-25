#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "Solution.hpp"
#include "AlgoGenetic.hpp"

class Population{
    private:
        vector<Solution> solutions;
    public:    
        Population( vector<Solution> sols ) : solutions(sols){};

        /********************************************************************/
        /***************************** Iterator *****************************/
        /********************************************************************/
        struct Iterator { 
            using iterator_category = std::input_iterator_tag;
            using difference_type   = std::ptrdiff_t;
            using value_type        = Solution;
            using pointer           = Solution*;  // or also value_type*
            using reference         = Solution&;  // or also value_type&

        public:    
            Iterator(pointer ptr) : m_ptr(ptr) {};

            reference operator*() const { return *m_ptr; }
            pointer operator->() { return m_ptr; }
            
            // Prefix increment
            Iterator& operator++() { m_ptr++; return *this; }  

            // Postfix increment
            Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

            friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
            friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };
        private:
            pointer m_ptr;
        };

        Iterator begin(){ return Iterator(&solutions[0]); };
        Iterator end() { return Iterator(&solutions[solutions.size()]); };
        /********************************************************************/

        //getters
        int size() const{ return solutions.size(); };
        vector<Solution> get_solutions() const { return solutions;};

        //genetic algo
        /*
        void selection( Population& pop, Selection s );
        void selection_roulette( Population& pop );
        void selection_elite( Population& pop );
        */
};

// fonction externe
ostream& operator <<(ostream& stream, Population& pop);
#endif