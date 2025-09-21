 : lightPalette();
        QApplication::setPalette(palette);

        QString titleStyle = QString("font-size: 20px; font-weight: bold; padding: 10px; color: %1;")
                                 .arg(darkMode ? "white" : "black");
        title->setStyleSheet(titleStyle);

        QString buttonStyle = QString("font-weight: bold; padding: 6px; background-color: %1; color: %2;")
                                  .arg(darkMode ? "#3A3A3A" : "#E0E0E0")
                                  .arg(darkMode ? "white" : "black");
        solveButton->setStyleSheet(buttonStyle);
        themeToggle->setStyleSheet(buttonStyle);
    }

private:
    QLineEdit *peopleInput;
    QLineEdit *stepInput;
    QTextEdit *resultBox;
    QPushButton *solveButton;
    QPushButton *themeToggle;
    QLabel *title;
    bool darkMode = false;

    void setupUI() {
        auto *central = new QWidget(this);
        setCentralWidget(central);
        auto *layout = new QVBoxLayout(central);

        title = new QLabel("⚔️ Josephus Problem Solver ⚔️");
        title->setAlignment(Qt::AlignCenter);
        layout->addWidget(title);

        peopleInput = new QLineEdit();
        peopleInput->setPlaceholderText("Enter number of people");
        layout->addWidget(peopleInput);

        stepInput = new QLineEdit();
        stepInput->setPlaceholderText("Enter step size");
        layout->addWidget(stepInput);

        solveButton = new QPushButton("Solve");
        layout->addWidget(solveButton);

        resultBox = new QTextEdit();
        resultBox->setReadOnly(true);
        resultBox->setFixedHeight(60);
        layout->addWidget(resultBox);

        themeToggle = new QPushButton("🌙 Toggle Dark Mode");
        layout->addWidget(themeToggle);

        connect(solveButton, &QPushButton::clicked, this, &JosephusApp::solveProblem);
        connect(themeToggle, &QPushButton::clicked, this, &JosephusApp::toggleTheme);

        toggleTheme();
        toggleTheme();
    }

    static QPalette darkPalette() {
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(45, 45, 45));
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::Base, QColor(30, 30, 30));
        palette.setColor(QPalette::AlternateBase, QColor(45, 45, 45));
        palette.setColor(QPalette::ToolTipBase, Qt::white);
        palette.setColor(QPalette::ToolTipText, Qt::white);
        palette.setColor(QPalette::Text, Qt::white);
        palette.setColor(QPalette::Button, QColor(60, 60, 60));
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::BrightText, Qt::red);
        return palette;
    }

    static QPalette lightPalette() {
        return QApplication::style()->standardPalette();
    }
};

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    JosephusApp window;
    window.show();
    return app.exec();
}

#include "main.moc"#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QPalette>
#include <QMessageBox>

int josephus(int n, int k) {
    int result = 0;
    for (int i = 1; i <= n; i++) {
        result = (result + k) % i;
    }
    return result + 1;
}

class JosephusApp : public QMainWindow {
    Q_OBJECT

public:
    JosephusApp(QWidget *parent = nullptr) : QMainWindow(parent) {
        setupUI();
        setWindowTitle("Josephus Solver");
        setMinimumSize(420, 320);
    }

private slots:
    void solveProblem() {
        bool okN, okK;
        int n = peopleInput->text().toInt(&okN);
        int k = stepInput->text().toInt(&okK);

        if (!okN || !okK || n <= 0 || k <= 0) {
            resultBox->clear();
            QMessageBox::warning(this, "Invalid Input",
                                 "Please enter valid positive integers for people and step size.");
            return;
        }

        int survivor = josephus(n, k);
        resultBox->setText(
            QString("With %1 people and step size %2,\n"
                    "the safe position is: %3")
                .arg(n).arg(k).arg(survivor));
    }

    void toggleTheme() {
        darkMode = !darkMode;
        QPalette palette = darkMode ? darkPalette() : lightPalette();
        QApplication::setPalette(palette);

        QString titleStyle = QString("font-size: 20px; font-weight: bold; padding: 10px; color: %1;")
                                 .arg(darkMode ? "white" : "black");
        title->setStyleSheet(titleStyle);

        QString buttonStyle = QString("font-weight: bold; padding: 6px; background-color: %1; color: %2;")
                                  .arg(darkMode ? "#3A3A3A" : "#E0E0E0")
                                  .arg(darkMode ? "white" : "black");
        solveButton->setStyleSheet(buttonStyle);
        themeToggle->setStyleSheet(buttonStyle);
    }

private:
    QLineEdit *peopleInput;
    QLineEdit *stepInput;
    QTextEdit *resultBox;
    QPushButton *solveButton;
    QPushButton *themeToggle;
    QLabel *title;
    bool darkMode = false;

