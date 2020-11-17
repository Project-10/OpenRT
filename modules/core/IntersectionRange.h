#include <iostream>
#include "IPrim.h"


namespace rt
{
    class IntersectionRange
    {
    public:
        IntersectionRange();
        IntersectionRange(double, double);
        explicit IntersectionRange(std::pair<double, double> range);
        IntersectionRange(IntersectionRange &);
        ~IntersectionRange();

        [[nodiscard]] IntersectionRange union_op(const IntersectionRange &) const;
        [[nodiscard]] IntersectionRange subtract_op(const IntersectionRange &) const;
        [[nodiscard]] IntersectionRange intersection_op(const IntersectionRange &) const;

        IntersectionRange operator+(const IntersectionRange &) const;
        IntersectionRange operator-(const IntersectionRange &) const;
        IntersectionRange operator&(const IntersectionRange &) const;

        [[nodiscard]] double getIn() const;
        [[nodiscard]] double getOut() const;

    private:
        std::pair<double, double> m_range;
    };
}