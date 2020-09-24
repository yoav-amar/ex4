#include "StatesPair.hpp"
#include <vector>
namespace pairAndPrice {
    class PairAndPrice {
        private:
        double m_price;
        statesPair::StatesPair m_pair;

        public :
        PairAndPrice(const statesPair::StatesPair& pair, const double& price);
        double getPrice() const;
        statesPair::StatesPair getPair();
    };
}