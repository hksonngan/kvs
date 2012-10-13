#pragma once
#include <kvs/Assert>
#include <kvs/Math>
#include <kvs/Value>


namespace kvs
{

class ValueRange
{
private:
    double m_lower;
    double m_upper;

public:
    ValueRange()
    {
        m_lower = kvs::Value<double>::Max();
        m_upper = kvs::Value<double>::Min();
    }

    ValueRange( double lower, double upper )
    {
        KVS_ASSERT( lower <= upper );
        m_lower = lower;
        m_upper = upper;
    }

    void extend( double x )
    {
        m_lower = kvs::Math::Min( m_lower, x );
        m_upper = kvs::Math::Max( m_upper, x );
    }

    void extend( const ValueRange& other )
    {
        m_lower = kvs::Math::Min( m_lower, other.m_lower );
        m_upper = kvs::Math::Max( m_upper, other.m_upper );
    }

    bool hasLength() const
    {
        return m_lower < m_upper;
    }

    double lower() const
    {
        return m_lower;
    }

    double upper() const
    {
        return m_upper;
    }
};

} // end of namespace kvs
