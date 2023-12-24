#include "mainwindow.h"
//#include "HybridMenubar/menuactionproxystyle.h"

#include <QApplication>
#include <QPainterPath>
#include <QStyle>
#include <QSurfaceFormat>
#include <QWindow>
#include <dwmapi.h>

static QRegion roundedRect(const QRect& rect, int r)
{
    QRegion region;
    // middle and borders
//    region += rect.adjusted(r, 0, -r, 0);
//    region += rect.adjusted(0, r, 0, -r);
    // top left
    QRect corner(rect.topLeft(), QSize(r*2, r*2));
    region += QRegion(corner, QRegion::Ellipse);
    // top right
    corner.moveTopRight(rect.topRight());
    region += QRegion(corner, QRegion::Ellipse);
    // bottom left
    corner.moveBottomLeft(rect.bottomLeft());
    region += QRegion(corner, QRegion::Rectangle);
    // bottom right
    corner.moveBottomRight(rect.bottomRight());
    region += QRegion(corner, QRegion::Ellipse);
    return region;
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
//    w.setWindowFlags(Qt::WindowFlags() | Qt::CustomizeWindowHint );
//    w.setStyleSheet("Window { "
//                    "   border: 2px solid red;"
//                    "}");
//    QPainterPath path;
//    path.addRoundedRect(w.rect(), 6, 6);
//    w.setMask(path.toFillPolygon().toPolygon());
//    w.setMask(roundedRect(w.rect(), 200));

//    QSurfaceFormat format;
//    format.setAlphaBufferSize(8);
//    w.setForegroundRole()


//    w.setStyle(new MenuActionProxyStyle);
    w.show();

//    auto hWnd = (HWND)w.window()->windowHandle()->winId();
//    {
//    //    hWnd->setFormat(format);


//        MARGINS margins;

//        margins.cxLeftWidth = 8;      // 8
//        margins.cxRightWidth = 8;    // 8
//        margins.cyBottomHeight = 20; // 20
//        margins.cyTopHeight = 27;       // 27
//        auto hr = DwmExtendFrameIntoClientArea(hWnd, &margins);

//        if (!SUCCEEDED(hr))
//        {
//            // Handle the error.
//            qDebug() << "[fail] DwmExtendFrameIntoClientArea";
//        }
//    }

//    {
//        RECT rcClient;
//        GetWindowRect(hWnd, &rcClient);

//        // Inform the application of the frame change.
//        SetWindowPos(hWnd,
//                     NULL,
//                     rcClient.left, rcClient.top,
//                     rcClient.right-rcClient.left, rcClient.bottom-rcClient.top,
//                     SWP_FRAMECHANGED);

//    }
    return a.exec();
}


// https://deeditor.com/ : icon color change from .svg file
// https://bugreports.qt.io/browse/QTBUG-47543?attachmentOrder=desc : 확장 창 영역
// https://learn.microsoft.com/ko-kr/windows/win32/dwm/customframe?redirectedfrom=MSDN : 확장 창 영역
