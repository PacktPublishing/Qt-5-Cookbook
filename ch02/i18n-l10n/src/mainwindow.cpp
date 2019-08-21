#include "mainwindow.h"

#include <QApplication>
#include <QColorDialog>
#include <QComboBox>
#include <QDateTime>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QPushButton>
#include <QToolBar>
#include <QVBoxLayout>

MainWindow::MainWindow(const QLocale &locale, QWidget *parent) :
   QMainWindow(parent),
   _locale(locale),
   _messagesSent(0)
{
   // Set window title
   setWindowTitle(tr("i18n/l10n Example Application"));

   // Menu with simple menu item
   auto fileMenu = menuBar()->addMenu(tr("&File"));
   auto exitAction = fileMenu->addAction(
            QIcon(QStringLiteral(":/icons/exit.svg")),
            tr("E&xit"),
            QApplication::instance(), &QApplication::exit,
            QKeySequence::Quit // No translation for standard actions
            );

   auto colorAction = menuBar()->addMenu(tr("&Tools"))->addAction(
            QIcon(QStringLiteral(":/icons/bgcolor.svg")),
            tr("&Background Color"),
            this, [this](){
               QPalette windowPalette { palette() };
               windowPalette.setColor(
                        backgroundRole(), QColorDialog::getColor());
               setPalette(windowPalette);
            },
            tr("Ctrl+T, Ctrl+B") // Enabling translation for shortcuts
            );

   // Main toolbar with simple action
   auto mainToolBar = addToolBar(tr("Main toolbar"));
   mainToolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
   mainToolBar->addAction(exitAction);
   mainToolBar->addAction(colorAction);

   // Label
   auto label = new QLabel { tr("i18n/l10n Example Application") };
   label->setAlignment(Qt::AlignHCenter);

   // Ambiguous buttons
   auto playLayout = new QHBoxLayout;
   //: Play (the game).
   playLayout->addWidget(new QPushButton { tr("Play") });
   playLayout->addWidget(
            new QPushButton { tr("Play", "Play (the song).") });

   // Message buttons
   auto sendButton = new QPushButton { tr("Send Message") };
   auto sentLabel = new QLabel {
         tr("%n message(s) sent", "", _messagesSent) };
   sentLabel->setAlignment(Qt::AlignHCenter);
   connect(sendButton, &QPushButton::clicked,
           this, [this, sentLabel](){
              sentLabel->setText(tr("%n message(s) sent", "",
                                    ++_messagesSent));
   });
   auto resetButton = new QPushButton { tr("Reset Counter") };
   connect(resetButton, &QPushButton::clicked,
           this, [this, sentLabel](){
              sentLabel->setText(tr("%n message(s) sent", "",
                                    _messagesSent = 0));
   });
   auto messageButtonsLayout = new QHBoxLayout;
   messageButtonsLayout->addWidget(sendButton);
   messageButtonsLayout->addWidget(resetButton);

   // Translating strings in variables
   std::array<const char *, 5> moodOptions {
      QT_TR_NOOP("Good morning"),
      QT_TR_NOOP("Bad morning"),
      QT_TR_NOOP("Good afternoon"),
      QT_TR_NOOP("Bad afternoon"),
      nullptr
   };
   auto comboBox1 = new QComboBox;
   for (auto option : moodOptions) {
      comboBox1->addItem(tr(option));
   }
   connect(comboBox1,
           QOverload<int>::of(&QComboBox::currentIndexChanged),
           this, [this, moodOptions](int index){
      // NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-constant-array-index)
      if (QLatin1String(moodOptions[static_cast<quint64>(index)]).
          startsWith(QStringLiteral("Good"))) {
         QMessageBox::information(this, tr("Information"),
                                  tr("Good mood!"));
      } else {
         QMessageBox::information(this, tr("Information"),
                                  tr("Bad mood!"));
      }
   });

   // Translating numbers and dates
   auto numberLabel = new QLabel;
   numberLabel->setText(tr("This is a localized number: %1\n"
                           "This is a localized datetime: %2")
                        .arg(_locale.toString(1203.1023),
                             _locale.toString(
                                QDateTime::currentDateTime(),
                                QLocale::ShortFormat)));
   numberLabel->setAlignment(Qt::AlignHCenter);

   // Localized image
   auto imageLabel = new QLabel;
   imageLabel->setPixmap(QStringLiteral(":/icons/flag.png"));
   imageLabel->setAlignment(Qt::AlignCenter);

   // Central widget
   auto centralWidget = new QWidget;
   setCentralWidget(centralWidget);
   auto centralLayout = new QVBoxLayout { centralWidget };
   centralLayout->addWidget(label);
   centralLayout->addLayout(playLayout);
   centralLayout->addLayout(messageButtonsLayout);
   centralLayout->addWidget(sentLabel);
   centralLayout->addWidget(comboBox1);
   centralLayout->addWidget(numberLabel);
   centralLayout->addWidget(imageLabel);
   centralLayout->addSpacerItem(new QSpacerItem(0, 0,
                     QSizePolicy::Minimum, QSizePolicy::Expanding));

   resize(640, 480);
}
