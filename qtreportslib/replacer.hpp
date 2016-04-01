#pragma once
#ifndef REPLACER_HPP
#define REPLACER_HPP
#include <QString>
#include "tags/report.hpp"

namespace qtreports
{
    namespace detail
    {

        /*! @~russian
        @brief �����, ���������� ��������� �� �������� ��������.

        �����, ���������� ��������� �� �������� �������� � �����,
        ����������� �� TextWidget
        */
        class Replacer {

        public:
            Replacer();
            ~Replacer();

            /*! @~russian
            ���������� ����� � �������������� ���������� ����������.
            @param[in] report ��������� �� �����
            @param[in] text �������� �����
            */
            static QString  replaceParameters( const ReportPtr & report, const QString & text );

            /*! @~russian
            ���������� ����� � �������������� ���������� ����� �� ��������� ������.
            @param[in] report ��������� �� �����
            @param[in] text �������� �����
            @param[in] i ������� ������
            */
            static QString  replaceField( const ReportPtr & report, const QString & text, int i );

        private:

        };

    }
}

#endif // REPLACER_HPP
