#include "IntersectionRange.h"

rt::IntersectionRange rt::IntersectionRange::union_op(const rt::IntersectionRange &range2) const {
    return rt::IntersectionRange(MIN(m_range.first, range2.m_range.first), MAX(m_range.second, range2.m_range.second));
}

rt::IntersectionRange rt::IntersectionRange::subtract_op(const rt::IntersectionRange & range2) const {
    return rt::IntersectionRange(MIN(m_range.second, range2.m_range.second), MAX(m_range.second, range2.m_range.second));
}

rt::IntersectionRange rt::IntersectionRange::intersection_op(const rt::IntersectionRange &range2) const {
    return rt::IntersectionRange(MAX(m_range.first, range2.m_range.first), MIN(m_range.second, range2.m_range.second));
}

rt::IntersectionRange rt::IntersectionRange::operator+(const rt::IntersectionRange &range2) const {
    return this->union_op(range2);
}

rt::IntersectionRange rt::IntersectionRange::operator-(const rt::IntersectionRange &range2) const {
    return this->subtract_op(range2);
}

rt::IntersectionRange rt::IntersectionRange::operator&(const rt::IntersectionRange &range2) const {
    return this->intersection_op(range2);
}

rt::IntersectionRange::IntersectionRange(rt::IntersectionRange &intersectionRange) {
    m_range = intersectionRange.m_range;
}

rt::IntersectionRange::IntersectionRange(double in, double out) {
    m_range.first = in;
    m_range.second = out;
}

rt::IntersectionRange::IntersectionRange(std::pair<double, double> range) {
    m_range = range;
}

double rt::IntersectionRange::getIn() const {
    return m_range.first;
}

double rt::IntersectionRange::getOut() const {
    return m_range.second;
}

rt::IntersectionRange::IntersectionRange() = default;
rt::IntersectionRange::~IntersectionRange() = default;