    void setupUI() {
        auto *central = new QWidget(this);
        setCentralWidget(central);
        auto *layout = new QVBoxLayout(central);

        title = new QLabel("⚔️ Josephus Problem Solver ⚔️");
        title->setAlignment(Qt::AlignCenter);
        layout->addWidget(title);

        peopleInput = new QLineEdit();
        peopleInput->setPlaceholderText("Enter number of people");
        layout->addWidget(peopleInput);

        stepInput = new QLineEdit();
        stepInput->setPlaceholderText("Enter step size");
        layout->addWidget(stepInput);

        solveButton = new QPushButton("Solve");
        layout->addWidget(solveButton);

        resultBox = new QTextEdit();
        resultBox->setReadOnly(true);
        resultBox->setFixedHeight(60);
        layout->addWidget(resultBox);

        themeToggle = new QPushButton("🌙 Toggle Dark Mode");
        layout->addWidget(themeToggle);

        connect(solveButton, &QPushButton::clicked, this, &JosephusApp::solveProblem);
        connect(themeToggle, &QPushButton::clicked, this, &JosephusApp::toggleTheme);

        toggleTheme();
        toggleTheme();
    }

    static QPalette darkPalette() {
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(45, 45, 45));
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::Base, QColor(30, 30, 30));
        palette.setColor(QPalette::AlternateBase, QColor(45, 45, 45));
        palette.setColor(QPalette::ToolTipBase, Qt::white);
        palette.setColor(QPalette::ToolTipText, Qt::white);
        palette.setColor(QPalette::Text, Qt::white);
        palette.setColor(QPalette::Button, QColor(60, 60, 60));
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::BrightText, Qt::red);
        return palette;
    }

    static QPalette lightPalette() {
        return QApplication::style()->standardPalette();
    }
};

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    JosephusApp window;
    window.show();
    return app.exec();
}

#include "main.moc"#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QPalette>
#include <QMessageBox>

int josephus(int n, int k) {
    int result = 0;
    for (int i = 1; i <= n; i++) {
        result = (result + k) % i;
    }
    return result + 1;
}

class JosephusApp : public QMainWindow {
    Q_OBJECT

public:
    JosephusApp(QWidget *parent = nullptr) : QMainWindow(parent) {
        setupUI();
        setWindowTitle("Josephus Solver");
        setMinimumSize(420, 320);
    }

private slots:
    void solveProblem() {
        bool okN, okK;
        int n = peopleInput->text().toInt(&okN);
        int k = stepInput->text().toInt(&okK);

        if (!okN || !okK || n <= 0 || k <= 0) {
            resultBox->clear();
            QMessageBox::warning(this, "Invalid Input",
                                 "Please enter valid positive integers for people and step size.");
            return;
        }

        int survivor = josephus(n, k);
        resultBox->setText(
            QString("With %1 people and step size %2,\n"
                    "the safe position is: %3")
                .arg(n).arg(k).arg(survivor));
    }

    void toggleTheme() {
        darkMode = !darkMode;
        QPalette palette = darkMode ? darkPalette() : lightPalette();
        QApplication::setPalette(palette);

        QString titleStyle = QString("font-size: 20px; font-weight: bold; padding: 10px; color: %1;")
                                 .arg(darkMode ? "white" : "black");
        title->setStyleSheet(titleStyle);

        QString buttonStyle = QString("font-weight: bold; padding: 6px; background-color: %1; color: %2;")
                                  .arg(darkMode ? "#3A3A3A" : "#E0E0E0")
                                  .arg(darkMode ? "white" : "black");
        solveButton->setStyleSheet(buttonStyle);
        themeToggle->setStyleSheet(buttonStyle);
    }

private:
    QLineEdit *peopleInput;
    QLineEdit *stepInput;
    QTextEdit *resultBox;
    QPushButton *solveButton;
    QPushButton *themeToggle;
    QLabel *title;
    bool darkMode = false;

