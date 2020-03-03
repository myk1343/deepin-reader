/*
 * Copyright (C) 2019 ~ 2019 Deepin Technology Co., Ltd.
 *
 * Author:     duanxiaohui
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef SEARCHITEMWIDGET_H
#define SEARCHITEMWIDGET_H

#include <DLabel>
#include <DTextEdit>

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFont>
#include <QMenu>
#include <QAction>
#include <QContextMenuEvent>

#include "../CustomItemWidget.h"

/**
 * @brief   搜索item
 */

class SearchItemWidget : public CustomItemWidget
{
    Q_OBJECT
    Q_DISABLE_COPY(SearchItemWidget)

public:
    explicit SearchItemWidget(DWidget *parent = nullptr);
    ~SearchItemWidget() override;

public:
    // IObserver interface
    int dealWithData(const int &, const QString &) override;

public:
    void setTextEditText(const QString &);
    void setSerchResultText(const QString &);
    bool bSelect();
    void setBSelect(const bool &paint);

private slots:
    void slotUpdateTheme();

protected:
    void initWidget() override;

    void resizeEvent(QResizeEvent *event) override;
    void paintEvent(QPaintEvent *e) override;


private:
    DLabel *m_pSearchResultNum = nullptr;
    DLabel *m_pTextLab = nullptr;
    QString m_strNote = "";   // 注释内容
    bool m_bPaint = false;
    DMenu *m_menu = nullptr;
};

#endif // SEARCHITEMWIDGET_H