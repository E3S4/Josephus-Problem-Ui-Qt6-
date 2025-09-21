#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSpinBox>
#include <QPushButton>
#include <QLabel>
#include <QSlider>
#include <QTimer>
#include <QTextEdit>
#include <QPainter>
#include <QPaintEvent>
#include <QStyleOption>
#include <QGroupBox>
#include <cmath>
#include <vector>
class CircleWidget : public QWidget {
    Q_OBJECT
public:
    CircleWidget(QWidget *parent = nullptr) : QWidget(parent) {
        setMinimumSize(420, 420);
    }
    void setPeople(int n) {
        total = n;
        alive.assign(n, true);
        activeIndices.clear();
        for (int i = 0; i < n; ++i) activeIndices.push_back(i);
        currentPos = 0;
        lastEliminated = -1;
        finished = (n <= 1);
        update();
    }

    
    void markEliminated(int idx) {
        if (idx < 0 || idx >= total) return;
        lastEliminated = idx;
        alive[idx] = false;
        for (auto it = activeIndices.begin(); it != activeIndices.end(); ++it) {
            if (*it == idx) { activeIndices.erase(it); break; }
        }
        if (activeIndices.size() <= 1) finished = true;
        update();
    }

    void setCurrentHighlight(int idx) {
        currentHighlight = idx;
        update();
    }
    int remainingCount() const { return static_cast<int>(activeIndices.size()); }
    void resetState() {
        currentHighlight = -1;
        lastEliminated = -1;
        finished = (activeIndices.size() <= 1);
        update();
    }
protected:
    void paintEvent(QPaintEvent *ev) override {
        Q_UNUSED(ev);
        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing, true);
        p.setBrush(palette().window());
        p.drawRect(rect());

        int w = width(), h = height();
        QPoint center(w/2, h/2);
        int radius = std::min(w, h) / 2 - 50;
        if (radius < 60) radius = std::min(w, h) / 2 - 20;

        if (total == 0) {
            p.drawText(rect(), Qt::AlignCenter, "Set n > 0 to visualize");
            return;
        }
        for (int i = 0; i < total; ++i) {
            double angle = 2.0 * M_PI * i / total - M_PI / 2.0; // start top
            int x = center.x() + int(radius * cos(angle));
            int y = center.y() + int(radius * sin(angle));
            QRect circleRect(x - 24, y - 24, 48, 48);
            bool isAlive = alive[i];
            bool isElim = (i == lastEliminated);
            bool isCurrent = (i == currentHighlight);

            if (!isAlive) {
                p.setBrush(QColor(80, 80, 80)); 
                p.setPen(Qt::NoPen);
            } else if (isElim) {
                p.setBrush(QColor(220, 80, 80)); 
                p.setPen(Qt::NoPen);
            } else if (isCurrent) {
                p.setBrush(QColor(255, 215, 0)); 
                p.setPen(Qt::NoPen);
            } else {
                p.setBrush(QColor(100, 180, 240)); 
                p.setPen(Qt::NoPen);
            }
            p.drawEllipse(circleRect);

            p.setPen(Qt::black);
            p.setFont(QFont("Sans", 10, QFont::Bold));
            QString label = QString::number(i + 1);
            p.drawText(circleRect, Qt::AlignCenter, label);
        }

          if (finished && total > 0) {
            int survivor = -1;
            for (int i = 0; i < total; ++i) if (alive[i]) { survivor = i; break; }
            if (survivor != -1) {
                QString text = QString("Safe position: %1").arg(survivor + 1);
                p.setPen(QColor(240,240,240));
                p.setFont(QFont("Sans", 14, QFont::Bold));
                p.drawText(10, 20, text);
            }
        }
    }

private:
    int total = 0;
    std::vector<bool> alive;
    std::vector<int> activeIndices;
    int currentPos = 0;        
    int currentHighlight = -1; 
    int lastEliminated = -1;   
    bool finished = true;
};

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow() {
        auto *central = new QWidget;
        setCentralWidget(central);

        auto *mainLayout = new QHBoxLayout;
        central->setLayout(mainLayout);

        auto *left = new QVBoxLayout;
        mainLayout->addLayout(left, 0);

        auto *paramsBox = new QGroupBox("Parameters");
        auto *paramsLayout = new QVBoxLayout;
        paramsBox->setLayout(paramsLayout);
        left->addWidget(paramsBox);

        auto *nLayout = new QHBoxLayout;
        nLayout->addWidget(new QLabel("People (n):"));
        nSpin = new QSpinBox; nSpin->setRange(1, 200); nSpin->setValue(7);
        nLayout->addWidget(nSpin);
        paramsLayout->addLayout(nLayout);

        auto *kLayout = new QHBoxLayout;
        kLayout->addWidget(new QLabel("Step (k):"));
        kSpin = new QSpinBox; kSpin->setRange(1, 1000); kSpin->setValue(3);
        kLayout->addWidget(kSpin);
        paramsLayout->addLayout(kLayout);

        auto *speedLayout = new QHBoxLayout;
        speedLayout->addWidget(new QLabel("Speed:"));
        speedSlider = new QSlider(Qt::Horizontal);
        speedSlider->setRange(50, 1500);
        speedSlider->setValue(500);
        speedLayout->addWidget(speedSlider);
        paramsLayout->addLayout(speedLayout);

        auto *btnLayout = new QHBoxLayout;
        startBtn = new QPushButton("Start");
        stepBtn = new QPushButton("Step");
        resetBtn = new QPushButton("Reset");
        btnLayout->addWidget(startBtn);
        btnLayout->addWidget(stepBtn);
        btnLayout->addWidget(resetBtn);
        left->addLayout(btnLayout);

        auto *quickBox = new QGroupBox("Quick");
        auto *quickLayout = new QHBoxLayout;
        quickBox->setLayout(quickLayout);
        left->addWidget(quickBox);

        auto *solveBtn = new QPushButton("Compute Safe Pos");
        quickLayout->addWidget(solveBtn);

        log = new QTextEdit;
        log->setReadOnly(true);
        log->setMinimumHeight(200);
        left->addWidget(new QLabel("Log"));
        left->addWidget(log);

        left->addStretch(1);

        
        circle = new CircleWidget;
        mainLayout->addWidget(circle, 1);
        connect(startBtn, &QPushButton::clicked, this, &MainWindow::onStart);
        connect(stepBtn, &QPushButton::clicked, this, &MainWindow::onStepManual);
        connect(resetBtn, &QPushButton::clicked, this, &MainWindow::onReset);
        connect(solveBtn, &QPushButton::clicked, this, &MainWindow::onComputeSafe);
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MainWindow::onTimerTick);

        onReset();
        setWindowTitle("Josephus Visualizer — Qt6");
        resize(900, 560);
    }