    void setupUI() {
        auto *central = new QWidget(this);
        setCentralWidget(central);
        auto *layout = new QVBoxLayout(central);

        title = new QLabel("⚔️ Josephus Problem Solver ⚔️");
        title->setAlignment(Qt::AlignCenter);
        layout->addWidget(title);

        peopleInput = new QLineEdit();
        peopleInput->setPlaceholderText("Enter number of people");
        layout->addWidget(peopleInput);

        stepInput = new QLineEdit();
        stepInput->setPlaceholderText("Enter step size");
        layout->addWidget(stepInput);

        solveButton = new QPushButton("Solve");
        layout->addWidget(solveButton);

        resultBox = new QTextEdit();
        resultBox->setReadOnly(true);
        resultBox->setFixedHeight(60);
        layout->addWidget(resultBox);

        themeToggle = new QPushButton("🌙 Toggle Dark Mode");
        layout->addWidget(themeToggle);

        connect(solveButton, &QPushButton::clicked, this, &JosephusApp::solveProblem);
        connect(themeToggle, &QPushButton::clicked, this, &JosephusApp::toggleTheme);

        toggleTheme();
        toggleTheme();
    }

    static QPalette darkPalette() {
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(45, 45, 45));
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::Base, QColor(30, 30, 30));
        palette.setColor(QPalette::AlternateBase, QColor(45, 45, 45));
        palette.setColor(QPalette::ToolTipBase, Qt::white);
        palette.setColor(QPalette::ToolTipText, Qt::white);
        palette.setColor(QPalette::Text, Qt::white);
        palette.setColor(QPalette::Button, QColor(60, 60, 60));
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::BrightText, Qt::red);
        return palette;
    }

    static QPalette lightPalette() {
        return QApplication::style()->standardPalette();
    }
};

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    JosephusApp window;
    window.show();
    return app.exec();
}

#include "main.moc"#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QPalette>
#include <QMessageBox>

int josephus(int n, int k) {
    int result = 0;
    for (int i = 1; i <= n; i++) {
        result = (result + k) % i;
    }
    return result + 1;
}

class JosephusApp : public QMainWindow {
    Q_OBJECT

public:
    JosephusApp(QWidget *parent = nullptr) : QMainWindow(parent) {
        setupUI();
        setWindowTitle("Josephus Solver");
        setMinimumSize(420, 320);
    }

private slots:
    void solveProblem() {
        bool okN, okK;
        int n = peopleInput->text().toInt(&okN);
        int k = stepInput->text().toInt(&okK);

        if (!okN || !okK || n <= 0 || k <= 0) {
            resultBox->clear();
            QMessageBox::warning(this, "Invalid Input",
                                 "Please enter valid positive integers for people and step size.");
            return;
        }

        int survivor = josephus(n, k);
        resultBox->setText(
            QString("With %1 people and step size %2,\n"
                    "the safe position is: %3")
                .arg(n).arg(k).arg(survivor));
    }

    void toggleTheme() {
        darkMode = !darkMode;
        QPalette palette = darkMode ? darkPalette() : lightPalette();
        QApplication::setPalette(palette);

        QString titleStyle = QString("font-size: 20px; font-weight: bold; padding: 10px; color: %1;")
                                 .arg(darkMode ? "white" : "black");
        title->setStyleSheet(titleStyle);

        QString buttonStyle = QString("font-weight: bold; padding: 6px; background-color: %1; color: %2;")
                                  .arg(darkMode ? "#3A3A3A" : "#E0E0E0")
                                  .arg(darkMode ? "white" : "black");
        solveButton->setStyleSheet(buttonStyle);
        themeToggle->setStyleSheet(buttonStyle);
    }

private:
    QLineEdit *peopleInput;
    QLineEdit *stepInput;
    QTextEdit *resultBox;
    QPushButton *solveButton;
    QPushButton *themeToggle;
    QLabel *title;
    bool darkMode = false;

    void setupUI() {
        auto *central = new QWidget(this);
        setCentralWidget(central);
        auto *layout = new QVBoxLayout(central);

        title = new QLabel("⚔️ Josephus Problem Solver ⚔️");
        title->setAlignment(Qt::AlignCenter);
        layout->addWidget(title);

        peopleInput = new QLineEdit();
        peopleInput->setPlaceholderText("Enter number of people");
        layout->addWidget(peopleInput);

        stepInput = new QLineEdit();
        stepInput->setPlaceholderText("Enter step size");
        layout->addWidget(stepInput);

        solveButton = new QPushButton("Solve");
        layout->addWidget(solveButton);

        resultBox = new QTextEdit();
        resultBox->setReadOnly(true);
        resultBox->setFixedHeight(60);
        layout->addWidget(resultBox);

        themeToggle = new QPushButton("🌙 Toggle Dark Mode");
        layout->addWidget(themeToggle);

        connect(solveButton, &QPushButton::clicked, this, &JosephusApp::solveProblem);
        connect(themeToggle, &QPushButton::clicked, this, &JosephusApp::toggleTheme);

        toggleTheme();
        toggleTheme();
    }

