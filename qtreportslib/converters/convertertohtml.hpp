#pragma once
#ifndef CONVERTERTOHTML_HPP
#define CONVERTERTOHTML_HPP
#include <QString>
#include "tags/report.hpp"

#include <QDebug>

namespace qtreports {
    namespace detail {

        class ConverterToHTML {

        public:
            ConverterToHTML( const ReportPtr & report );
            ~ConverterToHTML();

            bool    convert();
            bool    convert( const QString & path );

            const QString   getLastError() const;
            const QString   getHTML() const;

        private:
            ReportPtr   m_report;
            QString     m_lastError;
            QString     m_html;

            bool        createHTML();
            void        drawShapes(QSharedPointer< Band > band, QString &elementStr, int index);

            QString m_path;
        };

    }
}
#endif // CONVERTERTOHTML_HPP
