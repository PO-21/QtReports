#pragma once
#ifndef TEXTFIELD_HPP
#define TEXTFIELD_HPP
#include <QString>
#include <QSharedPointer>
#include "textwidget.hpp"

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief �����, ����������� ��� TextField

        �����, ����������� ��� TextField
        */
        class TextField : public TextWidget {

        public:
            TextField();
            ~TextField();

            /*! @~russian
            ������������� ��� ������. ������ �������� ����� ��������������
            ��� ���������� �����������.
            @param[in] name ��� ������
            */
            void            setClassName( const QString & name );

            /*! @~russian
            ���������� ������� ��� ������.
            */
            const QString   getClassName() const;

        private:
            QString     m_className;

        };
        typedef QSharedPointer< TextField > TextFieldPtr;

    }
}

#endif // TEXTFIELD_HPP
