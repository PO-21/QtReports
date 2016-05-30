#pragma once
#ifndef VARIABLE_HPP
#define VARIABLE_HPP
#include <QSharedPointer>

#include <QVariant>
#include <QString>
#include <QVector>

#include "object.hpp"

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief Класс, реализующий тэг <variable>

        Класс, реализующий тэг <variable>
        */
        class Variable : public Object {

        public:
            Variable();
            ~Variable();

            /*! @~russian
            Устанавливает атрибут className
            @param[in] name Название класса
            */
            void            setClassName( const QString & name );

            /*! @~russian
            Возвращает атрибут className.
            */
            const QString   getClassName() const;

            /*! @~russian
            Устанавливает содержимое <variable>
            @param[in] data Вектор, содержащие данные <variable>
            */
            void            setData( const QVector< QVariant > & data );

            /*! @~russian
            Возвращает содержимое <variable>
            @param[in] row Номер строки
            */
            QString         getData( int row );

            /*! @~russian
            Возвращает содержимое <variable>. Шаблонный вариант.
            @param[in] row Номер строки
            */
            template< typename T1 >
            const T1        getData( int row )
            {
                return m_data.value( row ).value< T1 >();
            }

            const QVariant getDataVar(int row)
            {
                return m_data[row];
            }

            void setDataVar(int row, const QVariant & value) {
                m_data[row] = value;
            }

            /*! @~russian
            Получить количество строк в <variable>
            */
            int             getRowCount();

        private:
            QString                 m_className;
            QVector< QVariant >     m_data;

        };

        typedef QSharedPointer< Variable > VariablePtr;
    }
}

#endif // FIELD_HPP
