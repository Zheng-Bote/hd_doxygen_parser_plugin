#pragma once

#include <QDebug>
#include <QObject>
#include <QString>
#include <QtPlugin>

#include <QDir>
#include <QRegularExpression>
#include <QTextStream>

#include "rz_header_docu_plugins.h"

const QString PLUGIN_SHORTNAME = "doxygen";
const QString PLUGIN_NAME = "doxygen header parser";
const QString PLUGIN_VERSION = "1.0.0";

class Hd_doxygen_parser_plugin : public QObject, public Plugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "net.hase-zheng.header_docu_plugin");
    Q_INTERFACES(Plugin);

public:
    explicit Hd_doxygen_parser_plugin(QObject *parent = nullptr);
    ~Hd_doxygen_parser_plugin();

private:
    // QString parseLine(QString text);

signals:
public slots:

    // Plugin interface
public:
    void test(QString name) Q_DECL_OVERRIDE;
    QString getName() Q_DECL_OVERRIDE;
    QString getVersion() Q_DECL_OVERRIDE;

    void parseFile(QMap<QString, QString> &mapParseKeys, QString pathToFile) Q_DECL_OVERRIDE;
    void writeFile(QMap<QString, QString> mapParseKeys,
                   QMap<QString, QString> mapFileAttribs,
                   QString pathToFile) Q_DECL_OVERRIDE;
};
