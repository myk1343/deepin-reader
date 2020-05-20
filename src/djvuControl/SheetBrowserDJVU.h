#ifndef SHEETBROWSERDJVU_H
#define SHEETBROWSERDJVU_H

#include <QGraphicsView>
#include "document/model.h"
#include "global.h"
#include <QLabel>

class DocOperation;
class SheetBrowserDJVUItem;
class SheetBrowserDJVU : public QGraphicsView
{
    Q_OBJECT
public:
    explicit SheetBrowserDJVU(QWidget *parent = nullptr);

    ~SheetBrowserDJVU();

    bool openFilePath(const QString &);

    void loadPages(DocOperation &operation);

    void loadMouseShape(DocOperation &operation);

    void deform(DocOperation &operation);      //根据当前参数进行变换

    bool hasLoaded();

    int allPages();

    int currentPage();

    int  viewPointInPage(QPoint viewPoint);

    void setCurrentPage(int page);

    bool getImageMax(int index, QImage &image, double max);

    void openMagnifier();

    void closeMagnifier();

signals:
    void sigPageChanged(int page);

    void sigWheelUp();

    void sigWheelDown();

    void sigSizeChanged();

protected:
    void showEvent(QShowEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event);

    void dragEnterEvent(QDragEnterEvent *event);

    void wheelEvent(QWheelEvent *event);

    bool getImagePoint(QPoint viewPoint, double scaleFactor, QImage &image);

private slots:
    void onVerticalScrollBarValueChanged(int value);

private:
    deepin_reader::Document *m_document = nullptr;
    QList<SheetBrowserDJVUItem *> m_items;
    double m_lastScaleFactor = 0;
    int m_maxWidth = 0;         //最大一页的宽度
    int m_maxHeight = 0;        //最大一页的高度
    bool m_hasLoaded = false;   //是否已经加载过每页的信息
    int m_initPage = 1;         //用于刚显示跳转的页数
    QLabel *m_magnifierLabel = nullptr;
};

#endif // SHEETBROWSERDJVU_H