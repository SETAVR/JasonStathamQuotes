#include "mainwindow.h"

#include <QHBoxLayout>
#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
    , m_quotes({QStringLiteral("Упал - вставай. Встал - упай. Чокопай"),
                QStringLiteral("В жизни всегда есть две дороги: одна - первая, а другая - вторая."),
                QStringLiteral("Запомни: всего одна ошибка – и ты ошибся."),
                QStringLiteral("Как говорил мой дед: «Я твой дед»."),
                QStringLiteral("Слово - не воробей. Вообще ничто не воробей, кроме самого воробья."),
                QStringLiteral("Если тебе где-то не рады в рваных носках, то и в целых туда идти не стоит."),
                QStringLiteral("Если закрыть глаза, становится темно."),
                QStringLiteral("Кто рано встаёт - тому весь день спать хочется."),
                QStringLiteral("Ради денег люди готовы пойти на всё, даже на работу.")})
{
    setWindowTitle(QStringLiteral("Библиотека цитат Джейсона Стейтема"));
    resize(540, 240);
    m_layout = new QVBoxLayout(this);

    auto *buttons = new QHBoxLayout;
    m_visibilityButton = new QPushButton(this);
    m_visibilityButton->setObjectName("visibilityButton");
    m_autoButton = new QPushButton(QStringLiteral("Автосмена: выкл."), this);
    m_autoButton->setObjectName("autoButton");
    buttons->addWidget(m_visibilityButton);
    buttons->addWidget(m_autoButton);
    m_layout->addLayout(buttons);

    m_timer = new QTimer(this);
    m_timer->setObjectName("quoteTimer");
    m_timer->setInterval(5000);

    // The window is the context, so its destruction disconnects the lambdas.
    connect(m_visibilityButton, &QPushButton::clicked, this, [this] { toggleQuote(); });
    connect(m_autoButton, &QPushButton::clicked, this, [this] { toggleAutoChange(); });
    connect(m_timer, &QTimer::timeout, this, [this] {
        if (!m_quoteLabel) return;
        m_index = (m_index + 1) % int(m_quotes.size());
        m_quoteLabel->setText(m_quotes.at(m_index));
        qDebug() << "[TIMER] Quote changed, index:" << m_index;
    });

    showQuote();
}

void MainWindow::showQuote()
{
    if (m_quoteLabel) return;
    // The label belongs to the window and will also be deleted with it.
    m_quoteLabel = new QuoteLabel(m_quotes.at(m_index), this);
    m_layout->insertWidget(0, m_quoteLabel.data(), 1);
    m_visibilityButton->setText(QStringLiteral("Скрыть цитату"));
}

void MainWindow::toggleQuote()
{
    if (!m_quoteLabel) {
        showQuote();
        return;
    }

    stopAutoChange();
    m_layout->removeWidget(m_quoteLabel.data());
    m_quoteLabel->hide();
    m_quoteLabel->deleteLater();
    // Treat the label as hidden immediately, before DeferredDelete is processed.
    m_quoteLabel.clear();
    m_visibilityButton->setText(QStringLiteral("Показать цитату"));
}

void MainWindow::toggleAutoChange()
{
    if (m_timer->isActive()) {
        stopAutoChange();
    } else {
        showQuote();
        m_timer->start();
        m_autoButton->setText(QStringLiteral("Автосмена: вкл."));
        qDebug() << "[TIMER] Started, interval:" << m_timer->interval();
    }
}

void MainWindow::stopAutoChange()
{
    m_timer->stop();
    m_autoButton->setText(QStringLiteral("Автосмена: выкл."));
    qDebug() << "[TIMER] Stopped";
}
