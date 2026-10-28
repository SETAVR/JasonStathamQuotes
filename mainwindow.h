#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPointer>
#include <QStringList>
#include <QWidget>
#include "quotelabel.h"

class QPushButton;
class QTimer;
class QVBoxLayout;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

private:
    void showQuote();
    void toggleQuote();
    void toggleAutoChange();
    void stopAutoChange();

    const QStringList m_quotes;
    int m_index = 0;
    QPointer<QuoteLabel> m_quoteLabel;
    QVBoxLayout *m_layout;
    QPushButton *m_visibilityButton;
    QPushButton *m_autoButton;
    QTimer *m_timer;
};

#endif
