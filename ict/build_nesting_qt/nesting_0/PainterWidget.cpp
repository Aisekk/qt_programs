#include "PainterWidget.h"
#include <QPainter>
#include <QResizeEvent>
#include <QPaintEvent>
#include <QStandardItemModel>
#include "drawers/DrawerParams.h"

PainterWidget::PainterWidget(QWidget *parent) : QWidget(parent),
    m_pixmap(QPixmap(300,300)),
    m_sheetWidth(m_pixmap.width()), m_sheetHeight(m_pixmap.height()),
    m_upAlgorithmDrawer(new NestingDrawer),
    m_drawing(m_upAlgorithmDrawer.get())
{
    setMinimumSize(m_pixmap.size());
}
void PainterWidget::resizeEvent(QResizeEvent *pEvent)
{
    m_pixmap = QPixmap(pEvent->size());
    m_pixmap.fill(Qt::white);
    draw();
}
void PainterWidget::paintEvent(QPaintEvent *pEvent)
{
    QPainter painter(this);
    painter.drawPixmap(0, 0, m_pixmap);
    pEvent->accept();
}
void PainterWidget::imageClear()
{
    m_pixmap.fill(Qt::white);
}
void PainterWidget::setSheetSizes(double sheetWidth, double sheetHeight)
{
    m_sheetWidth = sheetWidth;
    m_sheetHeight = sheetHeight;
}
void PainterWidget::setItemSizesModel(const QStandardItemModel& model)
{
    int rows = model.rowCount();
    int columns = model.columnCount();

    imageClear();
    m_mmap_Square_and_ItemSizes.clear();

    QLocale russian(QLocale::Russian);
    for (int row = 0; row < rows; ++row)
    {
        double square = 1.0;
        QPair<double,double> sizes;
        for (int column = 0; column < columns; ++column)
        {
            QModelIndex index = model.index(row, column, QModelIndex());
            QString str = (index.data()).toString();
            double size = russian.toDouble(str);
            if(column == 0)
                sizes.first = size;
            else
                sizes.second = size;
            square *= russian.toDouble(str);
        }
        m_mmap_Square_and_ItemSizes.insert(square, sizes);
    }
}

void PainterWidget::draw()
{
    QPainter painter(&m_pixmap);
    drawMetalSheet_and_Items(painter);
}
void PainterWidget::drawMetalSheet_and_Items(QPainter& painter)
{
    // если количество изделий = 0
    if(m_mmap_Square_and_ItemSizes.isEmpty()) return;

    // коэффициент масштабирования
    double scale = height() * 0.98;
    // выполнимое количество изделий
    int nExecItemCount{};
    // контейнер с изделиями
    ItemsContainer itemsContainer(m_mmap_Square_and_ItemSizes);

    // АЛГОРИТМ РАСКРОЯ ЛИСТА МЕТАЛЛА

    /* Параметры алгоритма:
     * scale, not scaled sheet width, not scaled sheet height, painter&,
     * контейнер с изделиями &,
     * выполнимое количество изделий (executed item count) &
    */
    DrawerParams params(scale, m_sheetWidth, m_sheetHeight, painter,
                        itemsContainer, nExecItemCount);
    // алгоритм
    m_drawing.draw(params);

    emit executedItemQuantity(params.m_nExecItemCount);
}


