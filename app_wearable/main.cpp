#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickStyle>
#include "connect.h"


int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    //设置QML样式
    QQuickStyle::setStyle(QStringLiteral("qrc:/qml/Style"));

    //注册到元对象系统
    qmlRegisterType<Connect>("Connect",1,0,"Connect");


    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
