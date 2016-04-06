﻿#include <QTest>
#include <QSqlQuery>
#include <QSqlDatabase>
#include <parser.hpp>
#include <converters/convertertoqwidget.hpp>
#include "test_convertertoqwidget.hpp"

Test_ConverterToQWidget::Test_ConverterToQWidget( QObject * parent ) :
    QObject( parent ) {}

Test_ConverterToQWidget::~Test_ConverterToQWidget() {}

void    Test_ConverterToQWidget::convert() {
    QString input = QFINDTESTDATA( "full.qrxml" );
    QWARN( ( "Used input: " + input ).toStdString().c_str() );
    
    qtreports::detail::Parser parser;
    if( !parser.parse( input ) )
    {
        QFAIL( ( "Parsing error: " + parser.getLastError() ).toStdString().c_str() );
        return;
    }

    auto report = parser.getReport();

    qtreports::detail::ConverterToQWidget converterToWidget( report );
    QVERIFY2( converterToWidget.convert( qtreports::detail::ConverterToQWidget::WidgetType::Report ), converterToWidget.getLastError().toStdString().c_str() );
    QCOMPARE( converterToWidget.isReport(), true );
    QCOMPARE( converterToWidget.isLayout(), false );
    QCOMPARE( converterToWidget.getType(), qtreports::detail::ConverterToQWidget::WidgetType::Report );
    QVERIFY( converterToWidget.getQWidget() != qtreports::QWidgetPtr() );
    QVERIFY( converterToWidget.getPage( 0 ) != qtreports::QWidgetPtr() );
    QVERIFY( converterToWidget.getPages() != QVector< qtreports::QWidgetPtr >() );
    QCOMPARE( converterToWidget.getLastError(), QString() );

    qtreports::detail::ConverterToQWidget converterToLayout( report );
    QVERIFY2( converterToLayout.convert( qtreports::detail::ConverterToQWidget::WidgetType::Layout ), converterToLayout.getLastError().toStdString().c_str() );
    QCOMPARE( converterToLayout.isReport(), false );
    QCOMPARE( converterToLayout.isLayout(), true );
    QCOMPARE( converterToLayout.getType(), qtreports::detail::ConverterToQWidget::WidgetType::Layout );
    QVERIFY( converterToLayout.getQWidget() != qtreports::QWidgetPtr() );
    QVERIFY( converterToLayout.getPage( 0 ) != qtreports::QWidgetPtr() );
    QVERIFY( converterToLayout.getPages() != QVector< qtreports::QWidgetPtr >() );
    QCOMPARE( converterToLayout.getLastError(), QString() );
}

void    Test_ConverterToQWidget::isReport()
{
    auto report = qtreports::detail::ReportPtr();
    qtreports::detail::ConverterToQWidget converter( report );

    QCOMPARE( converter.isReport(), true );
}

void    Test_ConverterToQWidget::isLayout()
{
    auto report = qtreports::detail::ReportPtr();
    qtreports::detail::ConverterToQWidget converter( report );

    QCOMPARE( converter.isLayout(), false );
}

void    Test_ConverterToQWidget::getType()
{
    auto report = qtreports::detail::ReportPtr();
    qtreports::detail::ConverterToQWidget converter( report );

    QCOMPARE( converter.getType(), qtreports::detail::ConverterToQWidget::WidgetType::Report );
}

void    Test_ConverterToQWidget::getQWidget()
{
    auto report = qtreports::detail::ReportPtr();
    qtreports::detail::ConverterToQWidget converter( report );

    QCOMPARE( converter.getQWidget(), qtreports::QWidgetPtr() );
}

void    Test_ConverterToQWidget::getPage()
{
    auto report = qtreports::detail::ReportPtr();
    qtreports::detail::ConverterToQWidget converter( report );

    QCOMPARE( converter.getPage( 0 ), qtreports::QWidgetPtr() );

}

void    Test_ConverterToQWidget::getPages()
{
    auto report = qtreports::detail::ReportPtr();
    qtreports::detail::ConverterToQWidget converter( report );

    QCOMPARE( converter.getPages(), QVector< qtreports::QWidgetPtr >() );
}

void    Test_ConverterToQWidget::getLastError()
{
    auto report = qtreports::detail::ReportPtr();
    qtreports::detail::ConverterToQWidget converter( report );

    QCOMPARE( converter.getLastError(), QString() );

}
