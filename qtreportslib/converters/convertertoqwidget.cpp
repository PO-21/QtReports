#include <QFrame>
#include <QLabel>
#include <QPainter>
#include "utils/replacer.hpp"
#include "convertertoqwidget.hpp"
#include <QDebug>

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

        void    ConverterToQWidget::addVerticalBorder( QBoxLayout * parent, const QMargins & margins, int height )
        {
            auto leftFrame = new QFrame();
            leftFrame->setFixedWidth( margins.left() );
            leftFrame->setFixedHeight( height );

            auto centerFrame = new QFrame();
            centerFrame->setFixedHeight( height );

            auto rightFrame = new QFrame();
            rightFrame->setFixedWidth( margins.right() );
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

        void    ConverterToQWidget::addEmptySection( QBoxLayout * parent, const QMargins & margins )
        {
            auto leftFrame = new QFrame();
            leftFrame->setFixedWidth( margins.left() );

            auto centerFrame = new QFrame();

            auto rightFrame = new QFrame();
            rightFrame->setFixedWidth( margins.right() );

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

        QFrame *    ConverterToQWidget::addSectionLayout( QBoxLayout * parent, const QMargins & margins, int height )
        {
            auto leftFrame = new QFrame();
            leftFrame->setFixedHeight( height );
            leftFrame->setFixedWidth( margins.left() );

            auto centerFrame = new QFrame();
            centerFrame->setFixedHeight( height );



            auto rightFrame = new QFrame();
            rightFrame->setFixedHeight( height );
            rightFrame->setFixedWidth( margins.right() );

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

        void    ConverterToQWidget::addPage()
        {
            QWidgetPtr widget( new QWidget() );
            widget->resize( m_report->getSize() );
            widget->setStyleSheet( "background-color: white; " );
            m_pages.append( widget );
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

            addPage();

            auto layout = new QVBoxLayout( m_qwidget.data() );
            layout->setMargin( 0 );
            layout->setSpacing( 0 );
            addVerticalBorder( layout, report->getMargins(), report->getTopMargin() );

            auto title = report->getTitle();
            if( !title.isNull() )
            {
                QWidget * sectionWidget = isLayout() ? addSectionLayout( layout, report->getMargins(), title->getHeight() ) : nullptr;
                if( !createSection( sectionWidget, title, 0 ) )
                {
                    return false;
                }
            }

            int count = isReport() ? report->getRowCount() : 1;
            for( int i = 0; i < count; ++i )
            {
                QWidget * sectionWidget = isLayout() ? addSectionLayout( layout, report->getMargins(), detail->getHeight() ) : nullptr;
                if( !createSection( sectionWidget, detail, i ) )
                {
                    return false;
                }
            }

            addEmptySection( layout, report->getMargins() );
            addVerticalBorder( layout, report->getMargins(), report->getBottomMargin() );
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
            else
            {
                detail::Replacer replacer;
                if( !replacer.replace( section, m_report, i ) )
                {
                    m_lastError = "Error in replacing process: " + replacer.getLastError();
                    return false;
                }
            }

            if( !createBands( parent, section ) )
            {
                return false;
            }

            return true;
        }

        bool    ConverterToQWidget::createBands( QWidget * parent, const SectionPtr & section )
        {
            auto dy = 0;
            for( auto && band : section->getBands() )
            {
                if( m_currentHeight + band->getHeight() > m_report->getHeight() )
                {
                    addPage();
                    m_currentHeight = 0;
                }

                auto frame = new QFrame( isLayout() ? parent : m_pages.last().data() );
                frame->setStyleSheet( "background-color: transparent; " );
                frame->move( frame->x(), isLayout() ? dy : m_currentHeight );

                m_currentHeight += band->getHeight();
                dy += band->getHeight();

                for( auto && textWidget : band->getTextWidgets() )
                {
                    auto label = new QLabel( frame );
                    QString style = "";
                    if( textWidget->isBold() )
                    {
                        style += "font-weight: bold; ";
                    }
                    if( isLayout() )
                    {
                        style += "border: 1px solid gray; ";
                    }
                    label->setStyleSheet( "background-color: transparent; " + style );
                    label->setGeometry( textWidget->getRect() );
                    label->setAlignment( textWidget->getAlignment() );
                    auto text = isLayout() ? textWidget->getOriginalText() : textWidget->getText();
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
                for( auto && imageWidget : band->getImages() )
                {
                    if( imageWidget->getRect().isEmpty() )
                    {
                        m_lastError = "Ellipse \"" + imageWidget->getName() + "\" rect is empty";
                        return false;
                    }

                    auto label = new QLabel( frame );
                    QString style = "";
                    if( isLayout() )
                    {
                        style += "border: 1px solid gray; ";
                    }
                    label->setStyleSheet( "background-color: transparent; " + style );
                    label->setGeometry( imageWidget->getRect() );
                    label->setAlignment( imageWidget->getAlignment() );
                    label->setPixmap( QPixmap::fromImage( imageWidget->getImage() ) );
                }
                for( auto && rect : band->getRects() )
                {
                    if( rect->getRect().isEmpty() )
                    {
                        m_lastError = "Rect \"" + rect->getName() + "\" rect is empty";
                        return false;
                    }

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
                for( auto && ellipse : band->getEllipses() )
                {
                    if( ellipse->getSize().isEmpty() )
                    {
                        m_lastError = "Ellipse \"" + ellipse->getName() + "\" size is empty";
                        return false;
                    }

                    auto label = new QLabel( frame );
                    QString style = "";
                    if( isLayout() )
                    {
                        style += "border: 1px solid gray; ";
                    }

                    QPixmap pixmap( ellipse->getSize() );
                    pixmap.fill( Qt::GlobalColor::transparent );

                    QPainter painter( &pixmap );
                    painter.setRenderHint( QPainter::Antialiasing );
                    painter.drawEllipse( ellipse->getRect() );
                    painter.end();
                    label->setPixmap( pixmap );

                    label->setStyleSheet( "background-color: transparent; " + style );
                    label->setGeometry( ellipse->getRect() );
                    label->setAlignment( ellipse->getAlignment() );
                }
            }

            return true;
        }

    }
}