    static QPalette darkPalette() {
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(45, 45, 45));
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::Base, QColor(30, 30, 30));
        palette.setColor(QPalette::AlternateBase, QColor(45, 45, 45));
        palette.setColor(QPalette::ToolTipBase, Qt::white);
        palette.setColor(QPalette::ToolTipText, Qt::white);
        palette.setColor(QPalette::Text, Qt::white);
        palette.setColor(QPalette::Button, QColor(60, 60, 60));
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::BrightText, Qt::red);
        return palette;
    }

    static QPalette lightPalette() {
        return QApplication::style()->standardPalette();
    }
};

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    JosephusApp window;
    window.show();
    return app.exec();
}

#include "main.moc"#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QPalette>
#include <QMessageBox>

int josephus(int n, int k) {
    int result = 0;
    for (int i = 1; i <= n; i++) {
        result = (result + k) % i;
    }
    return result + 1;
}

class JosephusApp : public QMainWindow {
    Q_OBJECT

public:
    JosephusApp(QWidget *parent = nullptr) : QMainWindow(parent) {
        setupUI();
        setWindowTitle("Josephus Solver");
        setMinimumSize(420, 320);
    }

private slots:
    void solveProblem() {
        bool okN, okK;
        int n = peopleInput->text().toInt(&okN);
        int k = stepInput->text().toInt(&okK);

        if (!okN || !okK || n <= 0 || k <= 0) {
            resultBox->clear();
            QMessageBox::warning(this, "Invalid Input",
                                 "Please enter valid positive integers for people and step size.");
            return;
        }

        int survivor = josephus(n, k);
        resultBox->setText(
            QString("With %1 people and step size %2,\n"
                    "the safe position is: %3")
                .arg(n).arg(k).arg(survivor));
    }

    void toggleTheme() {
        darkMode = !darkMode;
        QPalette palette = darkMode ? darkPalette() : lightPalette();
        QApplication::setPalette(palette);

        QString titleStyle = QString("font-size: 20px; font-weight: bold; padding: 10px; color: %1;")
                                 .arg(darkMode ? "white" : "black");
        title->setStyleSheet(titleStyle);

        QString buttonStyle = QString("font-weight: bold; padding: 6px; background-color: %1; color: %2;")
                                  .arg(darkMode ? "#3A3A3A" : "#E0E0E0")
                                  .arg(darkMode ? "white" : "black");
        solveButton->setStyleSheet(buttonStyle);
        themeToggle->setStyleSheet(buttonStyle);
    }

private:
    QLineEdit *peopleInput;
    QLineEdit *stepInput;
    QTextEdit *resultBox;
    QPushButton *solveButton;
    QPushButton *themeToggle;
    QLabel *title;
    bool darkMode = false;

    void setupUI() {
        auto *central = new QWidget(this);
        setCentralWidget(central);
        auto *layout = new QVBoxLayout(central);

        title = new QLabel("⚔️ Josephus Problem Solver ⚔️");
        title->setAlignment(Qt::AlignCenter);
        layout->addWidget(title);

        peopleInput = new QLineEdit();
        peopleInput->setPlaceholderText("Enter number of people");
        layout->addWidget(peopleInput);

        stepInput = new QLineEdit();
        stepInput->setPlaceholderText("Enter step size");
        layout->addWidget(stepInput);

        solveButton = new QPushButton("Solve");
        layout->addWidget(solveButton);

        resultBox = new QTextEdit();
        resultBox->setReadOnly(true);
        resultBox->setFixedHeight(60);
        layout->addWidget(resultBox);

        themeToggle = new QPushButton("🌙 Toggle Dark Mode");
        layout->addWidget(themeToggle);

        connect(solveButton, &QPushButton::clicked, this, &JosephusApp::solveProblem);
        connect(themeToggle, &QPushButton::clicked, this, &JosephusApp::toggleTheme);

        toggleTheme();
        toggleTheme();
    }

    static QPalette darkPalette() {
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(45, 45, 45));
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::Base, QColor(30, 30, 30));
        palette.setColor(QPalette::AlternateBase, QColor(45, 45, 45));
        palette.setColor(QPalette::ToolTipBase, Qt::white);
        palette.setColor(QPalette::ToolTipText, Qt::white);
        palette.setColor(QPalette::Text, Qt::white);
        palette.setColor(QPalette::Button, QColor(60, 60, 60));
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::BrightText, Qt::red);
        return palette;
    }

    static QPalette lightPalette() {
        return QApplication::style()->standardPalette();
    }
};

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    JosephusApp window;
    window.show();
    return app.exec();
}

