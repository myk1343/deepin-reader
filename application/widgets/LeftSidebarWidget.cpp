#include "LeftSidebarWidget.h"

#include <DStackedWidget>
#include <QButtonGroup>
#include <QVBoxLayout>

#include "MainOperationWidget.h"
#include "MsgModel.h"

#include "docview/docummentproxy.h"
#include "pdfControl/DataStackedWidget.h"

#include "widgets/main/MainTabWidgetEx.h"

LeftSidebarWidget::LeftSidebarWidget(CustomWidget *parent)
    : CustomWidget("LeftSidebarWidget", parent)
{
    setMinimumWidth(LEFTMINWIDTH);
    setMaximumWidth(LEFTMAXWIDTH);

    resize(LEFTNORMALWIDTH, this->height());

    m_pMsgList = {MSG_WIDGET_THUMBNAILS_VIEW};
    initWidget();
    initConnections();

    onSetWidgetVisible(0);  //  默认 隐藏
    slotUpdateTheme();

    dApp->m_pModelService->addObserver(this);
}

LeftSidebarWidget::~LeftSidebarWidget()
{
    dApp->m_pModelService->removeObserver(this);
}

void LeftSidebarWidget::SlotOpenFileOk(const QString &sPath)
{
    FileDataModel fdm = MainTabWidgetEx::Instance()->qGetFileData(sPath);
    int nShow = fdm.qGetData(Thumbnail);
    bool showLeft = nShow == 1 ? true : false;
    onSetWidgetVisible(showLeft);
}

void LeftSidebarWidget::onSetWidgetVisible(const int &nVis)
{
    this->setVisible(nVis);
}

void LeftSidebarWidget::slotUpdateTheme()
{
    updateWidgetTheme();
}

void LeftSidebarWidget::initConnections()
{
    connect(this, SIGNAL(sigUpdateTheme()), SLOT(slotUpdateTheme()));
}

void LeftSidebarWidget::initWidget()
{
    auto pVBoxLayout = new QVBoxLayout;
    pVBoxLayout->setContentsMargins(0, 0, 0, 0);
    pVBoxLayout->setSpacing(0);
    this->setLayout(pVBoxLayout);

    auto pStackedWidget = new DataStackedWidget(this);
    pVBoxLayout->addWidget(pStackedWidget);

    m_pMainOperationWidget = new MainOperationWidget;
    connect(m_pMainOperationWidget, SIGNAL(sigShowStackWidget(const int &)), pStackedWidget, SLOT(slotSetStackCurIndex(const int &)));

    pVBoxLayout->addWidget(m_pMainOperationWidget, 0, Qt::AlignBottom);
}

int LeftSidebarWidget::dealWithData(const int &msgType, const QString &msgContent)
{
    return 0;
}

int LeftSidebarWidget::qDealWithData(const int &msgType, const QString &msgContent)
{
    if (msgType == MSG_WIDGET_THUMBNAILS_VIEW) {
        onSetWidgetVisible(msgContent.toInt());
    } else if (msgType == MSG_OPERATION_OPEN_FILE_OK) {
        SlotOpenFileOk(msgContent);

        m_pMainOperationWidget->qDealWithData(msgType, msgContent);
    }

    int nRes = MSG_NO_OK;
    if (m_pMsgList.contains(msgType)) {
        nRes = MSG_OK;
    }

    if (nRes != MSG_OK) {
        auto children = this->findChildren<CustomWidget *>();
        foreach (auto cw, children) {
            nRes = cw->qDealWithData(msgType, msgContent);
            if (nRes == MSG_OK) {
                break;
            }
        }
    }

    return nRes;
}