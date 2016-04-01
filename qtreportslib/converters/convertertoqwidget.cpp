#include <QFrame>
#include <QLabel>
#include "convertertoqwidget.hpp"

namespace qtreports
{
    namespace detail
    {

        ConverterToQWidget::ConverterToQWidget( const ReportPtr & report ) :
            m_report( report ),
            m_type( WidgetType::Report ),
            m_currentHeight( 0 )
        {}

        ConverterToQWidget::~ConverterToQWidget() {}

        bool    ConverterToQWidget::convert( WidgetType type )
        {
            m_type = type;
            return createQWidget( m_report );
        }

        bool    ConverterToQWidget::isReport() const
        {
            return m_type == WidgetType::Report;
        }

        bool    ConverterToQWidget::isLayout() const
        {
            return m_type == WidgetType::Layout;
        }

        ConverterToQWidget::WidgetType  ConverterToQWidget::getType() const
        {
            return m_type;
        }

        const QWidgetPtr    ConverterToQWidget::getQWidget() const
        {
            return m_qwidget;
        }

        const QWidgetPtr    ConverterToQWidget::getPage( int i ) const
        {
            return m_pages.value( i );
        }

        const QVector< QWidgetPtr >     ConverterToQWidget::getPages() const
        {
            return m_pages;
        }

        const QString       ConverterToQWidget::getLastError() const
        {
            return m_lastError;
        }

        QHBoxLayout * createLayout( QWidget * left, QWidget * center, QWidget * right )
        {
            auto layout = new QHBoxLayout();
            layout->setMargin( 0 );
            layout->setSpacing( 0 );

            layout->addWidget( left );
            layout->addWidget( center );
            layout->addWidget( right );

            return layout;
        }

        void    ConverterToQWidget::addVerticalBorder( QBoxLayout * parent, int height, int left, int right )
        {
            auto leftFrame = new QFrame();
            leftFrame->setFixedWidth( left );
            leftFrame->setFixedHeight( height );

            auto centerFrame = new QFrame();
            centerFrame->setFixedHeight( height );

            auto rightFrame = new QFrame();
            rightFrame->setFixedWidth( right );
            rightFrame->setFixedHeight( height );

            if( isLayout() )
            {
                QString style = "border: 1px solid gray; ";
                leftFrame->setStyleSheet( style + "border-width: 0px 1px 0px 0px; " );
                rightFrame->setStyleSheet( style + "border-width: 0px 0px 0px 1px; " );
            }

            auto layout = createLayout( leftFrame, centerFrame, rightFrame );
            parent->addLayout( layout );
        }

        void    ConverterToQWidget::addEmptySection( QBoxLayout * parent, int left, int right )
        {
            auto leftFrame = new QFrame();
            leftFrame->setFixedWidth( left );

            auto centerFrame = new QFrame();

            auto rightFrame = new QFrame();
            rightFrame->setFixedWidth( right );

            if( isLayout() )
            {
                QString style = "border: 1px solid gray; ";
                leftFrame->setStyleSheet( style + "border-width: 1px 1px 1px 0px; " );
                centerFrame->setObjectName( "frame" );
                centerFrame->setStyleSheet( "#frame{" + style + "border-width: 1px 0px 1px 0px; }" );
                rightFrame->setStyleSheet( style + "border-width: 1px 0px 1px 1px; " );
            }

            auto layout = createLayout( leftFrame, centerFrame, rightFrame );
            parent->addLayout( layout );
        }

        QFrame *    ConverterToQWidget::addSectionLayout( QBoxLayout * parent, int height, int left, int right )
        {
            auto leftFrame = new QFrame();
            leftFrame->setFixedHeight( height );
            leftFrame->setFixedWidth( left );

            auto centerFrame = new QFrame();
            centerFrame->setFixedHeight( height );



            auto rightFrame = new QFrame();
            rightFrame->setFixedHeight( height );
            rightFrame->setFixedWidth( right );

            if( isLayout() )
            {
                QString style = "border: 1px solid gray; ";
                leftFrame->setStyleSheet( style + "border-width: 1px 1px 0px 0px; " );
                centerFrame->setObjectName( "frame" );
                centerFrame->setStyleSheet( "#frame{" + style + "border-width: 1px 0px 0px 0px; }" );
                rightFrame->setStyleSheet( style + "border-width: 1px 0px 0px 1px; " );
            }

            auto layout = createLayout( leftFrame, centerFrame, rightFrame );
            parent->addLayout( layout );

            return centerFrame;
        }

        QWidget *   ConverterToQWidget::addPage()
        {
            m_pages.append( QWidgetPtr( new QWidget() ) );
            return m_pages.last().data();
        }

