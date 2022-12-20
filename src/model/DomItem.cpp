#include <model/DomItem.h>

// Copyright (C) 2016 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QtXml>

DomItem::DomItem(const QDomNode &node, int row, DomItem *parent)
        : domNode(node),
        // Record the item's location within its parent.
          parentItem(parent),
          rowNumber(row)
{}

DomItem::~DomItem()
{
    qDeleteAll(childItems);
}

QDomNode DomItem::node() const
{
    return domNode;
}

DomItem *DomItem::parent()
{
    return parentItem;
}

DomItem *DomItem::child(int i)
{
    DomItem *childItem = childItems.value(i);
    if (childItem)
        return childItem;

    // if child does not yet exist, create it
    if (i >= 0 && i < domNode.childNodes().count()) {
        QDomNode childNode = domNode.childNodes().item(i);
        childItem = new DomItem(childNode, i, this);
        childItems[i] = childItem;
    }
    return childItem;
}

int DomItem::row() const
{
    return rowNumber;
}
