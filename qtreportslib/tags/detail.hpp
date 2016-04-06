#pragma once
#ifndef DETAIL_HPP
#define DETAIL_HPP
#include <QSharedPointer>
#include "section.hpp"

namespace qtreports {
    namespace detail {


        /*! @~russian
        @brief Класс, реализующий тэг <Detail>
        Класс, реализующий тэг <Detail>
        */
        class Detail : public Section {

        public:
            Detail();
            ~Detail();

        private:

        };
        typedef QSharedPointer< Detail > DetailPtr;

    }
}

#endif // DETAIL_HPP
