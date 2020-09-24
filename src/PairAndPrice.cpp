#pragma once

#include "PairAndPrice.hpp"
#include "StatesPair.hpp"
#include <memory>

pairAndPrice::PairAndPrice::PairAndPrice(const statesPair::StatesPair& pair, const double& price) : m_pair(pair.getPrev(), m_pair.getCur()) {
    m_price = price;
}

double pairAndPrice::PairAndPrice::getPrice() const {
    return m_price;
}

statesPair::StatesPair pairAndPrice::PairAndPrice::getPair() {
    auto pair = std::make_unique<statesPair::StatesPair>(m_pair.getPrev(), m_pair.getCur());
    return *pair;
}
