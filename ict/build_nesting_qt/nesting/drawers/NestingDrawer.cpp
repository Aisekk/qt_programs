#include "NestingDrawer.h"
#include "DrawerParams.h"
#include <QPainter>

NestingDrawer::NestingDrawer() : Drawer() {}

void NestingDrawer::drawItem(QPainter &painter, double x, double y, double width, double height)
{
    QRectF itemRect(x, y, width, height);
    painter.drawRect(itemRect);
}

void NestingDrawer::draw(DrawerParams &params)
{
    // масштабирование
    double tan_alpha = params.m_notScaledSheetWidth / params.m_notScaledSheetHeight;
    double sheet_h_scaled = params.m_scale;
    double sheet_w_scaled = sheet_h_scaled * tan_alpha;

    // инструменты рисования
    QPainter& painter = params.m_painter;
    QPen pen(QColor(0, 0, 0));
    pen.setStyle(Qt::SolidLine);
    pen.setWidth(2);
    painter.setPen(pen);
    // рисование листа металла
    double x0 = 0.0;
    double y0 = 0.0;
    QRectF sheet(x0, y0, sheet_w_scaled, sheet_h_scaled);
    painter.drawRect(sheet);

    // высота и ширина листа металла
    double hs = sheet_h_scaled;
    double ws = sheet_w_scaled;
    // координаты изделия (верхнего левого угла)
    double x = x0, y = y0;
    // смещение координат изделия
    double dx = 0.0, dy = 0.0;
    // оставшееся место на листе
    double hr = hs;
    double wr = ws;
    // высота максимальная из предыдущих высот изделий, размещенных на листе
    double h_max = 0.0;
    // минимальное оставшееся место по ширине листа
    double wr_min = ws, wr_min_temp;
    // смещение по X происходит, если лист заполнен по высоте и еще есть свободное место
    double shift_x = 0.0;
    // выполнимое количество изделий
    int& nExecItemCount = params.m_nExecItemCount;

    ItemsContainer& itemsContainer = params.m_itemsContaner;

    auto it = itemsContainer.begin();
    auto it_end = itemsContainer.end();

    while(it != it_end)
    {
        // размеры изделий
        double w = it.item_width();
        double h = it.item_height();
        ++ it;
        double tan_angle = w / h;
        // масштабированные размеры изделий
        h = h * params.m_scale / params.m_notScaledSheetHeight;
        w = h * tan_angle;

        // изделие умещается на листе металла
        bool bItemTooLarge = false;
        // второй проход алгоритма, если изделие не умещается по высоте, но умещается по ширине
        int N = 2;

        for(int i = 0; i < N; ++i)
        {
            if(h - hr <= eps && w - ws <= eps)
            {
                // размещение вдоль Y (вниз)
                x = x0 + shift_x;
                y += dy;
                drawItem(painter, x, y, w, h);
                hr -= h;
                wr = ws - w;
                dx = w; dy = h;
                h_max = h;

                wr_min_temp = std::min(wr, wr_min);
                wr_min = wr_min_temp;

                ++ nExecItemCount;
                break;
            }
            else if(h - hr > eps && h - (h_max + hr) <= eps && w - wr <= eps)
            {
                // размещение вдоль X (вправо)
                x += dx;
                drawItem(painter, x, y, w, h);
                dx = w;
                if(h - h_max > eps)
                {
                    hr = hr - (h - h_max);
                    h_max = h;
                    dy = h;
                }
                else
                {
                    dy = h_max;
                }
                wr -= w;

                wr_min_temp = std::min(wr, wr_min);
                wr_min = wr_min_temp;

                ++ nExecItemCount;
                break;
            }
            else if(h - hr > eps && w - hr > eps && (h - wr_min <= eps || w - wr_min <= eps)
                    && y + h - hs > eps)
            {
                // если лист заполнен по высоте, но изделия еще остались и есть место,
                // рисование продолжается сверху вниз со смещением по оси X
                double new_h = std::max(h, w);
                double new_w = std::min(h, w);
                if(new_h - hs <= eps)
                {
                    y = y0;
                    x = ws - wr_min;
                    drawItem(painter, x, y, new_w, new_h);
                    hr = hs - new_h;
                    wr = wr_min - w;
                    dy = new_h;
                    dx = new_w;
                    shift_x += x;

                    wr_min_temp = std::min(wr, wr_min);
                    wr_min = wr_min_temp;

                    ++ nExecItemCount;
                    break;
                }
            }
            else if(h - hr > eps && (w - ws <= eps ||
                                     (h - (h_max + hr) > eps && w - wr <= eps)) )
            {
                // если изделие не умещается по высоте, но умещается по ширине
                std::swap(h, w);
                continue;
            }
            else
            {
                bItemTooLarge = true;
                break;
            }

        }

        // изделие, не умещаемое на листе, не рисуется
        if(bItemTooLarge) continue;

    } // while()

}


