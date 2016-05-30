#include "variable.hpp"

namespace qtreports
{
    namespace detail
    {

        Variable::Variable() {}

        Variable::~Variable() {}

        void    Variable::setClassName( const QString & name )
        {
            //int id = QMetaType::type( name.toStdString().c_str() );
            //QMetaType type( id );
            //return type.isValid();
            m_className = name;
        }

        const QString   Variable::getClassName() const
        {
            return m_className;
        }

        void Variable::setData( const QVector<QVariant> &data )
        {
            m_data = data;
        }

        QString Variable::getData( int row )
        {
            return m_data.value( row ).toString();
        }

        int Variable::getRowCount()
        {
            return m_data.size();
        }

    }
}