private slots:
    
    void onReset() {
        timer->stop();
        running = false;
        log->clear();
        int n = nSpin->value();
        k = kSpin->value();
        circle->setPeople(n);

        active.clear();
        for (int i = 0; i < n; ++i) active.push_back(i);
        countPos = 0; // start counting from index 0
        appendLog(QString("Reset with n=%1, k=%2").arg(n).arg(k));

        startBtn->setText("Start");
    }

    void onStart() {
        if (!running) {
            int n = nSpin->value();
            if (n <= 0 || kSpin->value() <= 0) { appendLog("Invalid parameters!"); return; }
            k = kSpin->value();
            running = true;
            startBtn->setText("Pause");
            nSpin->setEnabled(false);
            kSpin->setEnabled(false);
            stepBtn->setEnabled(false);
            resetBtn->setEnabled(false);
            int interval = speedSlider->value();
            timer->start(interval);
            appendLog("Auto-run started");
        } else {
            timer->stop();
            running = false;
            startBtn->setText("Start");
            nSpin->setEnabled(true);
            kSpin->setEnabled(true);
            stepBtn->setEnabled(true);
            resetBtn->setEnabled(true);
            appendLog("Auto-run paused");
        }
    }

    
    void onStepManual() {
        if (circle->remainingCount() <= 1) {
            appendLog("Already finished.");
            return;
        }
        // ensure local variables reflect current inputs if not running
        k = kSpin->value();
        performEliminationStep();
    }

    // timer tick -> step with animation (2-phase)
    void onTimerTick() {
        if (circle->remainingCount() <= 1) {
            timer->stop();
            running = false;
            startBtn->setText("Start");
            nSpin->setEnabled(true);
            kSpin->setEnabled(true);
            stepBtn->setEnabled(true);
            resetBtn->setEnabled(true);
            appendLog("Finished.");
            return;
        }
        performEliminationStep();
    }

    // compute safe position using iterative formula
    void onComputeSafe() {
        int n = nSpin->value();
        int kk = kSpin->value();
        if (n <= 0 || kk <= 0) { appendLog("Invalid for safe computation"); return; }
        int res = 0;
        for (int i = 1; i <= n; ++i) res = (res + kk) % i;
        appendLog(QString("Safe position (1-based): %1").arg(res + 1));
    }

private:
    // do one elimination step: highlight counting then eliminate
    void performEliminationStep() {
        if (active.empty()) return;

        // counting: move countPos by k-1, wrap around
        countPos = (countPos + (k - 1)) % (int)active.size();
        int eliminateOriginalIndex = active[countPos];

        // highlight current
        circle->setCurrentHighlight(eliminateOriginalIndex);
        appendLog(QString("Counting... eliminate -> %1").arg(eliminateOriginalIndex + 1));

        // Elimination animation: show highlight for half of interval then remove
        int delay = std::max(50, speedSlider->value() / 2);
        // use a single-shot to perform the actual remove so UI shows highlight
        QTimer::singleShot(delay, this, [this, eliminateOriginalIndex]() {
            // mark eliminated in visual widget and remove from active vector
            circle->markEliminated(eliminateOriginalIndex);
            appendLog(QString("Eliminated %1").arg(eliminateOriginalIndex + 1));
            // update active vector: actual erase performed inside CircleWidget? we keep our own too
            for (auto it = active.begin(); it != active.end(); ++it) {
                if (*it == eliminateOriginalIndex) { active.erase(it); break; }
            }
            // next counting starts at same position (because after removing,
            // the next person is at this index).
            if (!active.empty()) {
                if (countPos >= (int)active.size()) countPos = countPos % (int)active.size();
                // set small delay before highlighting next candidate, so visuals are readable
                circle->resetState();
            } else {
                // finished: highlight survivor inside CircleWidget done already
                appendLog("Simulation complete.");
            }
        });
    }

    void appendLog(const QString &s) {
        log->append(s);
    }

    CircleWidget *circle = nullptr;
    QSpinBox *nSpin = nullptr;
    QSpinBox *kSpin = nullptr;
    QSlider *speedSlider = nullptr;
    QPushButton *startBtn = nullptr;
    QPushButton *stepBtn = nullptr;
    QPushButton *resetBtn = nullptr;
    QTextEdit *log = nullptr;
    QTimer *timer = nullptr;

    // simulation state
    std::vector<int> active; // original indices still in circle
    int k = 3;
    int countPos = 0; // index into active
    bool running = false;
};

#include "main.moc"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow w;
    w.show();
    return app.exec();
}

