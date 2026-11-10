#include "mainwindow.h"
#include "quote_delegate.h"

#include <QHBoxLayout>
#include <QListView>
#include <QPushButton>
#include <QStringListModel>
#include <QTimer>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle(QStringLiteral("Библиотека цитат Джейсона Стейтема"));
    resize(720, 500);
    m_model = new QStringListModel(this);
    m_model->setObjectName("quoteModel");
    m_model->setStringList({QStringLiteral("Упал - вставай. Встал - упай. Чокопай"),
                QStringLiteral("В жизни всегда есть две дороги: одна - первая, а другая - вторая."),
                QStringLiteral("Запомни: всего одна ошибка – и ты ошибся."),
                QStringLiteral("Как говорил мой дед: «Я твой дед»."),
                QStringLiteral("Слово - не воробей. Вообще ничто не воробей, кроме самого воробья."),
                QStringLiteral("Если тебе где-то не рады в рваных носках, то и в целых туда идти не стоит."),
                QStringLiteral("Если закрыть глаза, становится темно."),
                QStringLiteral("Кто рано встаёт - тому весь день спать хочется."),
                QStringLiteral("Ради денег люди готовы пойти на всё, даже на работу.")});
    m_layout = new QVBoxLayout(this);

    m_view = new QListView(this);
    m_view->setObjectName("quoteView");
    m_view->setModel(m_model);
    m_view->setSelectionMode(QAbstractItemView::SingleSelection);
    m_view->setEditTriggers(QAbstractItemView::DoubleClicked);
    m_view->setWordWrap(true);
    m_view->setItemDelegate(new QuoteDelegate(m_view));
    m_view->setToolTip(QStringLiteral("Двойной клик по цитате — редактировать. Enter — сохранить, Escape — отменить."));
    m_layout->addWidget(m_view, 2);

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
        if (!m_quoteLabel || m_model->rowCount() == 0) return;
        m_index = (m_index + 1) % m_model->rowCount();
        updateQuote();
        qDebug() << "[TIMER] Quote changed, index:" << m_index;
    });
    // Both the current quote and its list read the same data source.
    connect(m_model, &QStringListModel::dataChanged, this, [this] { updateQuote(); });

    showQuote();
}

void MainWindow::showQuote()
{
    if (m_quoteLabel) return;
    // The label belongs to the window and will also be deleted with it.
    m_quoteLabel = new QuoteLabel(m_model->index(m_index, 0).data().toString(), this);
    m_layout->insertWidget(0, m_quoteLabel.data(), 1);
    m_visibilityButton->setText(QStringLiteral("Скрыть цитату"));
}

void MainWindow::updateQuote()
{
    if (m_quoteLabel)
        m_quoteLabel->setText(m_model->index(m_index, 0).data().toString());
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
