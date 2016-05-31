#include "variable.hpp"

namespace qtreports
{
    namespace detail
    {

        Variable::Variable() {}

        Variable::~Variable() {}

		void Variable::setExpression(const QString & text)
		{
			m_expression = text;
		}

		const QString Variable::getExpression() const
		{
			return m_expression;
		}

        void    Variable::setClassName( const QString & name )
        {
            m_className = name;
        }

        const QString   Variable::getClassName() const
        {
            return m_className;
        }

		void Variable::setResetType(const QString & resetType)
		{
			m_resetType = resetType;
		}

		const QString Variable::getResetType()
		{
			return m_resetType;
		}

		void Variable::setResetGroup(const QString & resetGroup)
		{
			m_resetGroup = resetGroup;
		}

		const QString Variable::getResetGroup()
		{
			return m_resetGroup;
		}

		void Variable::setIncrementType(const QString & incrementType)
		{
			m_incrementType = incrementType;
		}

		const QString Variable::getIncrementType() const
		{
			return m_incrementType;
		}

		void Variable::setIncrementGroup(const QString & incrementGroup)
		{
			m_incrementGroup = incrementGroup;
		}

		const QString Variable::getIncrementGroup() const
		{
			return m_incrementGroup;
		}

		void Variable::setCalculation(const QVariant & calculation)
		{

		}

    }
}