        bool    ConverterToQWidget::createQWidget( const ReportPtr & report )
        {
            if( report.isNull() )
            {
                m_lastError = "Report is empty";
                return false;
            }

            auto detail = report->getDetail();
            if( detail.isNull() )
            {
                m_lastError = "Report->Detail is empty";
                return false;
            }

            m_qwidget = QWidgetPtr( new QWidget() );
            m_qwidget->setStyleSheet( "background-color: white; " );//border: 1px solid gray; 
            //m_qwidget->setContentsMargins( m_report->getMargins() );

            auto layout = new QVBoxLayout( m_qwidget.data() );
            layout->setMargin( 0 );
            layout->setSpacing( 0 );
            addVerticalBorder( layout, report->getTopMargin(), report->getLeftMargin(), report->getRightMargin() );

            auto title = report->getTitle();
            if( !title.isNull() )
            {
                auto sectionWidget = addSectionLayout( layout, title->getHeight(), report->getLeftMargin(), m_report->getRightMargin() );
                if( !createSection( sectionWidget, title, 0 ) )
                {
                    return false;
                }
            }

            int count = isReport() ? report->getRowCount() : 1;
            for( int i = 0; i < count; ++i )
            {
                auto sectionWidget = addSectionLayout( layout, detail->getHeight(), report->getLeftMargin(), m_report->getRightMargin() );
                if( !createSection( sectionWidget, detail, i ) )
                {
                    return false;
                }
            }

            addEmptySection( layout, report->getLeftMargin(), report->getRightMargin() );
            addVerticalBorder( layout, report->getBottomMargin(), report->getLeftMargin(), report->getRightMargin() );

            return true;
        }


        bool    ConverterToQWidget::createSection( QWidget * parent, const SectionPtr & section, int i )
        {
            if( isLayout() )
            {
                auto label = new QLabel( parent );
                label->setText( section->getTagName() );
                label->setStyleSheet( "font-size: 26px; color: gray" );
                label->setAlignment( Qt::AlignCenter );
                label->setAttribute( Qt::WA_TranslucentBackground );
                label->resize( parent->size() );
            }

            if( !createBands( parent, section, i ) )
            {
                return false;
            }

            return true;
        }

        bool    ConverterToQWidget::createBands( QWidget * parent, const SectionPtr & section, int i )
        {
            auto dy = 0;
            for( auto && band : section->getBands() )
            {
                if( m_currentHeight + band->getHeight() > m_report->getHeight() )
                {
                    parent = addPage();
                    m_currentHeight = 0;
                }
                m_currentHeight += band->getHeight();

                auto frame = new QFrame( parent );
                frame->move( frame->x(), dy );
                dy += band->getHeight();
                frame->setStyleSheet( "background-color: transparent; " );
                for( auto && staticText : band->getStaticTexts() )
                {
                    auto label = new QLabel( frame );
                    QString style = "";
                    if( staticText->isBold() )
                    {
                        style += "font-weight: bold; ";
                    }
                    if( isLayout() )
                    {
                        style += "border: 1px solid gray; ";
                    }
                    label->setStyleSheet( "background-color: transparent; " + style );
                    label->setGeometry( staticText->getRect() );
                    label->setAlignment( staticText->getAlignment() );
                    label->setText( staticText->getText() );
                }
                for( auto && textField : band->getTextFields() )
                {
                    auto label = new QLabel( frame );
                    QString style = "";
                    if( textField->isBold() )
                    {
                        style += "font-weight: bold; "; 
                    }
                    if( isLayout() )
                    {
                        style += "border: 1px solid gray; ";
                    }
                    label->setStyleSheet( "background-color: transparent; " + style );
                    label->setGeometry( textField->getRect() );
                    label->setAlignment( textField->getAlignment() );

                    auto text = textField->getText();
                    text = text.replace( "\n", "" ).replace( "\r", "" ).replace( " ", "" );
                    if( isReport() && text.startsWith( "$F{" ) && text.contains( "}" ) )
                    {
                        auto name = text.split( "{" ).at( 1 ).split( "}" ).at( 0 );
                        text = m_report->getField( name )->getData( i );
                    }
                    label->setText( text );
                }
                for( auto && line : band->getLines() )
                {
                    auto label = new QLabel( frame );
                    QString style = "";
                    if( line->isBold() )
                    {
                        style += "font-weight: bold; ";
                    }
                    //if( isLayout() )
                    {
                        style += "border: 1px solid gray; ";
                    }
                    label->setStyleSheet( "background-color: transparent; " + style );
                    label->setGeometry( line->getRect() );
                    label->setAlignment( line->getAlignment() );
                    //label->setText( "----------------------" );
                }
                for( auto && rect : band->getRects() )
                {
                    auto label = new QLabel( frame );
                    QString style = "";
                    if( rect->isBold() )
                    {
                        style += "font-weight: bold; ";
                    }
                    //if( isLayout() )
                    {
                        style += "border: 1px solid gray; ";
                    }
                    label->setStyleSheet( "background-color: transparent; " + style );
                    label->setGeometry( rect->getRect() );
                    label->setAlignment( rect->getAlignment() );
                    //label->setText( "----------------------" );
                }
            }

            return true;
        }

    }
}
