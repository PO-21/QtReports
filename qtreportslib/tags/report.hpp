#pragma once
#ifndef REPORT_HPP
#define REPORT_HPP

#include <QString>
#include <QSize>
#include <QMap>
#include <QVector>
#include <QSharedPointer>
#include <QMargins>
#include <QPrinter>

#include "object.hpp"
#include "field.hpp"
#include "style.hpp"
#include "group.hpp"
#include "title.hpp"
#include "detail.hpp"

namespace qtreports {
    namespace detail {

        /*! @~russian
        @brief Класс, реализующий тэг <report>
        
        Класс, реализующий тэг <report>
        */
        class Report : public Object {
                 
        public:
            Report();
            ~Report();

            /*! @~russian
            Устанавливает <style> по умолчанию
            @param[in] style Указатель на <style>
            */
            void                                setDefaultStyle( const StylePtr & style );
            
            /*! @~russian
            Возвращает <style> по умолчанию
            */
            const StylePtr                      getDefaultStyle() const;
            
            /*! @~russian
            Добавляет <style> в <report> 
            @param[in] name Имя стиля
            @param[in] style Указатель на <style>
            */
            void                                addStyle( const QString & name, const StylePtr & style );
            
            /*! @~russian
            Возвращает указатель на <style> по имени
            @param[in] name Имя <style>
            */
            const StylePtr                      getStyle( const QString & name ) const;
            
            /*! @~russian
            Возвращает карту указателей на <style>
            */
            const QMap< QString, StylePtr >     getStyles() const;

            /*! @~russian
            Добавляет <group> в <report>
            @param[in] name Имя <group>
            @param[in] group Указатель на <group>
            */
            void                                addGroup( const QString & name, const GroupPtr & group );

            /*! @~russian
            Возвращает указатель на <group> по имени
            @param[in] name Имя <group>
            */
            const GroupPtr                      getGroup( const QString & name ) const;

            /*! @~russian
            Возвращает карту указателей на <group>
            */
            const QMap< QString, GroupPtr >     getGroups() const;

            /*! @~russian
            Устанавливает <queryString>
            @param[in] query Значение <queryString>
            */
            void                                setQuery( const QString & query );
            
            /*! @~russian
            Возвращает <queryString>
            */
            const QString                       getQuery() const;

            /*! @~russian
            Устанавливает <field>
            @param[in] name Имя <field>
            @param[in] field Указатель на обьект <field>
            */
            void                                setField( const QString & name, const FieldPtr & field );   
            
            /*! @~russian
            Возвращает <field>
            @param[in] name Имя <field>
            */
            const FieldPtr                      getField( const QString & name ) const;   
            
            /*! @~russian
            Возвращает карту <field>
            */
            const QMap< QString, FieldPtr >     getFields() const;
            
            /*! @~russian
            Устанавливает данные <field>
            @param[in] name Имя <field>
            @param[in] data Вектор данных <field>
            */
            void                                setFieldData( const QString & name, const QVector< QVariant > & data );

            /*! @~russian
            Устанавливает <title>
            @param[in] title Указатель на обьект <title>
            */
            void                                setTitle( const TitlePtr & title );
            
            /*! @~russian
            Возвращает указатель на обьект <title>
            */
            const TitlePtr                      getTitle() const;

            /*! @~russian
            Устанавливает <detail>
            @param[in] detail Указатель на обьект <detail>
            */
            void                                setDetail( const DetailPtr & detail );
            
            /*! @~russian
            Возвращает указатель на обьект <detail>
            */
            const DetailPtr                     getDetail() const;

            /*! @~russian
            Устанавливаются ссылки на обьекты
            @param[in] имя
            @param[in] значение
            */
            void                                setParameter( const QString & name, const QVariant & value );
            
            /*! @~russian
            Устанавливает QMap ссылок на обьекты
            @param[in] Ссылки на параметры
            */            
            void                                setParameters( const QMap< QString, QVariant > & parameters );
            
            /*! @~russian
            Возвращает имя параметра
            */            
            const QVariant                      getParameter( const QString & name ) const;
            
            /*! @~russian
            Возвращает карту параметров с названием и значением
            */            
            const QMap< QString, QVariant >     getParameters() const;
            
            /*! @~russian
            Возвращает количество строк
            */
            int     getRowCount() const;

            /*! @~russian
            Устанавливает ориентации отчета книжная/альбомная
            @param[in] ориентация
            */
            void                    setOrientation( QPrinter::Orientation orientation );
            
            /*! @~russian
            Возвращает ориентацию отчета(книжная/альбомная)
            */
            QPrinter::Orientation   getOrientation() const;

            /*! @~russian
            Устанавливает размер отчета
            @param[in] размер
            */
            void            setSize( const QSize & size );
            
            /*! @~russian
            Возвращает размер отчета
            */
            const QSize     getSize() const;

            /*! @~russian
            Устанавливает ширину отчета
            @param[in] значение ширины
            */
            void            setWidth( int width );
            
            /*! @~russian
            Возвращает ширину отчета
            */
            int             getWidth() const;

            /*! @~russian
            Устанавливает высоту отчета
            @param[in] значение высоты
            */
            void            setHeight( int height );
            
            /*! @~russian
            Возвращает высоту отчета
            */
            int             getHeight() const;
            
            /*! @~russian
            Устанавливает левый отступ
            @param[in] значение 
            */
            void    setLeftMargin( int left );
            
            /*! @~russian
            Возвращает левый отступ
            */
            int     getLeftMargin() const;
            
            /*! @~russian
            Устанавливает верхний отступ
            @param[in] значение
            */
            void    setTopMargin( int top );
            
            /*! @~russian
            Возвращает верхний отступ
            */
            int     getTopMargin() const;
            
            /*! @~russian
            Устанавливает правый отступ
            @param[in] значение
            */
            void    setRightMargin( int right );
            
            /*! @~russian
            Возвращает правый отступ
            */
            int     getRightMargin() const;
            
            /*! @~russian
            Устанавливает нижний отступ
            @param[in] значение
            */
            void    setBottomMargin( int bottom );
            
            /*! @~russian
            Возвращает нижний отступ
            */
            int     getBottomMargin() const;

            /*! @~russian
            Устанавливает отступы от краев
            @param[in] слева
            @param[in] сверху
            @param[in] справа
            @param[in] снизу
            */
            void            setMargins( int left, int top, int right, int bottom );
            
            /*! @~russian
            Устанавливает карту отступов
            @param[in] отступы
            */
            void            setMargins( const QMargins & margins );
            
            /*! @~russian
            Возвращает карту отступов
            */
            const QMargins  getMargins() const;

        private:
            QPrinter::Orientation	    m_orientation;
            QSize	                    m_size;
            QMargins                    m_margins;
            StylePtr                    m_defaultStyle;
            QMap< QString, StylePtr >   m_styles;
            QString                     m_query;
            QMap< QString, FieldPtr >   m_fields;
            QMap< QString, GroupPtr >   m_groups;
            TitlePtr                    m_title;
            DetailPtr                   m_detail;
            QMap< QString, QVariant >   m_parameters;

        };
        typedef QSharedPointer< Report > ReportPtr;

    }
}

#endif // REPORT_HPP
