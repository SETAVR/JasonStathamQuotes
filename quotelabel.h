#ifndef QUOTELABEL_H
#define QUOTELABEL_H

#include <QDebug>
#include <QLabel>

class QuoteLabel : public QLabel
{
public:
    QuoteLabel(const QString &text, QWidget *parent) : QLabel(text, parent)
    {
        setObjectName("quoteLabel");
        setAlignment(Qt::AlignCenter);
        setWordWrap(true);
        setMinimumHeight(120);
        qDebug() << "[CREATE] QuoteLabel";
    }

    ~QuoteLabel() override
    {
        qDebug() << "[DESTROY] QuoteLabel";
    }
};

#endif
