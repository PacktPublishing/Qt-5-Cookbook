#include <QCoreApplication>
#include <QLoggingCategory>

Q_LOGGING_CATEGORY(component1, "myapp.component1", QtInfoMsg)
Q_LOGGING_CATEGORY(component2, "myapp.component2")

int main(int argc, char *argv[])
{
   QCoreApplication app(argc, argv);
   QCoreApplication::setApplicationName(QStringLiteral("logging"));

//   QLoggingCategory::setFilterRules("myapp.component1.debug=true\n"
//                                    "myapp.component2.info=false");
   qSetMessagePattern(QStringLiteral("%{pid}:%{appname}:%{file}:%{function}:%{line}:%{category}: %{message}"));

   qCDebug(component1) << "Debug";
   qCInfo(component1) << "Info";
   qCWarning(component1) << "Warning";
   qCCritical(component1) << "Critical";

   qDebug().setVerbosity(QDebug::MaximumVerbosity);
   if (qDebug().verbosity() > QDebug::MinimumVerbosity) {
      qDebug() << "APARECE";
   }
   qDebug() << component1().isDebugEnabled();

   qCDebug(component2) << "Debug";
   qCInfo(component2) << "Info";
   qCWarning(component2) << "Warning";
   qCCritical(component2) << "Critical";
}

