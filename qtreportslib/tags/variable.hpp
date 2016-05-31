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
			Устанавливает <variableExpression>
			@param[in] text Значение <variableExpression>
			*/
			void                                setExpression(const QString & text);

			/*! @~russian
			Возвращает значение <groupExpression>
			*/
			const QString                       getExpression() const;
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
            Когда происходит сброс переменной
            @param[in] resetType значения сброса переменной
            */
			void			setResetType( const QString & resetType);

			/*! @~russian
			Возвращает атрибут ResetType.
			*/
			const QString   getResetType();

			/*! @~russian
			Если ResetType=Group, то на какой группе
			@param[in] resetGroup имя группы для сброса
			*/
			void			setResetGroup(const QString & resetGroup);

			/*! @~russian
			Возвращает атрибут ResetGroup.
			*/
			const QString   getResetGroup();

			/*! @~russian
			Когда происходит обновление переменной
			@param[in] incrementType значения обновления переменной
			*/
			void			setIncrementType( const QString & incrementType);

			/*! @~russian
			Возвращает атрибут IncrementType.
			*/
			const QString	getIncrementType() const;

			/*! @~russian
			Если RIncrementType=Group, то на какой группе
			@param[in] incrementGroup имя группы
			*/
			void			setIncrementGroup(const QString & incrementGroup);

			/*! @~russian
			Возвращает атрибут IncrementGroup.
			*/
			const QString	getIncrementGroup() const;

			/*! @~russian
			Устанавливает функции
			@param[in] calculation выражение
			*/
			void			setCalculation( const QVariant & calculation);
			
        private:
            QString                 m_className;
			QString					m_resetType;
			QString					m_resetGroup;
			QString					m_incrementType;
			QString					m_incrementGroup;
			QString					m_expression;
		 ///						m_calculation;
        };

        typedef QSharedPointer< Variable > VariablePtr;
    }
}

#endif // VARIABLE_HPP
