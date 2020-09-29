#pragma once
#include <string>
#include "MazeState.hpp"
#include<cstdint>

namespace statesPair {
    class StatesPair {
        private:
        state::MazeState m_curState;
        state::MazeState m_prevState;

        public:
        /**
         * @brief Construct a new States Pair object
         * 
         * @param cur is a state to define as the current state of the pair.
         * @param prev is a state to define as the prev state of the pair.
         */
        StatesPair(const state::MazeState& cur, const state::MazeState& prev);

        /**
         * @brief Get the Prev object
         * 
         * @return state::MazeState is the previous state of the pair.
         */
        state::MazeState getPrev() const;

        /**
         * @brief Get the Cur object
         * 
         * @return state::MazeState is the current state of the pair
         */
        state::MazeState getCur() const;

        /**
         * @brief set the pair.
         * 
         * @param other is other pair to state our pair fields according to.
         */
        void set(const statesPair::StatesPair& other);

        /**
         * @brief Get the Step From Prev To Cur object.
         * 
         * @return std::string is a string represent the step, can be ("Right, Left, Up, Down")
         */
        std::string getStepFromPrevToCur() const;

        /**
         * @brief Destroy the States Pair object
         * 
         */
        ~StatesPair();

        bool operator==(const statesPair::StatesPair& pair);
        bool operator!=(const statesPair::StatesPair& pair);
        bool operator<(const statesPair::StatesPair& pair);
        bool operator>(const statesPair::StatesPair& pair);
        bool operator<=(const statesPair::StatesPair& pair);
        bool operator>=(const statesPair::StatesPair& pair);


        struct pairComparator {
            public :
            bool operator() (const statesPair::StatesPair& pair1, const statesPair::StatesPair& pair2);
        };
    };
}