#include "main.moc"#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QPalette>
#include <QMessageBox>

int josephus(int n, int k) {
    int result = 0;
    for (int i = 1; i <= n; i++) {
        result = (result + k) % i;
    }
    return result + 1;
}

class JosephusApp : public QMainWindow {
    Q_OBJECT

public:
    JosephusApp(QWidget *parent = nullptr) : QMainWindow(parent) {
        setupUI();
        setWindowTitle("Josephus Solver");
        setMinimumSize(420, 320);
    }

private slots:
    void solveProblem() {
        bool okN, okK;
        int n = peopleInput->text().toInt(&okN);
        int k = stepInput->text().toInt(&okK);

        if (!okN || !okK || n <= 0 || k <= 0) {
            resultBox->clear();
            QMessageBox::warning(this, "Invalid Input",
                                 "Please enter valid positive integers for people and step size.");
            return;
        }

        int survivor = josephus(n, k);
        resultBox->setText(
            QString("With %1 people and step size %2,\n"
                    "the safe position is: %3")
                .arg(n).arg(k).arg(survivor));
    }

    void toggleTheme() {
        darkMode = !darkMode;
        QPalette palette = darkMode ? darkPalette() : lightPalette();
        QApplication::setPalette(palette);

        QString titleStyle = QString("font-size: 20px; font-weight: bold; padding: 10px; color: %1;")
                                 .arg(darkMode ? "white" : "black");
        title->setStyleSheet(titleStyle);

        QString buttonStyle = QString("font-weight: bold; padding: 6px; background-color: %1; color: %2;")
                                  .arg(darkMode ? "#3A3A3A" : "#E0E0E0")
                                  .arg(darkMode ? "white" : "black");
        solveButton->setStyleSheet(buttonStyle);
        themeToggle->setStyleSheet(buttonStyle);
    }

private:
    QLineEdit *peopleInput;
    QLineEdit *stepInput;
    QTextEdit *resultBox;
    QPushButton *solveButton;
    QPushButton *themeToggle;
    QLabel *title;
    bool darkMode = false;

    void setupUI() {
        auto *central = new QWidget(this);
        setCentralWidget(central);
        auto *layout = new QVBoxLayout(central);

        title = new QLabel("⚔️ Josephus Problem Solver ⚔️");
        title->setAlignment(Qt::AlignCenter);
        layout->addWidget(title);

        peopleInput = new QLineEdit();
        peopleInput->setPlaceholderText("Enter number of people");
        layout->addWidget(peopleInput);

        stepInput = new QLineEdit();
        stepInput->setPlaceholderText("Enter step size");
        layout->addWidget(stepInput);

        solveButton = new QPushButton("Solve");
        layout->addWidget(solveButton);

        resultBox = new QTextEdit();
        resultBox->setReadOnly(true);
        resultBox->setFixedHeight(60);
        layout->addWidget(resultBox);

        themeToggle = new QPushButton("🌙 Toggle Dark Mode");
        layout->addWidget(themeToggle);

        connect(solveButton, &QPushButton::clicked, this, &JosephusApp::solveProblem);
        connect(themeToggle, &QPushButton::clicked, this, &JosephusApp::toggleTheme);

        toggleTheme();
        toggleTheme();
    }

    static QPalette darkPalette() {
        QPalette palette;
        palette.setColor(QPalette::Window, QColor(45, 45, 45));
        palette.setColor(QPalette::WindowText, Qt::white);
        palette.setColor(QPalette::Base, QColor(30, 30, 30));
        palette.setColor(QPalette::AlternateBase, QColor(45, 45, 45));
        palette.setColor(QPalette::ToolTipBase, Qt::white);
        palette.setColor(QPalette::ToolTipText, Qt::white);
        palette.setColor(QPalette::Text, Qt::white);
        palette.setColor(QPalette::Button, QColor(60, 60, 60));
        palette.setColor(QPalette::ButtonText, Qt::white);
        palette.setColor(QPalette::BrightText, Qt::red);
        return palette;
    }

    static QPalette lightPalette() {
        return QApplication::style()->standardPalette();
    }
};

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    JosephusApp window;
    window.show();
    return app.exec();
}

#include "main.moc"
